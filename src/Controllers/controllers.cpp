#include <Arduino.h>
#include "Controllers/controllers.h"


Controller::Controller(
    const float kp, 
    const float ki, 
    const float kd,
    const float minControlSignal = 0,
    const float maxControlSignal = 0
) {
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
    this->minControlSignal = minControlSignal;
    this->maxControlSignal = maxControlSignal;
}


void Controller::receiveSetPoint(const float setPoint) {
    this->setPoint = setPoint;
};


void Controller::receiveFeedback(const float feedback) {
    previousError = currentError;
    currentError = setPoint - feedback;
    cummulativeError += currentError;
    differentError = currentError - previousError;
};


float Controller::sendControlSignal() {
    float pTerm = kp * currentError;
    float iTerm = ki * cummulativeError;
    float dTerm = kd * differentError;
    float controlSignal = pTerm + iTerm + dTerm;
    return clampControlSignal(controlSignal);
};


float Controller::clampControlSignal(float controlSignal) {
    bool maxControlSignalSet = maxControlSignal != 0;
    if (controlSignal > 0) {
        controlSignal = max(controlSignal, minControlSignal);
        if (maxControlSignalSet) {
            controlSignal = min(controlSignal, maxControlSignal);
        }
    }
    else {
        controlSignal = min(controlSignal, -minControlSignal);
        if (maxControlSignalSet) {
            controlSignal = max(controlSignal, -maxControlSignal);
        }
    }
    return controlSignal;
}
