/*
 * mems.h
 *
 *  Created on: 1 мая 2016 г.
 *      Author: Kreyl
 */

#pragma once

#include "kl_lib.h"

//struct i2cParams_t {
//    I2C_TypeDef *pi2c;
//    GPIO_TypeDef *PGpio;
//    uint16_t SclPin;
//    uint16_t SdaPin;
//    uint32_t Timing;    // Setting for TIMINGR register.
////    stm32_dma_stream_t *APDmaTx;
////    stm32_dma_stream_t *APDmaRx;
//};

//static const i2cParams_t memsI2CParams = {
//        I2C3,
////        GPIOB, 6, 7,
//        GPIOC, 0, 1,
//        0x00000004  // Calculated by Cube for 400kHz
//};


//class i2c_t {
//private:
//    const i2cParams_t *PParams;
//public:
//    void Init();
//    void Standby();
//    void Resume();
//    i2c_t(const i2cParams_t *APParams) : PParams(APParams) {}
//};


class Mems_t {
private:
//    i2c_t i2c {&memsI2CParams};

public:
    uint8_t Init();
};

extern Mems_t Mems;
