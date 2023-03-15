#include <Arduino.h>
#include "Controllers/controllers.h"


Controller::Controller(const float kp, const float ki, const float kd) {
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
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
    return pTerm + iTerm + dTerm;
};
