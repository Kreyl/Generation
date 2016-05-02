/*
 * i2cL476.cpp
 *
 *  Created on: 2 мая 2016 г.
 *      Author: Kreyl
 */

#include "i2cL476.h"
#include "uart.h"

static const i2cParams_t I2C3Params = {
        I2C3,
//        GPIOB, 6, 7,
        GPIOC, 0, 1,
        0xE14  // Calculated by Cube for 100kHz
};

i2c_t i2c3 {&I2C3Params};

void i2c_t::Init() {
    // GPIO
    PinSetupAlterFunc(PParams->PGpio, PParams->SclPin, omOpenDrain, pudNone, AF4);
    PinSetupAlterFunc(PParams->PGpio, PParams->SdaPin, omOpenDrain, pudNone, AF4);
    // I2C
    I2C_TypeDef *pi2c = PParams->pi2c;  // To make things shorter
    pi2c->CR1 = 0;  // Clear PE bit => disable and reset i2c
    rccResetI2C3();
    rccEnableI2C3(FALSE);
    pi2c->CR1 = 0;  // Analog filter enabled, digital disabled, clk stretch enabled
    pi2c->TIMINGR = PParams->Timing;    // setup timings
    // Enable i2c
    pi2c->CR1 |= I2C_CR1_PE;
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
                // Reset I2C
                pi2c->CR1 &= ~I2C_CR1_PE;
                __NOP(); __NOP(); __NOP();  // Wait 3 cycles
                pi2c->CR1 |= I2C_CR1_PE;
                // Set addr and autoend; NBYTES = 0
                pi2c->CR2 = (Addr << 1) | I2C_CR2_AUTOEND;
                pi2c->CR2 |= I2C_CR2_START;     // Start
                while(!(pi2c->ISR & I2C_ISR_STOPF));
                if(pi2c->ISR & I2C_ISR_NACKF) Uart.Printf("__ ");
                else Uart.Printf("%02X ", Addr);
            }
        } // for lo
    } // for hi
}
