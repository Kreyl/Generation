/*
 * mems.cpp
 *
 *  Created on: 1 ��� 2016 �.
 *      Author: Kreyl
 */

#include "mems.h"
#include "uart.h"

#include "cc1101.h"
#include "radio_lvl1.h"
//#include "state_machine.h"
#include "full_state_machine.h"
#include "main.h"

#include "qpc.h"
#include "biotics.h"

#include "Sequences.h"

/*
#include "beeper.h"

extern Beeper_t Beeper;

void DbgBeep(uint32_t Indx) {
    switch(Indx) {
        case 0: Beeper.StartOrRestart(bsqCharge); break;
        case 1: Beeper.StartOrRestart(bsqThrow); break;
        case 2: Beeper.StartOrRestart(bsqPunch); break;
        case 3: Beeper.StartOrRestart(bsqLift); break;
        case 4: Beeper.StartOrRestart(bsqWarp); break;
        case 5: Beeper.StartOrRestart(bsqBarrier); break;
        case 6: Beeper.StartOrRestart(bsqCleanse); break;
        case 7: Beeper.StartOrRestart(bsqSingular); break;
        case 8: Beeper.StartOrRestart(bsqSong); break;
        case 9: Beeper.StartOrRestart(bsqRelease); break;
        case 10: Beeper.StartOrRestart(bsqPwrRelease); break;
        default: break;
    }
}

void DbgVibro(uint32_t Indx) {
    switch(Indx) {
        case 0: Vibro.StartOrRestart(vsqCharge); break;
        case 1: Vibro.StartOrRestart(vsqThrow); break;
        case 2: Vibro.StartOrRestart(vsqPunch); break;
        case 3: Vibro.StartOrRestart(vsqLift); break;
        case 4: Vibro.StartOrRestart(vsqWarp); break;
        case 5: Vibro.StartOrRestart(vsqBarrier); break;
        case 6: Vibro.StartOrRestart(vsqCleanse); break;
        case 7: Vibro.StartOrRestart(vsqSingular); break;
        case 8: Vibro.StartOrRestart(vsqSong); break;
        case 9: Vibro.StartOrRestart(vsqRelease); break;
        case 10: Vibro.StartOrRestart(vsqPwrRelease); break;
        default: break;
    }
}
*/

void LoadGyroCal(int32_t *Offset);
void LoadAccCal(int32_t *Offset);
void SaveGyroCal(int32_t *Offset);
void SaveAccCal(int32_t *Offset);

//StateMachine stateMachine(0);
FullStateMachine fullStateMachine(0);

static THD_WORKING_AREA(waMemsThread, 8192);
__noreturn
static void MemsThread(void *arg) {
    chRegSetThreadName("Mems");
    Mems.ITask();
}

__noreturn
void Mems_t::ITask() {
    uint32_t PrevTime = 0;
//    int n=0;

    while(true) {
        chThdSleepMilliseconds(5);
        rPkt_t IPkt;
        IPkt.Time = chVTGetSystemTime() / 10;
        uint32_t tmp32 = IPkt.Time - PrevTime;
        float Delta = tmp32;
        Delta /= 1000;

        PrevTime = IPkt.Time;
        // Read raw data
        gyroRead(IPkt.gyro);
        accRead(IPkt.acc);
        magRead(IPkt.mag);
        // Replace gyro axes
        int16_t tmp = IPkt.gyro[0];
        IPkt.gyro[0] = IPkt.gyro[1];
        IPkt.gyro[1] = -tmp;

        // Add pkt to buf
//        Radio.TxBuf.PutAnyway(IPkt);

        // Make 3 arrays for state machine
        Vector acc(IPkt.acc[0], IPkt.acc[1], IPkt.acc[2]);
        Vector gyro(IPkt.gyro[0], IPkt.gyro[1], IPkt.gyro[2]);
        Vector mag(IPkt.mag[0], IPkt.mag[1], IPkt.mag[2]);

        // Do calibration if needed
        switch(State) {
            case mstCalG:
                GyroOffset[0] += IPkt.gyro[0];
                GyroOffset[1] += IPkt.gyro[1];
                GyroOffset[2] += IPkt.gyro[2];
                CalCounter++;
//                Uart.Printf("%d; %d; %d\r", GyroOffset[0], GyroOffset[1], GyroOffset[2]);
                if(CalCounter >= GYRO_CAL_CNT) {
                    GyroOffset[0] /= CalCounter;
                    GyroOffset[1] /= CalCounter;
                    GyroOffset[2] /= CalCounter;
                    State = mstNormal;
                    SaveGyroCal(GyroOffset);
                    Uart.PrintfI("Gyro calibration done: %d %d %d\r", GyroOffset[0], GyroOffset[1], GyroOffset[2]);
                }
                break;

            case mstCalA1:
            case mstCalA2:
            case mstCalA3:
            case mstCalA4:
            case mstCalA5:
            case mstCalA6:
                AccOffset[0] += IPkt.acc[0];
                AccOffset[1] += IPkt.acc[1];
                AccOffset[2] += IPkt.acc[2];
                CalCounter++;
                if(CalCounter >= ACC_CAL_CNT) {
                    if(State == mstCalA6) {
                        AccOffset[0] /= (CalCounter * 6);
                        AccOffset[1] /= (CalCounter * 6);
                        AccOffset[2] /= (CalCounter * 6);
                        SaveAccCal(AccOffset);
                        Uart.PrintfI("Acc calibration done: %d %d %d\r", AccOffset[0], AccOffset[1], AccOffset[2]);
                        State = mstNormal;
                    }
                    else {
                        Uart.PrintfI("Acc phase done: %d %d %d\r", AccOffset[0], AccOffset[1], AccOffset[2]);
                        State = mstIntermediate;
                    }
                }
                break;

            case mstNormal:
                fullStateMachine.setData(Delta, acc, gyro, mag);
                break;

            default: break;
        } // switch

//        if(n-- == 0) {
//            n = 11;
//            Uart.Printf("%u;   %d; %d; %d;   %d; %d; %d;   %d; %d; %d\r\n", IPkt.Time,  IPkt.gyro[0], IPkt.gyro[1], IPkt.gyro[2], IPkt.acc[0],  IPkt.acc[1],  IPkt.acc[2], IPkt.mag[0],  IPkt.mag[1],  IPkt.mag[2]);
//        }
    }
}

