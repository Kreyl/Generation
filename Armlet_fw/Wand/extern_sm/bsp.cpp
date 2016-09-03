/*
 * bsp.cpp
 *
 *  Created on: 3 сент. 2016 г.
 *      Author: Kreyl
 */

#include "colors.h"
#include "color.h"
#include "main.h"

static LedRGBChunk_t lsqBlink[] = {
        {csSetup, 0, clGreen},
        {csWait, 180},
        {csSetup, 0, clBlack},
        {csWait, 180},
        {csGoto, 0}
};

#ifdef __cplusplus
extern "C" {
#endif

void RGB_blink_slow(uint8_t Color) {
    lsqBlink[0].Color.Set(Colors[Color].R, Colors[Color].G, Colors[Color].B);
    lsqBlink[1].Time_ms = 270;
    lsqBlink[3].Time_ms = 270;
    Led.StartSequence(lsqBlink);
}

void RGB_blink_fast(uint8_t Color) {
    lsqBlink[0].Color.Set(Colors[Color].R, Colors[Color].G, Colors[Color].B);
    lsqBlink[1].Time_ms = 99;
    lsqBlink[3].Time_ms = 99;
    Led.StartSequence(lsqBlink);
}

void RGB_blink_stop() {
    Led.Stop();
}

void vibro(uint8_t Power) {
    Vibro.Set(Power);
}

#ifdef __cplusplus
}
#endif

