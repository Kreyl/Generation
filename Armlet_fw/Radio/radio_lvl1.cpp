/*
 * radio_lvl1.cpp
 *
 *  Created on: Nov 17, 2013
 *      Author: kreyl
 */

#include "radio_lvl1.h"
#include "evt_mask.h"
#include "main.h"
#include "cc1101.h"
#include "uart.h"
//#include "led.h"

#define DBG_PINS

#ifdef DBG_PINS
#define DBG_GPIO1   GPIOB
#define DBG_PIN1    0
#define DBG1_SET()  PinSetHi(DBG_GPIO1, DBG_PIN1)
#define DBG1_CLR()  PinSetLo(DBG_GPIO1, DBG_PIN1)
//#define DBG_GPIO2   GPIOB
//#define DBG_PIN2    9
//#define DBG2_SET()  PinSet(DBG_GPIO2, DBG_PIN2)
//#define DBG2_CLR()  PinClear(DBG_GPIO2, DBG_PIN2)
#else
#define DBG1_SET()
#define DBG1_CLR()
#endif

rLevel1_t Radio;

static LedRGBChunk_t lsqBlink[] = {
        {csSetup, 0, clGreen},
        {csWait, 180},
        {csSetup, 0, clBlack},
        {csWait, 180},
        {csGoto, 0}
};

#if 1 // ================================ Task =================================
static THD_WORKING_AREA(warLvl1Thread, 256);
__noreturn
static void rLvl1Thread(void *arg) {
    chRegSetThreadName("rLvl1");
    Radio.ITask();
}

__noreturn
void rLevel1_t::ITask() {
    while(true) {
        int8_t Rssi;
        Color_t Clr;
        uint8_t RxRslt = CC.ReceiveSync(7, &PktRx, &Rssi);
        if(RxRslt == OK) {
            Uart.Printf("\rRssi=%d", Rssi);

            // Blink or steady?
            if(PktRx.BlinkOn != 0) {
                lsqBlink[0].Color.Set(PktRx.R, PktRx.G, PktRx.B);
                lsqBlink[1].Time_ms = PktRx.BlinkOn;
                lsqBlink[3].Time_ms = PktRx.BlinkOff;
//                if(Led.GetCurrentSequence() == nullptr) Led.StartSequence(lsqBlink);
            }
            else {
                if(Led.GetCurrentSequence() != nullptr) Led.Stop();
//                Led.SetColor(PktRx.R, PktRx.G, PktRx.B);
            }

            Vibro.Set(PktRx.VibroPwr);
            // Send all data in queue
            while(TxBuf.GetFullCount() != 0) {
                // Get data
                chSysLock();
                rPkt_t PktTx;
                TxBuf.Get(&PktTx);
                chSysUnlock();
                DBG1_SET();
                CC.TransmitSync(&PktTx);
                DBG1_CLR();
                chThdSleepMilliseconds(1);
            } // while
        } // if rx rslt
    } // while true
}
#endif // task

#if 1 // ============================
uint8_t rLevel1_t::Init() {
#ifdef DBG_PINS
    PinSetupOut(DBG_GPIO1, DBG_PIN1, omPushPull);
//    PinSetupOut(DBG_GPIO2, DBG_PIN2, omPushPull);
#endif    // Init radioIC
    if(CC.Init() == OK) {
        CC.SetTxPower(CC_Pwr0dBm);
        CC.SetPktSize(RPKT_LEN);
        CC.SetChannel(1);
//        CC.EnterPwrDown();
        // Thread
//        PThd = chThdCreateStatic(warLvl1Thread, sizeof(warLvl1Thread), HIGHPRIO, (tfunc_t)rLvl1Thread, NULL);
        return OK;
    }
    else return FAILURE;
}
#endif
