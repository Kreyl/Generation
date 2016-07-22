/*
 * ee.h
 *
 *  Created on: 3 мая 2016 г.
 *      Author: Kreyl
 */

#pragma once

#include "board.h"
#include "kl_lib.h"

class EE_t {
private:

public:
    void Init() { PinSetupOut(EE_PWR_GPIO, EE_PWR_PIN, omPushPull); }
    void On()   {
        PinSetHi(EE_PWR_GPIO, EE_PWR_PIN);
//        chThdSleepMilliseconds(1);
    }
    void Off()  { PinSetLo(EE_PWR_GPIO, EE_PWR_PIN); }
};

extern EE_t ee;
