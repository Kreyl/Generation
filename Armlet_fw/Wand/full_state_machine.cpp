#include "full_state_machine.h"
#include "service.h"
#include "generation_light.h"
#include "knowledge.h"

#include "uart.h"
#include "led.h"
#include "Sequences.h"

extern LedRGB_t Led;

FullStateMachine::FullStateMachine(int axis) : innerMachine(axis) {
    innerTimer = 0;
}

bool FullStateMachine::setData(const float delta,
    const float acc[DIMENTION], const float gyro[DIMENTION], const float mag[DIMENTION])
{
    int innerState = innerMachine.setData(delta, acc, gyro, mag);

//    Uart.Printf("IS: %d\r", innerState);

    if (innerState == CALIBRATION) {
        return false;
    } else {
        if(Led.GetCurrentSequence() == lsqStart) Led.Stop();
        QEvt e;
        if (innerState > IDLE) {
            e.sig = SIG_MAP[innerState - STATES_OFFSET];
            QMSM_DISPATCH(the_hand, &e);
            QMSM_DISPATCH(the_biotics, &e);
        }

        innerTimer += (uint16_t) (delta * 1000);
        if (innerTimer > EXTERN_TICK_MS) {
            e.sig = TICK_SEC_SIG;
            QMSM_DISPATCH(the_hand, &e);
            QMSM_DISPATCH(the_biotics, &e);
        }

        innerTimer %= EXTERN_TICK_MS;
    }
    return true;
}
