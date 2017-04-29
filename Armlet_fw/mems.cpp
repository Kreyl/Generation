/*
 * mems.cpp
 *
 *  Created on: 1 мая 2016 г.
 *      Author: Kreyl
 */

#include "mems.h"
#include "uart.h"

#include "cc1101.h"
#include "radio_lvl1.h"
#include "full_state_machine.h"
#include "main.h"

FullStateMachine fullStateMachine(0);

Color_t ClrTbl[] = {
        clBlack,
        clWhite,
        clRed,
        {100, 100, 0},
        clYellow,
        clGreen,
        clMagenta,
        clBlue      // CALIBRATION
};

//static LedRGBChunk_t lsqBlink[] = {
//        {csSetup, 0, clGreen},
//        {csWait, 180},
//        {csSetup, 0, clBlack},
//        {csWait, 180},
//        {csGoto, 0}
//};

static THD_WORKING_AREA(waMemsThread, 1024);
__noreturn
static void MemsThread(void *arg) {
    chRegSetThreadName("Mems");
    Mems.ITask();
}

TmrKL_t SnsTmr(MS2ST(20), EVT_START_LISTEN, tktPeriodic);

__noreturn
void Mems_t::ITask() {
//    uint32_t PrevTime = 0;
    while(true) {
//        chThdSleepMilliseconds(16);
        chEvtWaitAny(ALL_EVENTS);
        rPkt_t IPkt;
        uint32_t Time = chVTGetSystemTimeX();
        Time = ST2MS(Time);
        IPkt.Time = Time;

//        Time = chVTGetSystemTimeX() - PrevTime;
//        PrevTime = chVTGetSystemTimeX();
//        Uart.Printf("t=%u\r", Time);

        gyroRead(IPkt.gyro);
        accRead(IPkt.acc);
        magRead(IPkt.mag);

        // Replace gyro axes
        int16_t tmp = IPkt.gyro[0];
        IPkt.gyro[0] = IPkt.gyro[1];
        IPkt.gyro[1] = -tmp;

        // Replace Mag axes
        tmp = IPkt.mag[2];
        IPkt.mag[2] = IPkt.mag[1];
        IPkt.mag[1] = tmp;

        // Add pkt to buf
        chSysLock();
        Radio.TxBuf.PutAnyway(IPkt);
        chSysUnlock();

//        float acc[3], gyro[3], mag[3];
//        for(int i=0; i<3; i++) {
//            acc[i] = IPkt.acc[i];
//            gyro[i] = IPkt.gyro[i];
//            mag[i] = IPkt.mag[i];
//        }

//        Uart.Printf("%u;   %d; %d; %d;   %d; %d; %d;   %d; %d; %d\r\n", IPkt.Time,  IPkt.gyro[0], IPkt.gyro[1], IPkt.gyro[2], IPkt.acc[0],  IPkt.acc[1],  IPkt.acc[2], IPkt.mag[0],  IPkt.mag[1],  IPkt.mag[2]);
//        uint8_t ClrN;
//        uint16_t BlinkOn, BlinkOff;
//        uint8_t VibroPwr;

//        fullStateMachine.setData(Delta, acc, gyro, mag, 0xFFFFFFFF, &ClrN, &BlinkOn, &BlinkOff, &VibroPwr);

//        if(BlinkOn != 0) {
//            lsqBlink[0].Color.Set(ClrTbl[ClrN]);
//            lsqBlink[1].Time_ms = BlinkOn;
//            lsqBlink[3].Time_ms = BlinkOff;
//            if(Led.GetCurrentSequence() == nullptr) Led.StartSequence(lsqBlink);
//        }
//        else {
//            if(Led.GetCurrentSequence() != nullptr) Led.Stop();
//            Led.SetColor(ClrTbl[ClrN]);
//        }

//        Vibro.Set(VibroPwr);

    }
}


