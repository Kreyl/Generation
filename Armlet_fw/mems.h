/*
 * mems.h
 *
 *  Created on: 1 мая 2016 г.
 *      Author: Kreyl
 */

#pragma once

#include "kl_lib.h"
#include "board.h"
#include "i2cL476.h"

#define L3G_I2C_ADDR        0x6B

class Mems_t {
private:
    i2c_t *pi2c;
    uint8_t gyroWriteReg(uint8_t Reg, uint8_t Value);
    uint8_t gyroReadReg(uint8_t Reg, uint8_t *PValue);
public:
    uint8_t Init();
    void On()  { PinSetLo(MEMS_PWR_GPIO, MEMS_PWR_PIN); }
    void Off() { PinSetHi(MEMS_PWR_GPIO, MEMS_PWR_PIN); }
    Mems_t(i2c_t *api2c) : pi2c(api2c) {}
};

#if 1 // ====================== L3G Register defines ===========================
#define L3G_WHO_AM_I        0x0F

#define L3G_CTRL_REG1       0x20
#define L3G_CTRL_REG2       0x21
#define L3G_CTRL_REG3       0x22
#define L3G_CTRL_REG4       0x23
#define L3G_CTRL_REG5       0x24
#define L3G_REFERENCE       0x25
#define L3G_OUT_TEMP        0x26
#define L3G_STATUS_REG      0x27

#define L3G_OUT_X_L         0x28
#define L3G_OUT_X_H         0x29
#define L3G_OUT_Y_L         0x2A
#define L3G_OUT_Y_H         0x2B
#define L3G_OUT_Z_L         0x2C
#define L3G_OUT_Z_H         0x2D

#define L3G_FIFO_CTRL_REG   0x2E
#define L3G_FIFO_SRC_REG    0x2F

#define L3G_INT1_CFG        0x30
#define L3G_INT1_SRC        0x31
#define L3G_INT1_THS_XH     0x32
#define L3G_INT1_THS_XL     0x33
#define L3G_INT1_THS_YH     0x34
#define L3G_INT1_THS_YL     0x35
#define L3G_INT1_THS_ZH     0x36
#define L3G_INT1_THS_ZL     0x37
#define L3G_INT1_DURATION   0x38
#define L3G_LOW_ODR         0x39
#endif
