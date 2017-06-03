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
#define ACC_I2C_ADDR        0x19
#define MAG_I2C_ADDR        0x1E

// LSM303 accelerometer: 8 g sensitivity
// 3.9 mg/digit; 1 g = 256
#define GRAVITY 256 //this equivalent to 1G in the raw data coming from the accelerometer

class Mems_t {
private:
    i2c_t *pi2c;
    // Gyro
    uint8_t gyroWriteReg(uint8_t Reg, uint8_t Value);
    uint8_t gyroReadReg(uint8_t Reg, uint8_t *PValue);
    uint8_t gyroRead(int16_t *pBuf);
    int32_t GyroOffset[3];
    // Acc
    uint8_t accWriteReg(uint8_t Reg, uint8_t Value);
    uint8_t accReadReg(uint8_t Reg, uint8_t *PValue);
    uint8_t accRead(int16_t *pBuf);
    int32_t AccOffset[3];
    // Magnetometer
    uint8_t magWriteReg(uint8_t Reg, uint8_t Value);
    uint8_t magReadReg(uint8_t Reg, uint8_t *PValue);
    uint8_t magRead(int16_t *pBuf);

    MemsState_t State = mstNormal;
    int32_t CalCounter;
public:
    int16_t Gyro[3];
    uint8_t Init();
    void SetState(MemsState_t NewState);
    void On()  { PinSetLo(MEMS_PWR_GPIO, MEMS_PWR_PIN); }
    void Off() { PinSetHi(MEMS_PWR_GPIO, MEMS_PWR_PIN); }
    Mems_t(i2c_t *api2c) : pi2c(api2c), State(mstNormal), CalCounter(0) {}
    void ITask();
};

extern Mems_t Mems;

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

#if 1 // ====================== Acc Register defines ===========================
#define ACC_CTRL_REG1       0x20
#define ACC_CTRL_REG2       0x21
#define ACC_CTRL_REG3       0x22
#define ACC_CTRL_REG4       0x23
#define ACC_CTRL_REG5       0x24
#define ACC_CTRL_REG6       0x25
#define ACC_OUT_X_L         0x28
#define ACC_OUT_X_H         0x29
#define ACC_OUT_Y_L         0x2A
#define ACC_OUT_Y_H         0x2B
#define ACC_OUT_Z_L         0x2C
#define ACC_OUT_Z_H         0x2D
#endif

#if 1 // ====================== Mag Register defines ===========================
#define MAG_CRA_REG         0x00
#define MAG_CRB_REG         0x01
#define MAG_MR_REG          0x02
#define MAG_OUT_X_H         0x03

#endif
