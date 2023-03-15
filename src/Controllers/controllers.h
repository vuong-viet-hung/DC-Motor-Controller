#pragma once
#include <stdint.h>


class Controller {
    float kp, ki, kd;
    float setPoint = 0;
    float previousError = 0;
    float currentError = 0;
    float cummulativeError = 0;
    float differentError = 0;
public:
    Controller(const float kp, const float ki, const float kd);
    void receiveSetPoint(const float setPoint);
    void receiveFeedback(const float feedBack);
    float sendControlSignal();
};
