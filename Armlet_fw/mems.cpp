/*
 * mems.cpp
 *
 *  Created on: 1 мая 2016 г.
 *      Author: Kreyl
 */

#include "mems.h"
#include "uart.h"

uint8_t Mems_t::Init() {
    PinSetupOut(MEMS_PWR_GPIO, MEMS_PWR_PIN, omPushPull);
    On();
    chThdSleepMilliseconds(99);
    pi2c->ScanBus();
    // Gyro
    gyroWriteReg(L3G_CTRL_REG4, 0x20); // 2000 dps full scale
    gyroWriteReg(L3G_CTRL_REG1, 0x0F); // normal power mode, all axes enabled, 100 Hz

    uint8_t v=0;
    gyroReadReg(L3G_WHO_AM_I, &v);
    Uart.Printf("gyro: %X\r", v);

    return 0;
}

uint8_t Mems_t::gyroWriteReg(uint8_t Reg, uint8_t Value) {
    uint8_t Buf[2];
    Buf[0] = Reg;
    Buf[1] = Value;
    return pi2c->Write(L3G_I2C_ADDR, Buf, 2);
}

uint8_t Mems_t::gyroReadReg(uint8_t Reg, uint8_t *PValue) {
    return pi2c->WriteRead(L3G_I2C_ADDR, &Reg, 1, PValue, 1);
}
