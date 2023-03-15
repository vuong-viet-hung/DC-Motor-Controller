#include <Arduino.h>
#include <stdint.h>
#include "MotorDrivers/motorDrivers.h"


MotorDriver::MotorDriver(
    const uint8_t enaPin, 
    const uint8_t enbPin, 
    const uint8_t inaPin, 
    const uint8_t inbPin, 
    const uint8_t incPin, 
    const uint8_t indPin
) {
    this->enaPin = enaPin;
    this->enbPin = enbPin;
    this->inaPin = inaPin;
    this->inbPin = inbPin;
    this->incPin = incPin;
    this->indPin = indPin;
};


void MotorDriver::connect() {
    pinMode(enaPin, OUTPUT);
    pinMode(enbPin, OUTPUT);
    pinMode(inaPin, OUTPUT);
    pinMode(inbPin, OUTPUT);
    pinMode(incPin, OUTPUT);
    pinMode(indPin, OUTPUT);
};


void MotorDriver::driveLeftMotor(const int16_t controlSignal) {
    if (controlSignal > 0) {
        digitalWrite(inaPin, HIGH);
        digitalWrite(inbPin, LOW);  
    }
    else {
        digitalWrite(inaPin, LOW);
        digitalWrite(inbPin, HIGH);
    }
    analogWrite(enaPin, abs(controlSignal));
};


void MotorDriver::driveRightMotor(const int16_t controlSignal) {
    if (controlSignal > 0) {
        digitalWrite(incPin, HIGH);
        digitalWrite(indPin, LOW);
    }
    else {
        digitalWrite(inaPin, LOW);
        digitalWrite(inbPin, HIGH);
    }
    analogWrite(enbPin, abs(controlSignal));
};


void MotorDriver::stopLeftMotor() {
    digitalWrite(inaPin, LOW);
    digitalWrite(inbPin, LOW);  
}


void MotorDriver::stopRightMotor() {
    digitalWrite(incPin, LOW);
    digitalWrite(indPin, LOW);
};
