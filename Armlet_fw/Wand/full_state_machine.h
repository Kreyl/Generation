#ifndef FullStateMachine_h
#define FullStateMachine_h

#include <stdint.h>

#include "state_machine.h"
#include "extern_sm/generation_light.h"

#define EXTERN_TICK_MS 1000

const uint8_t SIG_MAP[STROKES_COUNT] =  {
    I_SIG,
    II_SIG,
    III_SIG,
    IV_SIG
};

class FullStateMachine {
private:
    StateMachine innerMachine;
    uint16_t innerTimer;
public:

    FullStateMachine(int axis);
    bool setData(const float delta,
        const float acc[DIMENTION], const float gyro[DIMENTION], const float mag[DIMENTION]);

    void resetCalibration();
};
#endif
