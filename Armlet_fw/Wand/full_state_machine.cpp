#include "full_state_machine.h"
//#include "extern_sm/service.h"
#include "extern_sm/generation_light.h"
#include "knowledge.h"
#include <stdio.h>
#include "board.h"

#include "led.h"
#include "Sequences.h"

extern void DbgBeep(uint32_t Indx);
extern void DbgVibro(uint32_t Indx);

FullStateMachine::FullStateMachine(int axis) : innerMachine(axis) {
    innerTimer = 0;
}

bool FullStateMachine::setData(const float delta,
    const float acc[DIMENTION], const float gyro[DIMENTION], const float mag[DIMENTION])
{
    int innerState = innerMachine.setData(delta, acc, gyro, mag);

    if (innerState == CALIBRATION) {
        return false;
    } else {
        if(Led.GetCurrentSequence() == lsqStart) Led.Stop();
        QEvt e;
        if (innerState > IDLE) {
            switch(innerState) {
                case 2: e.sig = I_SIG; break;
                case 3: e.sig = II_SIG; break;
                case 4: e.sig = III_SIG; break;
                case 5: e.sig = IV_SIG; break;
                default: break;
            }
//            e.sig = SIG_MAP[0];//innerState - STATES_OFFSET];
#if DEBUG_OTK
//            DbgBeep(innerState - STATES_OFFSET);
            DbgVibro(innerState - STATES_OFFSET);
#endif
            QMSM_DISPATCH(the_hand, &e);
            QMSM_DISPATCH(the_biotics, &e);
        }

        innerTimer += (uint16_t) (delta * 1000);
        if (innerTimer > EXTERN_TICK_MS) {
            e.sig = TICK_SEC_SIG;
            QMSM_DISPATCH(the_biotics, &e);
            QMSM_DISPATCH(the_hand, &e);
        }

        innerTimer %= EXTERN_TICK_MS;
    }
    return true;
}

void FullStateMachine::resetCalibration() {
    innerMachine.resetCalibration();
}
