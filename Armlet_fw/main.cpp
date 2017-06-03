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
static void ReadAbilityFromEE();
static void WriteAbilityToEE();

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
    Clk.SetupBusDividers(ahbDiv2, apbDiv1, apbDiv1);
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

//    ee.Init();
//    ReadIDfromEE();

    Uart.Printf("\r%S %S ID=%u\r", APP_NAME, BUILD_TIME, App.ID);
    Clk.PrintFreqs();

    // Battery measurement
//    Adc.Init();
//    BatPinGnd.Deinit();
//    PinSetupAnalog(BAT_INPUT_PIN);

//    TmrEverySecond.InitAndStart();

    if(Radio.Init() == OK) {
        Vibro.StartOrRestart(vsqBrrBrr);
    }
//    else Led.StartSequence(lsqFailure);
    chThdSleepMilliseconds(720);

    Mems.Init();
//    ReadAbilityFromEE();

    // Main cycle
    App.ITask();
}

__attribute__ ((__noreturn__))
void App_t::ITask() {
    bool UsbWasConnected = false;
    int32_t DischargedIndicationTimeout_s = DISCHARGED_INDICATION_PERIOD_S;
    while(true) {
        uint32_t Evt = chEvtWaitAny(ALL_EVENTS);
//        if(Evt & EVT_EVERY_SECOND) {
//            if(UsbIsConnected()) {
//                UsbWasConnected = true;
//                // Process charging
//                if(IsCharging()) {
//                    Led.StartOrContinue(lsqCharging);
//                    Uart.Printf("Connected and charging\r");
//                }
//                else {
//                    Led.StartOrContinue(lsqChargingDone);
//                    Uart.Printf("Connected, not charging\r");
//                }
//            } // if(UsbIsConnected()
//            else {
//                if(UsbWasConnected) {
//                    UsbWasConnected = false;
//                    Led.Stop();
//                    Uart.Printf("Disconnected\r");
//                }
//                // Start battery measurement
//                Adc.EnableVref();
//                BatPinGnd.Init();
//                BatPinGnd.SetLo();
//                PinConnectAdc(BAT_INPUT_PIN);
//                Adc.StartMeasurement();
//            }
//        } // EVT_EVERY_SECOND

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
//                uint32_t VDDA_mv = Adc.GetVDDA(VRef);
//                Uart.Printf("adc: %u; Vref: %u; VBat: %u\r", VBatAdc, VRef, VBat_mv);
                Uart.Printf("VBat_mv: %u\r", VBat_mv);
                // Check battery
                if(VBat_mv <= BAT_END_mV) {
//                    Uart.Printf("Discharged to death\r");
//                    Led.StartOrContinue(lsqDischarged);
//                    chThdSleepSeconds(4);
//                    Sleep::EnterStandby();
                }
                else if(VBat_mv < BAT_ZERO_mV) {
//                    Uart.Printf("Discharged %d\r", DischargedIndicationTimeout_s);
                    DischargedIndicationTimeout_s--;
                    if(DischargedIndicationTimeout_s <= 0) {
                        if(!Vibro.IsBusy()) {
                            DischargedIndicationTimeout_s = DISCHARGED_INDICATION_PERIOD_S;
                            Vibro.StartOrRestart(vsqDischarged);
                        }
                    }
//                    Led.StartOrContinue(lsqDischarged);
                }
            } // if idle
        }
#endif

#if 0 // ==== Pill ====
        if(Evt & EVT_PILL_CONNECTED) {
            Uart.Printf("Pill: %d; %X\r", PillMgr.Pill.TypeInt32, PillMgr.Pill.AbilityID);
            if(PillMgr.Pill.Type == pilltypeAbility) {
                uint32_t AbId = PillMgr.Pill.AbilityID; // To make things shorter
                bool HasChanged = true;
                switch(AbId) {
                    case PUNCH_PILL_SIG:       AbilityMsk |= 0x001; break;
                    case PUNCH_PWR_PILL_SIG:   AbilityMsk |= 0x002; break;
                    case LIFT_PILL_SIG:        AbilityMsk |= 0x004; break;
                    case LIFT_PWR_PILL_SIG:    AbilityMsk |= 0x008; break;
                    case WARP_PILL_SIG:        AbilityMsk |= 0x010; break;
                    case WARP_PWR_PILL_SIG:    AbilityMsk |= 0x020; break;
                    case CLEANSE_PILL_SIG:     AbilityMsk |= 0x040; break;
                    case BARRIER_PILL_SIG:     AbilityMsk |= 0x080; break;
                    case SINGULARITY_PILL_SIG: AbilityMsk |= 0x100; break;
                    case SONG_PILL_SIG:        AbilityMsk |= 0x200; break;
                    // PillReset
                    case DEFAULT_PILL_SIG:     AbilityMsk = 0; break;
                    // Pill EnableAll
                    case MAX_PILL_SIG:         AbilityMsk = 0x3FF; break;
                    default: HasChanged = false; break;
                }
                if(HasChanged) {
                    WriteAbilityToEE();
                    QEvt e;
                    e.sig = AbId;
                    QMSM_DISPATCH(the_hand, &e);
                    Vibro.StartOrRestart(vsqBrrBrr);
                }
                Uart.Printf("AbilityMsk: %X\r", App.AbilityMsk);
            } // if(PillMgr.Pill.Type == pilltypeAbility) {
        }
        if(Evt & EVT_PILL_DISCONNECTED) {
            Uart.Printf("Pill Discon\r");
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
//        CC.SetChannel(ID2RCHNL(App.ID));
        PShell->Ack(r);
    }

