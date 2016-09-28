/*
 * main.h
 *
 *  Created on: 15 сент. 2014 г.
 *      Author: g.kruglov
 */

#pragma once

#include "ch.h"
#include "kl_lib.h"
#include "uart.h"
#include "evt_mask.h"
#include "board.h"
#include "color.h"
#include "led.h"
#include "vibro.h"

#define APP_NAME            "ArmletRedTransmitter"

// ==== Constants and default values ====
#define ID_MIN              1
#define ID_MAX              36
#define ID_DEFAULT          ID_MIN

enum AppState_t { stIdle, stActive, stPowered };

class App_t {
private:
    thread_t *PThread;
    int32_t TimeLeft_s = 0;
    AppState_t State = stIdle;
public:
    uint8_t ID = 0;
    // Eternal methods
    void InitThread() { PThread = chThdGetSelfX(); }
    void SignalEvt(eventmask_t Evt) {
        chSysLock();
        chEvtSignalI(PThread, Evt);
        chSysUnlock();
    }
    void SignalEvtI(eventmask_t Evt) { chEvtSignalI(PThread, Evt); }
    void OnCmd(Shell_t *PShell);
    // Inner use
    void ITask();
};

extern App_t App;

extern LedRGB_t Led;
extern Vibro_t Vibro;
