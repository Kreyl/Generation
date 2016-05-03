/*
 * main.cpp
 *
 *  Created on: 20 ����. 2014 �.
 *      Author: g.kruglov
 */

#include "main.h"
#include "hal.h"
#include "math.h"
#include "mems.h"
#include "i2cL476.h"

App_t App;

//const I2CConfig I2C3Cfg = { 0xE14, 0, 0 }; // 0xE14 timing generated by CubeMX for 100kHz @ 4MHz


int main(void) {
    // ==== Setup clock frequency ====
    __unused uint8_t ClkResult = 1;
//    Clk.SetupFlashLatency(64);  // Setup Flash Latency for clock in MHz
//    Clk.EnablePrefetch();
//    // 12 MHz/6 = 2; 2*192 = 384; 384/6 = 64 (preAHB divider); 384/8 = 48 (USB clock)
//    Clk.SetupPLLDividers(6, 192, pllSysDiv6, 8);
//    // 64/1 = 64 MHz core clock. APB1 & APB2 clock derive on AHB clock; APB1max = 42MHz, APB2max = 84MHz
//    // Keep APB freq at 32 MHz to left peripheral settings untouched
//    Clk.SetupBusDividers(ahbDiv1, apbDiv2, apbDiv2);
//    if((ClkResult = Clk.SwitchToPLL()) == 0) Clk.HSIDisable();
    Clk.UpdateFreqValues();

    // Init OS
    halInit();
    chSysInit();

    // ==== Init hardware ====
    Uart.Init(115200, UART_GPIO, UART_TX_PIN, UART_GPIO, UART_RX_PIN);
    Uart.Printf("\r%S %S\r", APP_NAME, BUILD_TIME);
    Clk.PrintFreqs();
//    if(ClkResult != 0) Uart.Printf("\rXTAL failure");

    App.InitThread();

    PinSetupOut(GPIOC, 2, omPushPull, pudNone);
    PinSet(GPIOC, 2);   // Power up EEPROM
    PinSetupAlterFunc(GPIOC, 0, omOpenDrain, pudNone, AF4);
    PinSetupAlterFunc(GPIOC, 1, omOpenDrain, pudNone, AF4);

    chThdSleepMilliseconds(99);

    i2c3.Init();
//    i2c3.ScanBus();

    uint8_t txbuf[16] = {1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4};
    uint8_t rxBuf[9];

    uint8_t r = i2c3.WriteRead(0x50, txbuf, 1, rxBuf, 9);
    if(r == OK) Uart.Printf("%A\r", rxBuf, 9, ' ');
    else Uart.Printf("rslt=%u\r", r);

//    i2cInit();  // Init all I2C channels
//    i2cStart(&I2CD3, &I2C3Cfg);
//
//    msg_t r;
//    r = i2cMasterTransmitTimeout(&I2CD3, 0x50, txbuf, 1, rxBuf, 9, MS2ST(999));
//
//    Uart.Printf("r=%d; %A\r", r, rxBuf, 9, ' ');
//    Uart.Printf("r=%d\r", r);


    Mems.Init();

    // Main cycle
    App.ITask();
}

__attribute__ ((__noreturn__))
void App_t::ITask() {
    while(true) {
        uint32_t EvtMsk = chEvtWaitAny(ALL_EVENTS);
#if 0 // ==== USB ====
        if(EvtMsk & EVTMSK_USB_READY) {
            Uart.Printf("\rUsbReady");
        }
        if(EvtMsk & EVTMSK_USB_SUSPEND) {
            Uart.Printf("\rUsbSuspend");
        }
#endif
        if(EvtMsk & EVTMSK_UART_NEW_CMD) {
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

    else PShell->Ack(CMD_UNKNOWN);
}
#endif