uint8_t Mems_t::Init() {
    PinSetupOut(MEMS_PWR_GPIO, MEMS_PWR_PIN, omPushPull);
//    pi2c->ScanBus();
    for(int n=0; n<4; n++) {
        __unused uint8_t v;
        Uart.Printf("AccGyro Init: %u\r", n);
        pi2c->Standby();
        Off();
        chThdSleepMilliseconds(99);
        On();
        pi2c->Resume();
        chThdSleepMilliseconds(99);
        // Gyro
        gyroWriteReg(L3G_CTRL_REG4, 0x20); // 2000 dps full scale
        gyroWriteReg(L3G_CTRL_REG2, 0x00);
        gyroWriteReg(L3G_CTRL_REG3, 0x00);
        gyroWriteReg(L3G_CTRL_REG5, 0x00);
        gyroWriteReg(L3G_CTRL_REG1, 0x0F); // normal power mode, all axes enabled, 100 Hz
    //    gyroReadReg(L3G_WHO_AM_I, &v);
    //    Uart.Printf("gyro: %X\r", v);

        // Acc
        accWriteReg(ACC_CTRL_REG4, 0b00101000); // FS = 10 (+/- 8 g full scale); HR = 1 (high resolution enable)
        accWriteReg(ACC_CTRL_REG1, 0b01000111); // ODR = 0100 (50 Hz ODR); LPen = 0 (normal mode); all axes enabled
//        int16_t a[3];
//        accRead(a);
//        Uart.Printf("Acc: %d %d %d\r", a[0], a[1], a[2]);

//        accReadReg(ACC_CTRL_REG1, &v);
//        Uart.Printf("acc: %X\r", v);

        // Magnetometer
        magWriteReg(MAG_CRA_REG, 0b00001100); // DO = 011 (7.5 Hz ODR)
        magWriteReg(MAG_CRB_REG, 0b00100000); // GN = 001 (+/- 1.3 gauss full scale)
        magWriteReg(MAG_MR_REG,  0b00000000); // MD = 00 (continuous-conversion mode)
    } // for

    Biotics_ctor();
    QMSM_INIT(the_biotics, (QEvt *)0);
    Hand_ctor();
    QMSM_INIT(the_hand, (QEvt *)0);

    QEvt e;
    e.sig = MAX_PILL_SIG;
    QMSM_DISPATCH(the_hand, &e);
    QMSM_DISPATCH(the_biotics, &e);

    BIO_set_to_short(5);
    BIO_set_to_long(3);

    LoadGyroCal(GyroOffset);
    LoadAccCal(AccOffset);
    fullStateMachine.init();

    Led.StartOrContinue(lsqStart);    // Show Calibration Ongoing

//    DebugSM = 0;
//    QEvt e;
//    e.sig = MAX_PILL_SIG;
//    QMSM_DISPATCH(the_hand, &e);

    // Thread
    chThdCreateStatic(waMemsThread, sizeof(waMemsThread), NORMALPRIO, (tfunc_t)MemsThread, NULL);
    return 0;
}

Vector getGOffset() {
    return Vector((float)Mems.GyroOffset[0], (float)Mems.GyroOffset[1], (float)Mems.GyroOffset[2]);
}
Vector getAOffset() {
    return Vector((float)Mems.AccOffset[0], (float)Mems.AccOffset[1], (float)Mems.AccOffset[2]);
}
Vector getMOffset() {
    return Vector();
}

void onCalibrationDone() {
    Led.Stop();
}

void Mems_t::SetState(MemsState_t NewState) {
    chSysLock();
    State = NewState;
    CalCounter = 0;
    switch(State) {
        case mstCalG:
            Uart.PrintfI("Gyro calibration...\r");
            GyroOffset[0] = 0;
            GyroOffset[1] = 0;
            GyroOffset[2] = 0;
            break;

        case mstCalA1:
            Uart.PrintfI("Acc calibration phase1...\r");
            AccOffset[0] = 0;
            AccOffset[1] = 0;
            AccOffset[2] = 0;
            break;

        case mstCalA2:
            Uart.PrintfI("Acc calibration phase2...\r");
            break;
        case mstCalA3:
            Uart.PrintfI("Acc calibration phase3...\r");
            break;
        case mstCalA4:
            Uart.PrintfI("Acc calibration phase4...\r");
            break;
        case mstCalA5:
            Uart.PrintfI("Acc calibration phase5...\r");
            break;
        case mstCalA6:
            Uart.PrintfI("Acc calibration phase6...\r");
            break;

        default: break;
    }
    chSysUnlock();
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
    return pi2c->WriteRead(ACC_I2C_ADDR, &reg, 1, (uint8_t*)pBuf, 6);
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