#if 1 // ==== Pills ====
    else if(PCmd->NameIs("PillRead32")) {
        int32_t Cnt = 0;
        if(PCmd->GetNextInt32(&Cnt) != OK) { PShell->Ack(CMD_ERROR); return; }
        uint8_t MemAddr = 0, b = OK;
        PShell->Printf("#PillData32 ");
        for(int32_t i=0; i<Cnt; i++) {
            b = PillMgr.Read(MemAddr, &dw32, 4);
            if(b != OK) break;
            PShell->Printf("%d ", dw32);
            MemAddr += 4;
        }
        Uart.Printf("\r\n");
        PShell->Ack(b);
    }

    else if(PCmd->NameIs("PillWrite32")) {
        uint8_t b = CMD_ERROR;
        uint8_t MemAddr = 0;
        // Iterate data
        while(true) {
            if(PCmd->GetNextInt32(&dw32) != OK) break;
//            Uart.Printf("%X ", Data);
            b = PillMgr.Write(MemAddr, &dw32, 4);
            if(b != OK) break;
            MemAddr += 4;
        } // while
        Uart.Ack(b);
    }

//    else if(PCmd->NameIs("#PillRepeatWrite32") and (Type == dtPillFlasher)) {
//        uint32_t PillAddr;
//        if(PCmd->TryConvertTokenToNumber(&PillAddr) == OK) {
//            if((PillAddr >= 0) and (PillAddr <= 7)) {
//                b = OK;
//                Data2Wr.Sz32 = 0;
//                for(uint32_t i=0; i<PILL_SZ32; i++) Data2Wr.Data[i] = 0;
//                // Iterate data
//                for(uint32_t i=0; i<PILL_SZ32; i++) {
//                    if(PCmd->GetNextToken() != OK) break;   // Get next data to write, get out if end
//                    //Uart.Printf("%S\r", PCmd->Token);
//                    b = PCmd->TryConvertTokenToNumber(&Data2Wr.Data[i]);
//                    if(b == OK) Data2Wr.Sz32++;
//                    else break; // Token is NAN
//                } // while
//                // Save data to EEPROM
//                if(b == OK) b = EE.WriteBuf(&Data2Wr, sizeof(Data2Wr), EE_REPDATA_ADDR);
//                Uart.Ack(b);
//                // Write pill immediately if connected
//                if(PillMgr.CheckIfConnected(PILL_I2C_ADDR) == OK) App.OnPillConnect();
//                return;
//            } // if pill addr ok
//        } // if pill addr
//        Uart.Ack(CMD_ERROR);
//    }
#endif // Pills

    // Calibration
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

#if 1 // ======================== Ability Load/Save ============================

void ReadAbilityFromEE() {
    ee.Read(EE_ADDR_ABILITY, &App.AbilityMsk, 4);
    Uart.Printf("AbilityMsk: %X\r", App.AbilityMsk);
    QEvt e;
    if(App.AbilityMsk & 0x001) { e.sig = PUNCH_PILL_SIG; QMSM_DISPATCH(the_hand, &e); }
    if(App.AbilityMsk & 0x002) { e.sig = PUNCH_PWR_PILL_SIG; QMSM_DISPATCH(the_hand, &e); }
    if(App.AbilityMsk & 0x004) { e.sig = LIFT_PILL_SIG; QMSM_DISPATCH(the_hand, &e); }
    if(App.AbilityMsk & 0x008) { e.sig = LIFT_PWR_PILL_SIG; QMSM_DISPATCH(the_hand, &e); }
    if(App.AbilityMsk & 0x010) { e.sig = WARP_PILL_SIG; QMSM_DISPATCH(the_hand, &e); }
    if(App.AbilityMsk & 0x020) { e.sig = WARP_PWR_PILL_SIG; QMSM_DISPATCH(the_hand, &e); }
    if(App.AbilityMsk & 0x040) { e.sig = CLEANSE_PILL_SIG; QMSM_DISPATCH(the_hand, &e); }
    if(App.AbilityMsk & 0x080) { e.sig = BARRIER_PILL_SIG; QMSM_DISPATCH(the_hand, &e); }
    if(App.AbilityMsk & 0x100) { e.sig = SINGULARITY_PILL_SIG; QMSM_DISPATCH(the_hand, &e); }
    if(App.AbilityMsk & 0x200) { e.sig = SONG_PILL_SIG; QMSM_DISPATCH(the_hand, &e); }
}

void WriteAbilityToEE() {
    ee.Write(EE_ADDR_ABILITY, &App.AbilityMsk, 4);
}
#endif
