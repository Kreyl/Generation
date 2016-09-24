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

App_t App;
LedRGB_t Led { LED_RED_CH, LED_GREEN_CH, LED_BLUE_CH };
Vibro_t Vibro {VIBRO_PIN};

int main(void) {
    // ==== Setup clock frequency ====
    Clk.SetupBusDividers(ahbDiv2, apbDiv1, apbDiv1);
    Clk.UpdateFreqValues();

    // Init OS
    halInit();
    chSysInit();

    // ==== Init hardware ====
    Uart.Init(115200, UART_GPIO, UART_TX_PIN, UART_GPIO, UART_RX_PIN);
    Uart.Printf("\r%S %S\r", APP_NAME, BUILD_TIME);
    Clk.PrintFreqs();

    App.InitThread();

    Led.Init();
    Vibro.Init();

//    i2c1.Init();
//    i2c2.Init();
//    i2c3.Init();

//    PillMgr.Init();

//    ee.Init();
//    ee.On();

    if(Radio.Init() == OK) {
        Vibro.StartSequence(vsqBrrBrr);
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

    else PShell->Ack(CMD_UNKNOWN);
}
#endif
