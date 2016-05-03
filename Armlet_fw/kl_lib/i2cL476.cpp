/*
 * i2cL476.cpp
 *
 *  Created on: 2 мая 2016 г.
 *      Author: Kreyl
 */

#include "i2cL476.h"
#include "uart.h"

// TODO: remove DMA irqs

#define DMA_MODE_TX                                                         \
  (STM32_DMA_CR_PSIZE_BYTE | STM32_DMA_CR_MSIZE_BYTE | STM32_DMA_CR_MINC |  \
   STM32_DMA_CR_TEIE       | STM32_DMA_CR_TCIE       | STM32_DMA_CR_DIR_M2P | \
   STM32_DMA_CR_CHSEL(I2C3_DMA_CHNL) | DMA_PRIORITY_MEDIUM)

#define DMA_MODE_RX                                                         \
  (STM32_DMA_CR_PSIZE_BYTE | STM32_DMA_CR_MSIZE_BYTE | STM32_DMA_CR_MINC |  \
   STM32_DMA_CR_TEIE       | STM32_DMA_CR_TCIE       | STM32_DMA_CR_DIR_P2M | \
   STM32_DMA_CR_CHSEL(I2C3_DMA_CHNL) | DMA_PRIORITY_MEDIUM)

#define I2C_INT_MASK                                                        \
  ((uint32_t)(I2C_ISR_TCR | I2C_ISR_TC | I2C_ISR_STOPF | I2C_ISR_NACKF |    \
              I2C_ISR_ADDR | I2C_ISR_RXNE | I2C_ISR_TXIS))

#define I2C_ERROR_MASK                                                      \
  ((uint32_t)(I2C_ISR_BERR | I2C_ISR_ARLO | I2C_ISR_OVR | I2C_ISR_PECERR |  \
              I2C_ISR_TIMEOUT | I2C_ISR_ALERT))

#define I2C_NO_ERROR               0x00    /**< @brief No error.            */
#define I2C_BUS_ERROR              0x01    /**< @brief Bus Error.           */
#define I2C_ARBITRATION_LOST       0x02    /**< @brief Arbitration Lost.    */
#define I2C_ACK_FAILURE            0x04    /**< @brief Acknowledge Failure. */
#define I2C_OVERRUN                0x08    /**< @brief Overrun/Underrun.    */
#define I2C_PEC_ERROR              0x10    /**< @brief PEC Error in
                                                reception.                  */
#define I2C_TIMEOUT                0x20    /**< @brief Hardware timeout.    */
#define I2C_SMB_ALERT              0x40    /**< @brief SMBus Alert.         */

static const i2cParams_t I2C3Params = {
        I2C3,
//        GPIOB, 6, 7,
        GPIOC, 0, 1,
        0xE14,  // Calculated by Cube for 100kHz
        I2C3_DMA_TX, DMA_MODE_TX,
        I2C3_DMA_RX, DMA_MODE_RX,
        STM32_I2C3_EVENT_NUMBER,
        STM32_I2C3_ERROR_NUMBER
};

i2c_t i2c3 {&I2C3Params};

void i2c_t::Init() {
    // GPIO
//    PinSetupAlterFunc(PParams->PGpio, PParams->SclPin, omOpenDrain, pudNone, AF4);
//    PinSetupAlterFunc(PParams->PGpio, PParams->SdaPin, omOpenDrain, pudNone, AF4);
    // I2C
    I2C_TypeDef *pi2c = PParams->pi2c;  // To make things shorter
    pi2c->CR1 = 0;  // Clear PE bit => disable and reset i2c
    rccResetI2C3();
    rccEnableI2C3(FALSE);
    pi2c->TIMINGR = 0xE14;//PParams->Timing;    // setup timings
    // Analog filter enabled, digital disabled, clk stretch enabled, DMA enabled
//    pi2c->CR1 = I2C_CR1_TXDMAEN | I2C_CR1_RXDMAEN;
    // DMA
    dmaStreamAllocate(STM32_DMA1_STREAM2, IRQ_PRIO_MEDIUM, nullptr, nullptr);
    dmaStreamAllocate(STM32_DMA1_STREAM3, IRQ_PRIO_MEDIUM, nullptr, nullptr);
    dmaStreamSetPeripheral(PParams->PDmaRx, &pi2c->RXDR);
    dmaStreamSetPeripheral(STM32_DMA1_STREAM2, &pi2c->TXDR);
    // IRQ
    nvicEnableVector(72, IRQ_PRIO_MEDIUM);
    nvicEnableVector(73, IRQ_PRIO_MEDIUM);
}

