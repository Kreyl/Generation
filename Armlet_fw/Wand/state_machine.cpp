#include "state_machine.h"
// For debug
#include "uart.h"
#include "led.h"
#include "Sequences.h"
#include "matrix.h"
#include "kl_lib.h"
extern LedRGB_t Led;

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

    float Norm = norm(heading);
    Uart.Printf("N: %f;   ", Norm);
    Uart.Printf("H: %f %f %f\r", heading[0], heading[1], heading[2]);

    if (inClaibration) {
        return CALIBRATION;
    }

//    if(Norm < 0.5) {
//        REBOOT();
//        imu.resetCalibration();
//        Led.StartOrContinue(lsqStart);
//    }
    if(Norm < 0.5) {
        imu.softReset();
        Led.StartOrRestart(lsqFailure);
    }

    return splitter.setIMUData(delta, gyro, acc, heading) + STATES_OFFSET;
}

void StateMachine::resetCalibration() {
    imu.resetCalibration();
}
