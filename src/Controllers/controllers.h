#pragma once
#include <stdint.h>


class Controller {
    float kp, ki, kd;
    float minControlSignal, maxControlSignal;
    float setPoint = 0;
    float previousError = 0;
    float currentError = 0;
    float cummulativeError = 0;
    float differentError = 0;
    float clampControlSignal(const float controlSignal);
public:
    Controller(
        const float kp, 
        const float ki, 
        const float kd, 
        const float maxControlSignal = 0, 
        const float minControlSignal = 0
    );
    void receiveSetPoint(const float setPoint);
    void receiveFeedback(const float feedBack);
    float sendControlSignal();
};
