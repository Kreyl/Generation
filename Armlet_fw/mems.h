/*
 * mems.h
 *
 *  Created on: 1 мая 2016 г.
 *      Author: Kreyl
 */

#pragma once

#include "kl_lib.h"
#include "board.h"

class Mems_t {
private:

public:
    uint8_t Init();
    void On()  { PinClear(MEMS_PWR); }
    void Off() { PinSet(MEMS_PWR); }
};

extern Mems_t Mems;
