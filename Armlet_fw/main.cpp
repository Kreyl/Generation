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
#include "pill_mgr.h"
#include "kl_adc.h"
#include "battery_consts.h"

#include "beeper.h"


#include "qpc.h"
#include "full_state_machine.h"

App_t App;
Mems_t Mems(&i2c1);
LedRGB_t Led { LED_RED_CH, LED_GREEN_CH, LED_BLUE_CH };
Vibro_t Vibro {VIBRO_PIN};

const PinOutput_t BatPinGnd(BAT_GND_PIN);
static TmrKL_t TmrEverySecond {MS2ST(1000), EVT_EVERY_SECOND, tktPeriodic};


static inline bool IsCharging()     { return PinIsLo(CHARGE_PIN); }
static void ReadIDfromEE();
static uint8_t ISetID(int32_t NewID);

Beeper_t Beeper {BEEPER_PIN};

LedRGBChunk_t lsqStart[] = {
        {csSetup, 0, clDarkRed},
        {csWait, 99},
        {csSetup, 0, clDarkGreen},
        {csWait, 99},
        {csSetup, 0, clDarkBlue},
        {csWait, 99},
        {csGoto, 0}
};

int main(void) {
    // ==== Setup clock frequency ====
    Clk.SetupBusDividers(ahbDiv1, apbDiv1, apbDiv1);
    Clk.SetupPllSrc(pllsrcMsi); // Required to allow PLLSAI1 for ADC clocking
    Clk.UpdateFreqValues();

    // Init OS
    halInit();
    chSysInit();

    // ==== Init hardware ====
    App.InitThread();
    Uart.Init(115200, UART_GPIO, UART_TX_PIN, UART_GPIO, UART_RX_PIN);
    Led.Init();
    Vibro.Init();
    // State pins
    PinSetupInput(USB_DETECT_PIN, pudPullDown);
    PinSetupInput(CHARGE_PIN, pudPullUp);

    Beeper.Init();

    i2c1.Init();
    i2c2.Init();
    i2c3.Init();

//    PillMgr.Init();

    ee.Init();
    ReadIDfromEE();
    Uart.Printf("\r%S %S ID=%u\r", APP_NAME, BUILD_TIME, App.ID);
    Clk.PrintFreqs();

    // Battery measurement
    Adc.Init();
    BatPinGnd.Deinit();
    PinSetupAnalog(BAT_INPUT_PIN);

    TmrEverySecond.InitAndStart();

//    if(Radio.Init() == OK) {
        Vibro.StartOrRestart(vsqBrrBrr);
//    }
//    else Led.StartSequence(lsqFailure);
    chThdSleepMilliseconds(720);

    Mems.Init();

    // Main cycle
    App.ITask();
}

__attribute__ ((__noreturn__))
void App_t::ITask() {
    bool WasCharging = false;
    while(true) {
        uint32_t Evt = chEvtWaitAny(ALL_EVENTS);
        if(Evt & EVT_EVERY_SECOND) {
            // Process charging
            if(IsCharging() and !WasCharging) {
                WasCharging = true;
                Led.StartOrContinue(lsqCharging);
            }
            else if(!IsCharging() and WasCharging) {
                WasCharging = false;
                Led.StartOrContinue(lsqChargingDone);
            }
            // Check if USB connected
            if(!UsbIsConnected()) {
                // Start battery measurement
                Adc.EnableVref();
                BatPinGnd.Init();
                BatPinGnd.SetLo();
                PinConnectAdc(BAT_INPUT_PIN);
                Adc.StartMeasurement();
            }
        } // EVT_EVERY_SECOND

#if ADC_REQUIRED
        if(Evt & EVT_ADC_DONE) {
            // Disable ADC and pins
            Adc.DisableVref();
            PinDisconnectAdc(BAT_INPUT_PIN);
            BatPinGnd.Deinit();
            // Do something with result
            if(!UsbIsConnected()) {
                uint32_t VBatAdc = Adc.GetResult(ADC_BATTERY_CHNL);
                uint32_t VRef = Adc.GetResult(ADC_VREFINT_CHNL);
                uint32_t VBat_mv = 2 * Adc.Adc2mV(VBatAdc, VRef);
                uint32_t VDDA_mv = Adc.GetVDDA(VRef);
//                Uart.Printf("adc: %u; Vref: %u; VBat: %u\r", VBatAdc, VRef, VBat_mv);
                Uart.Printf("VBat_mv: %u; VDDA: %u\r", VBat_mv, VDDA_mv);
                // Check battery
                if(VBat_mv <= BAT_END_mV) {
                    Uart.Printf("Discharged to death\r");
                    Led.StartOrRestart(lsqDischarged);
                    chThdSleepSeconds(4);
//                    Sleep::EnterStandby();
                }
                else if(VBat_mv < BAT_ZERO_mV) {
                    Led.StartOrContinue(lsqDischarged);
                }
            } // if idle
        }
#endif

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
        QEvt e;
        e.sig = SIG_MAP[dw32];
        QMSM_DISPATCH(the_hand, &e);
        QMSM_DISPATCH(the_biotics, &e);
    }

    // ==== ID ====
    else if(PCmd->NameIs("GetID")) PShell->Reply("ID", App.ID);

    else if(PCmd->NameIs("SetID")) {
        if(PCmd->GetNextInt32(&dw32) != OK) { PShell->Ack(CMD_ERROR); return; }
        uint8_t r = ISetID(dw32);
        CC.SetChannel(ID2RCHNL(App.ID));
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