void i2c_t::ScanBus() {
    Uart.Printf("\r     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f");
    uint32_t AddrHi, Addr;
    I2C_TypeDef *pi2c = PParams->pi2c;  // To make things shorter
    for(AddrHi = 0; AddrHi < 0x80; AddrHi += 0x10) {
        Uart.Printf("\r%02X: ", AddrHi);
        for(uint32_t n=0; n<0x10; n++) {
            Addr = AddrHi + n;
            if(Addr <= 0x01 or Addr > 0x77) Uart.Printf("   ");
            else {
                IReset(); // Reset I2C
                // Set addr and autoend; NBYTES = 0
                pi2c->CR2 = (Addr << 1) | I2C_CR2_AUTOEND;
                pi2c->CR2 |= I2C_CR2_START;     // Start
                while(!(pi2c->ISR & I2C_ISR_STOPF));
                if(pi2c->ISR & I2C_ISR_NACKF) Uart.Printf("__ ");
                else Uart.Printf("%02X ", Addr);
            }
        } // for lo
    } // for hi
    // Disable I2C
    pi2c->CR1 &= ~I2C_CR1_PE;
}

uint8_t i2c_t::WriteRead(uint32_t Addr, uint8_t *WPtr, uint32_t WLength, uint8_t *RPtr, uint32_t RLength) {
    I2C_TypeDef *pi2c = PParams->pi2c;  // To make things shorter
    if(WLength == 0) return CMD_ERROR;
    if(IBusyWait() != OK) return BUSY;
    IReset(); // Reset I2C
//    Uart.Printf("1\r");
    // Prepare TX DMA
    dmaStreamSetMode(STM32_DMA1_STREAM2, DMA_MODE_TX);
    dmaStreamSetMemory0(STM32_DMA1_STREAM2, WPtr);
    dmaStreamSetTransactionSize(STM32_DMA1_STREAM2, WLength);
    // Prepare RX DMA. RLength may be zero, it is ok.
    dmaStreamSetMode(PParams->PDmaRx, PParams->DmaRxMode);
    dmaStreamSetMemory0(PParams->PDmaRx, RPtr);
    dmaStreamSetTransactionSize(PParams->PDmaRx, RLength);
    // Prepare transmission
    IState = istWriteRead;
    pi2c->CR2 = (Addr << 1) | (WLength << 16);
    dmaStreamEnable(STM32_DMA1_STREAM2);   // Enable TX DMA
    // Enable IRQs: TX completed, error, NAck
    pi2c->CR1 |= (I2C_CR1_TCIE | I2C_CR1_ERRIE | I2C_CR1_NACKIE  | I2C_CR1_ADDRIE);
    pi2c->CR1 |= I2C_CR1_TXDMAEN | I2C_CR1_RXDMAEN;
    pi2c->CR2 |= I2C_CR2_START;         // Start transmission
    // Wait completion
//    Uart.Printf("2\r");
//    Uart.Printf("cr1=%X; cr2=%X\r", pi2c->CR1, pi2c->CR2);
//    Uart.Printf("ISR=%X\r", pi2c->ISR);
    chSysLock();
    msg_t r = chThdSuspendTimeoutS(&PThd, MS2ST(I2C_TIMEOUT_MS));
    chSysUnlock();
//    Uart.Printf("3\r");
    // Disable IRQs
    pi2c->CR1 &= ~(I2C_CR1_TCIE | I2C_CR1_ERRIE | I2C_CR1_NACKIE);
    if(r == MSG_TIMEOUT) {
        pi2c->CR2 |= I2C_CR2_STOP;
        return TIMEOUT;
    }
    else return (IState == istFailure)? FAILURE : OK;
}

void i2c_t::IReset() {
    PParams->pi2c->CR1 &= ~I2C_CR1_PE;
    __NOP(); __NOP(); __NOP();  // Wait 3 cycles
    PParams->pi2c->CR1 |= I2C_CR1_PE;
}

