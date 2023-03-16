#include <Arduino.h>
#include <stdint.h>
#include "Encoders/encoders.h"


Encoder::Encoder(const uint8_t channelA, const uint8_t channelB, uint16_t pulsePerRevolution) {
    this->channelA = channelA;
    this->channelB = channelB;
    this->pulsePerRevolution = pulsePerRevolution;
};


void Encoder::connect() {
    pinMode(channelA, INPUT);
    pinMode(channelB, INPUT);
};


void Encoder::updatePulseCount() {
    bool rotatingForward = !digitalRead(channelB);
    pulseCount += (rotatingForward ? 1 : -1);
}


int64_t Encoder::readAngle() {
    return pulseCount * 360 / pulsePerRevolution;
}
