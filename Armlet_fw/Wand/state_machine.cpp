#include "state_machine.h"
#include "matrix.h"
#include "main.h"
#include "Sequences.h"

StateMachine::StateMachine(int axis) {
    this->axis = axis;
}


int StateMachine::setData(const float delta,
    const float accIn[DIMENTION], const float gyroIn[DIMENTION], const float magIn[DIMENTION])
{
    bool inClaibration;
    float gyro;
    float acc[DIMENTION];
    float heading[DIMENTION];

    inClaibration = imu.calc(delta, accIn, gyroIn, magIn, axis, &gyro, acc, heading);

    if (inClaibration) {
        return CALIBRATION;
    }

    float Norm = norm(heading);

    if(Norm < 0.5) {
        imu.softReset();
        Led.StartOrRestart(lsqFailure);
    }

    return splitter.setIMUData(delta, gyro, acc, heading) + STATES_OFFSET;
}

void StateMachine::resetCalibration() {
    imu.resetCalibration();
}
