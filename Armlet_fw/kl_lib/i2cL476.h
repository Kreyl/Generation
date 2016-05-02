/*
 * i2cL476.h
 *
 *  Created on: 2 мая 2016 г.
 *      Author: Kreyl
 */

#pragma once

#include "kl_lib.h"

struct i2cParams_t {
    I2C_TypeDef *pi2c;
    GPIO_TypeDef *PGpio;
    uint16_t SclPin;
    uint16_t SdaPin;
    uint32_t Timing;    // Setting for TIMINGR register
//    stm32_dma_stream_t *APDmaTx;
//    stm32_dma_stream_t *APDmaRx;
};

class i2c_t {
private:
    const i2cParams_t *PParams;
public:
    i2c_t(const i2cParams_t *APParams) : PParams(APParams) {}
    void Init();
    void ScanBus();
};

extern i2c_t i2c3;