uint8_t Mems_t::Init() {
    // Debug Pins
    PinSetupOut(GPIOB, 0, omPushPull);

    PinSetupOut(MEMS_PWR_GPIO, MEMS_PWR_PIN, omPushPull);
    On();
    chThdSleepMilliseconds(99);
//    pi2c->ScanBus();

    __unused uint8_t v=0;
    // Gyro
    gyroWriteReg(L3G_CTRL_REG4, 0x20); // 2000 dps full scale
    gyroWriteReg(L3G_CTRL_REG2, 0x00);
    gyroWriteReg(L3G_CTRL_REG3, 0x00);
    gyroWriteReg(L3G_CTRL_REG5, 0x00);
    gyroWriteReg(L3G_CTRL_REG1, 0x0F); // normal power mode, all axes enabled, 100 Hz
//    gyroReadReg(L3G_WHO_AM_I, &v);
//    Uart.Printf("gyro: %X\r", v);

    // Acc
    accWriteReg(ACC_CTRL_REG4, 0b10101000); // Block data update; FS = 10 (+/- 8 g full scale); HR = 1 (high resolution enable)
    accWriteReg(ACC_CTRL_REG1, 0b01000111); // ODR = 0100 (50 Hz ODR); LPen = 0 (normal mode); all axes enabled
//    accReadReg(ACC_CTRL_REG1, &v);
//    Uart.Printf("acc: %X\r", v);

    // Magnetometer
    magWriteReg(MAG_CRA_REG, 0b00001100); // DO = 011 (7.5 Hz ODR)
    magWriteReg(MAG_CRB_REG, 0b00100000); // GN = 001 (+/- 1.3 gauss full scale)
    magWriteReg(MAG_MR_REG,  0b00000000); // MD = 00 (continuous-conversion mode)
//    magReadReg(MAG_CRA_REG, &v);
//    Uart.Printf("mag: %X\r", v);

    // Calibrate
//    int16_t raw[3];
//    for(int i=0; i<32; i++) {
//        chThdSleepMilliseconds(20);
//        // Gyro
//        gyroReadRaw(raw);
//        GyroOffset[0] += raw[0];
//        GyroOffset[1] += raw[1];
//        GyroOffset[2] += raw[2];
//        // Acc
//        AccReadRaw(raw);
//        AccOffset[0] += raw[0];
//        AccOffset[1] += raw[1];
//        AccOffset[2] += raw[2];
//    }
//    GyroOffset[0] /= 32;
//    GyroOffset[1] /= 32;
//    GyroOffset[2] /= 32;
//    AccOffset [0] /= 32;
//    AccOffset [1] /= 32;
//    AccOffset [2] /= 32;
//    AccOffset[2] -= GRAVITY;

    // Thread
    thread_reference_t Thd = chThdCreateStatic(waMemsThread, sizeof(waMemsThread), NORMALPRIO, (tfunc_t)MemsThread, NULL);
    SnsTmr.InitAndStart(Thd);
    return 0;
}


#if 1 // ============================== Gyro ===================================
uint8_t Mems_t::gyroWriteReg(uint8_t Reg, uint8_t Value) {
    uint8_t Buf[2];
    Buf[0] = Reg;
    Buf[1] = Value;
    return pi2c->Write(L3G_I2C_ADDR, Buf, 2);
}

uint8_t Mems_t::gyroReadReg(uint8_t Reg, uint8_t *PValue) {
    return pi2c->WriteRead(L3G_I2C_ADDR, &Reg, 1, PValue, 1);
}

uint8_t Mems_t::gyroRead(int16_t *pBuf) {
    uint8_t reg = L3G_OUT_X_L | (1 << 7);   // Enable address auto-inc by setting MSB '1'
    return pi2c->WriteRead(L3G_I2C_ADDR, &reg, 1, (uint8_t*)pBuf, 6);
}
#endif

#if 1 // =============================== Acc ===================================
uint8_t Mems_t::accWriteReg(uint8_t Reg, uint8_t Value) {
    uint8_t Buf[2];
    Buf[0] = Reg;
    Buf[1] = Value;
    return pi2c->Write(ACC_I2C_ADDR, Buf, 2);
}

uint8_t Mems_t::accReadReg(uint8_t Reg, uint8_t *PValue) {
    return pi2c->WriteRead(ACC_I2C_ADDR, &Reg, 1, PValue, 1);
}

uint8_t Mems_t::accRead(int16_t *pBuf) {
    uint8_t reg = ACC_OUT_X_L | (1 << 7);   // Enable address auto-inc by setting MSB '1'
    uint8_t r = pi2c->WriteRead(ACC_I2C_ADDR, &reg, 1, (uint8_t*)pBuf, 6);
    // ?
//    pBuf[0] >>= 4;
//    pBuf[1] >>= 4;
//    pBuf[2] >>= 4;
    return r;
}
#endif

#if 1 // ========================== Magnetometer ===============================
uint8_t Mems_t::magWriteReg(uint8_t Reg, uint8_t Value) {
    uint8_t Buf[2];
    Buf[0] = Reg;
    Buf[1] = Value;
    return pi2c->Write(MAG_I2C_ADDR, Buf, 2);
}

uint8_t Mems_t::magReadReg(uint8_t Reg, uint8_t *PValue) {
    return pi2c->WriteRead(MAG_I2C_ADDR, &Reg, 1, PValue, 1);
}

uint8_t Mems_t::magRead(int16_t *pBuf) {
    uint8_t reg = MAG_OUT_X_H | (1 << 7);   // Enable address auto-inc by setting MSB '1'
    uint8_t r = pi2c->WriteRead(MAG_I2C_ADDR, &reg, 1, (uint8_t*)pBuf, 6);
    // Swap bytes in result as result is Big-Endian
    pBuf[0] = (int16_t)__REV16(pBuf[0]);
    pBuf[1] = (int16_t)__REV16(pBuf[1]);
    pBuf[2] = (int16_t)__REV16(pBuf[2]);
    return r;
}
#endif
