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

#define APP_NAME            "ArmletG"

#define RADIO_ENABLED       TRUE

// EEAddresses
#define EE_ADDR_DEVICE_ID   0
#define EE_ADDR_ABILITY     4

#define ID_MIN              1
#define ID_MAX              99
#define ID_DEFAULT          ID_MIN

#define DISCHARGED_INDICATION_PERIOD_S  360

class App_t {
private:
    thread_t *PThread;
public:
    uint8_t ID;
    uint32_t AbilityMsk = 0;
    bool UsbIsConnected() { return PinIsHi(USB_DETECT_PIN); }
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