uint8_t i2c_t::IBusyWait() {
    uint8_t RetryCnt = 4;
    while(RetryCnt--) {
        if(!(PParams->pi2c->ISR & I2C_ISR_BUSY)) return OK;
        chThdSleepMilliseconds(1);
    }
    return TIMEOUT;
}


void i2c_t::IServeIRQ(uint32_t isr) {
    Uart.PrintfI("isr: %X\r", isr);
    I2C_TypeDef *pi2c = PParams->pi2c;  // To make things shorter
#if 1 // ==== NACK ====
    if((isr & I2C_ISR_NACKF) != 0) {
        // Stop DMA
        dmaStreamDisable(PParams->PDmaTx);
        dmaStreamDisable(PParams->PDmaRx);
        // Stop transaction
        pi2c->CR2 |= I2C_CR2_STOP;
        // Disable IRQs
        pi2c->CR1 &= ~(I2C_CR1_TCIE | I2C_CR1_TXIE | I2C_CR1_RXIE);
        IState = istFailure;
        IWakeup();
        return;
    }
#endif
#if 1 // ==== TX completed ====
    if((isr & I2C_ISR_TC) != 0) {
        Uart.PrintfI(" TC\r");
        switch(IState) {
            case istWriteWrite: { // First write completed
                dmaStreamDisable(PParams->PDmaTx);
                // TODO
            } break;

            case istWriteRead: {  // Write phase completed
                dmaStreamDisable(PParams->PDmaTx);
                uint32_t RLen = dmaStreamGetTransactionSize(PParams->PDmaRx);
                Uart.PrintfI("  WR %u\r", RLen);
                if(RLen > 0) {
                    pi2c->CR2 = (pi2c->CR2 & ~I2C_CR2_NBYTES) | I2C_CR2_RD_WRN | (RLen << 16);
                    dmaStreamEnable(PParams->PDmaRx);
                    pi2c->CR2 |= I2C_CR2_START; // Send repeated start
                    IState = istRead;
                    return;
                }
            } break;

            case istRead:   // Rx completed
                dmaStreamDisable(PParams->PDmaRx);
                break;

            case istWrite:
                dmaStreamDisable(PParams->PDmaTx);
                break;

            default: break;
        } // switch
        IState = istIdle;
        pi2c->CR2 |= I2C_CR2_STOP;
        pi2c->CR1 &= ~I2C_CR1_TCIE; // Disable TransferComplete IRQ
        IWakeup();
    }
#endif
}

void i2c_t::IServeErrIRQ(uint32_t isr) {
    Uart.PrintfI("isre: %X\r", isr);
    // Stop DMA
    dmaStreamDisable(PParams->PDmaTx);
    dmaStreamDisable(PParams->PDmaRx);
    // Check errors
    uint32_t Errors = 0;
    if(isr & I2C_ISR_BERR) Errors |= I2C_BUS_ERROR;
    if(isr & I2C_ISR_ARLO) Errors |= I2C_ARBITRATION_LOST;
    if(isr & I2C_ISR_OVR)  Errors |= I2C_OVERRUN;
    if(isr & I2C_ISR_TIMEOUT) Errors |= I2C_TIMEOUT;
    // If some error has been identified then wake the waiting thread
    if(Errors != I2C_NO_ERROR) {
        Uart.PrintfI("i2c err: %X\r", Errors);
        IWakeup();
    }
}

void i2c_t::IWakeup() {
    chSysLockFromISR();
    chThdResumeI(&PThd, MSG_OK);
    chSysUnlockFromISR();
}

#if 1 // =============================== IRQs ==================================
extern "C" {
// ==== I2C3 ====
OSAL_IRQ_HANDLER(STM32_I2C3_EVENT_HANDLER) {
    uint32_t isr = I2C3->ISR;
    OSAL_IRQ_PROLOGUE();
    I2C3->ICR = isr & I2C_INT_MASK; // Clear IRQ bits
    i2c3.IServeIRQ(isr);
    OSAL_IRQ_EPILOGUE();
}

OSAL_IRQ_HANDLER(STM32_I2C3_ERROR_HANDLER) {
    uint32_t isr = I2C3->ISR;
    OSAL_IRQ_PROLOGUE();
    I2C3->ICR = isr & I2C_ERROR_MASK; // Clear IRQ bits
    i2c3.IServeErrIRQ(isr);
    OSAL_IRQ_EPILOGUE();
}

} // extern C
#endif
