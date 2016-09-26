/*
 * main.cpp
 *
 *  Created on: 20 февр. 2014 г.
 *      Author: g.kruglov
 */

#include "main.h"
#include "hal.h"
#include "ee.h"
#include "i2cL476.h"
#include "radio_lvl1.h"
#include "Sequences.h"
#include "pill_mgr.h"

// EEAddresses
#define EE_ADDR_DEVICE_ID       0

App_t App;
LedRGB_t Led { LED_RED_CH, LED_GREEN_CH, LED_BLUE_CH };
Vibro_t Vibro {VIBRO_PIN};

static TmrKL_t TmrEverySecond {MS2ST(1000), EVT_EVERY_SECOND, tktPeriodic};

static void ReadIDfromEE();
static uint8_t ISetID(int32_t NewID);

int main(void) {
    // ==== Setup clock frequency ====
    Clk.SetupBusDividers(ahbDiv2, apbDiv1, apbDiv1);
    Clk.UpdateFreqValues();

    // Init OS
    halInit();
    chSysInit();

    // ==== Init hardware ====
    Uart.Init(115200, UART_GPIO, UART_TX_PIN, UART_GPIO, UART_RX_PIN);

    App.InitThread();

    Led.Init();
    Vibro.Init();

//    i2c1.Init();
//    i2c2.Init();
    i2c3.Init();

//    PillMgr.Init();

    ee.Init();
    ReadIDfromEE();
    Uart.Printf("\r%S %S ID=%u\r", APP_NAME, BUILD_TIME, App.ID);
    Clk.PrintFreqs();

    TmrEverySecond.InitAndStart();

    if(Radio.Init() == OK) {
//        Vibro.StartSequence(vsqBrrBrr);
        Led.StartSequence(lsqStart);
    }
    else Led.StartSequence(lsqFailure);
    chThdSleepMilliseconds(720);

    // Main cycle
    App.ITask();
}

__attribute__ ((__noreturn__))
void App_t::ITask() {
    while(true) {
        uint32_t Evt = chEvtWaitAny(ALL_EVENTS);
        if(Evt & EVT_EVERY_SECOND) {
            if(TimeLeft_s > 0) TimeLeft_s--;
            else {
                Led.SetColor(clBlack);
                if(Vibro.GetCurrentSequence() != nullptr) Vibro.Stop();
            }
        }

        if(Evt & EVT_RADIO) {
            Color_t Clr(Radio.PktRx.R, Radio.PktRx.G, Radio.PktRx.B);
            TimeLeft_s = Radio.PktRx.TimeLeft_s;
            if(TimeLeft_s > 0) {
                Led.SetColor(Clr);
                if(Vibro.GetCurrentSequence() == nullptr) Vibro.StartSequence(vsqActive);
            }
            else {
                Led.SetColor(clBlack);
                Vibro.Stop();
            }
        }

#if 0 // ==== USB ====
        if(EvtMsk & EVTMSK_USB_READY) {
            Uart.Printf("\rUsbReady");
        }
        if(EvtMsk & EVTMSK_USB_SUSPEND) {
            Uart.Printf("\rUsbSuspend");
        }
#endif
        if(Evt & EVT_UART_NEW_CMD) {
            OnCmd((Shell_t*)&Uart);
            Uart.SignalCmdProcessed();
        }
    } // while true
}

#if 1 // ======================= Command processing ============================
void App_t::OnCmd(Shell_t *PShell) {
	Cmd_t *PCmd = &PShell->Cmd;
    __attribute__((unused)) int32_t dw32 = 0;  // May be unused in some configurations
    Uart.Printf("\r%S\r", PCmd->Name);
    // Handle command
    if(PCmd->NameIs("Ping")) PShell->Ack(OK);

    else if(PCmd->NameIs("Sig")) {
        if(PCmd->GetNextInt32(&dw32) != OK) PShell->Ack(FAILURE);
    }

    // ==== ID ====
    else if(PCmd->NameIs("GetID")) PShell->Reply("ID", App.ID);

    else if(PCmd->NameIs("SetID")) {
        if(PCmd->GetNextInt32(&dw32) != OK) { PShell->Ack(CMD_ERROR); return; }
        uint8_t r = ISetID(dw32);
        PShell->Ack(r);
    }

    else PShell->Ack(CMD_UNKNOWN);
}
#endif

#if 1 // =========================== ID management =============================
void ReadIDfromEE() {
    uint8_t R = ee.Read(EE_ADDR_DEVICE_ID, &App.ID, 1);
    if(App.ID < ID_MIN or App.ID > ID_MAX or R != OK) {
        Uart.Printf("\rUsing default ID\r");
        App.ID = ID_DEFAULT;
    }
}

uint8_t ISetID(int32_t NewID) {
    uint8_t rslt = ee.Write(EE_ADDR_DEVICE_ID, &NewID, 1);
    if(rslt == OK) {
        App.ID = NewID;
        Uart.Printf("New ID: %u\r", App.ID);
        return OK;
    }
    else {
        Uart.Printf("EE error: %u\r", rslt);
        return FAILURE;
    }
}
#endif
