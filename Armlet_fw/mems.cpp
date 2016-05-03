/*
 * mems.cpp
 *
 *  Created on: 1 мая 2016 г.
 *      Author: Kreyl
 */

#include "mems.h"
#include "i2cL476.h"

Mems_t Mems;

#define mi2c    i2c1

uint8_t Mems_t::Init() {
    PinSetupOut(MEMS_PWR, omPushPull, pudNone);
    On();
    chThdSleepMilliseconds(99);
    mi2c.ScanBus();

    return 0;
}


//void i2c_t::Init() {
//    Standby();
//    Resume();
//
//    PinSetupOut(GPIOC, 2, omPushPull, pudNone);
//    PinSet(GPIOC, 2);
//    chThdSleepMilliseconds(4);
//
//    uint8_t DevAddress = 0x50;
//    uint32_t Size = 4;
//
//    uint32_t tmp = PParams->pi2c->CR2;  // Read CR2
//    // Clear bits
//    tmp &= (uint32_t)~((uint32_t)(I2C_CR2_SADD | I2C_CR2_NBYTES | I2C_CR2_RELOAD | I2C_CR2_AUTOEND | I2C_CR2_RD_WRN | I2C_CR2_START | I2C_CR2_STOP));
//    // Update bits
//    tmp |= (uint32_t)(((uint32_t)DevAddress) | ((Size << 16 ) & I2C_CR2_NBYTES) | (uint32_t)Mode | (uint32_t)Request);
//
//
//}

/*

void i2c_t::Standby() {
    if(PParams->pi2c == I2C1) { rccResetI2C1(); rccDisableI2C1(FALSE); }
#ifdef I2C2
    else if(PParams->pi2c == I2C2) { rccResetI2C2(); rccDisableI2C2(FALSE); }
#endif
#ifdef I2C3
    else if (PParams->pi2c == I2C3) { rccResetI2C3(); rccDisableI2C3(FALSE); }
#endif
    // Disable GPIOs
    PinSetupAnalog(PParams->PGpio, PParams->SclPin);
    PinSetupAnalog(PParams->PGpio, PParams->SdaPin);
}

void i2c_t::Resume() {
    // ==== GPIOs ====
    PinSetupAlterFunc(PParams->PGpio, PParams->SclPin, omOpenDrain, pudNone, AF4);
    PinSetupAlterFunc(PParams->PGpio, PParams->SclPin, omOpenDrain, pudNone, AF4);
    // ==== Clock and reset ====
    if(PParams->pi2c == I2C1) { rccEnableI2C1(FALSE); rccResetI2C1(); }
#ifdef I2C2
    else if(PParams->pi2c == I2C2) { rccEnableI2C2(FALSE); rccResetI2C2(); }
#endif
#ifdef I2C3
    else if (PParams->pi2c == I2C3) { rccEnableI2C3(FALSE); rccResetI2C3(); }
#endif
    PParams->pi2c->CR1 &= 0xF000; // Reset all and disable
    __NOP(); __NOP(); __NOP(); // When cleared, PE must be kept low for at least 3 APB clock cycles
    PParams->pi2c->TIMINGR = PParams->Timing;   // Setup timings
    // Enable the AUTOEND by default, and enable NACK (should be disabled only when Slave )
    PParams->pi2c->CR2 |= (I2C_CR2_AUTOEND | I2C_CR2_NACK);
    PParams->pi2c->CR1 |= I2C_CR1_PE;    // Enable i2c
//    // ==== DMA ====
//    ii2c->CR2 |= I2C_CR2_DMAEN;
}

*/
