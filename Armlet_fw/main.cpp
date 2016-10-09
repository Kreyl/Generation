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
#include "kl_adc.h"
#include "battery_consts.h"

// EEAddresses
#define EE_ADDR_DEVICE_ID       0

App_t App;
LedRGB_t Led { LED_RED_CH, LED_GREEN_CH, LED_BLUE_CH };
Vibro_t Vibro {VIBRO_PIN};
const PinOutput_t BatPinGnd(BAT_GND_PIN);

static TmrKL_t TmrEverySecond {MS2ST(1000), EVT_EVERY_SECOND, tktPeriodic};

static void ReadIDfromEE();
static uint8_t ISetID(int32_t NewID);

static inline bool UsbIsConnected() { return PinIsHi(USB_DETECT_PIN); }
static inline bool IsCharging()     { return PinIsLo(CHARGE_PIN); }

LedRGBChunk_t lsqActive[] = {
        {csSetup, 0, clYellow},
        {csEnd}
};

int main(void) {
    // ==== Setup clock frequency ====
    Clk.SetupBusDividers(ahbDiv2, apbDiv1, apbDiv1);
    Clk.SetupPllSrc(pllsrcMsi); // Required to allow PLLSAI1 for ADC clocking
    Clk.UpdateFreqValues();

    // Init OS
    halInit();
    chSysInit();

    // ==== Init hardware ====
    Uart.Init(115200, UART_GPIO, UART_TX_PIN, UART_GPIO, UART_RX_PIN);
    App.InitThread();
    Led.Init();
    Vibro.Init();
    // State pins
    PinSetupInput(USB_DETECT_PIN, pudPullDown);
    PinSetupInput(CHARGE_PIN, pudPullUp);

//    i2c1.Init();
//    i2c2.Init();
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

    if(Radio.Init() == OK) {
        Vibro.StartOrRestart(vsqBrrBrr);
        switch(App.ID) {
            case 1: Led.StartOrContinue(lsq1); break;
            case 2: Led.StartOrContinue(lsq2); break;
            case 3: Led.StartOrContinue(lsq3); break;
            case 4: Led.StartOrContinue(lsq4); break;
            default: Led.StartOrContinue(lsqStart); break;
        }
    }
    else Led.StartOrContinue(lsqFailure);
    chThdSleepMilliseconds(720);

    // Main cycle
    App.ITask();
}

__noreturn
void App_t::ITask() {
    while(true) {
        uint32_t Evt = chEvtWaitAny(ALL_EVENTS);
        if(Evt & EVT_EVERY_SECOND) {
            switch(State) {
                case stIdle:
                    // Check if USB connected
                    if(UsbIsConnected()) State = stPowered;
                    else {
                        // Start battery measurement
                        Adc.EnableVref();
                        BatPinGnd.Init();
                        BatPinGnd.Lo();
                        PinConnectAdc(BAT_INPUT_PIN);
                        Adc.StartMeasurement();
                    }
                    break;
                case stActive:
                    // Check if time to switch indication off
                    if(TimeLeft_s > 0) TimeLeft_s--;
                    else {
                        Led.Stop();
                        Vibro.Stop();
                        State = stIdle;
                    }
                    break;
                case stPowered:
                    // Check if still connected
                    if(UsbIsConnected()) {
                        // Check if charging
                        if(IsCharging()) Led.StartOrContinue(lsqCharging);
                        else Led.StartOrContinue(lsqChargingDone);
                    }
                    else {  // Disconnected
                        Led.Stop();
                        State = stIdle;
                    }
                    break;
            } // switch
        } // EVT_EVERY_SECOND

        if(Evt & EVT_RADIO) {
            if(State == stIdle) {
                TimeLeft_s = Radio.PktRx.TimeLeft_s;
                if(TimeLeft_s > 0) {
                    lsqActive[0].Color.FromRGB(Radio.PktRx.R, Radio.PktRx.G, Radio.PktRx.B);
                    Led.StartOrRestart(lsqActive);   // always set new color
                    Vibro.StartOrRestart(vsqActive);
                    State = stActive;
                }
            } // if Idle
        }

#if ADC_REQUIRED
        if(Evt & EVT_ADC_DONE) {
            // Disable ADC and pins
            Adc.DisableVref();
            PinDisconnectAdc(BAT_INPUT_PIN);
            BatPinGnd.Deinit();
            // Do something with result
            if(State == stIdle) {
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
                    Sleep::EnterStandby();
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
