/*
 * main.cpp
 *
 *  Created on: 20 февр. 2014 г.
 *      Author: g.kruglov
 */

#include "main.h"
#include "hal.h"
#include "ee.h"
#include "mems.h"
#include "i2cL476.h"
#include "radio_lvl1.h"
#include "Sequences.h"
#include "full_state_machine.h"

App_t App;
Mems_t Mems(&i2c1);
LedRGB_t Led { LED_RED_CH, LED_GREEN_CH, LED_BLUE_CH };
Vibro_t Vibro {VIBRO_PIN};

int main(void) {
    // ==== Setup clock frequency ====
#if RADIO_ENABLED
    Clk.SetHiPerfMode();
#endif
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

    i2c1.Init();
    i2c3.Init();

    ee.Init();
    ee.On();

    Mems.Init();
#if RADIO_ENABLED
    if(Radio.Init() == OK) {
        Led.StartSequence(lsqStart);
        Vibro.StartSequence(vsqBrr);
    }
    else Led.StartSequence(lsqFailure);
    chThdSleepMilliseconds(1800);
#endif

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

    else if(PCmd->NameIs("CalG")) Mems.SetState(mstCalG);

    else if(PCmd->NameIs("CalA1")) Mems.SetState(mstCalA1);
    else if(PCmd->NameIs("CalA2")) Mems.SetState(mstCalA2);
    else if(PCmd->NameIs("CalA3")) Mems.SetState(mstCalA3);
    else if(PCmd->NameIs("CalA4")) Mems.SetState(mstCalA4);
    else if(PCmd->NameIs("CalA5")) Mems.SetState(mstCalA5);
    else if(PCmd->NameIs("CalA6")) Mems.SetState(mstCalA6);

    else PShell->Ack(CMD_UNKNOWN);
}
#endif
