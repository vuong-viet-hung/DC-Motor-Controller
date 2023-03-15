#include <Arduino.h>
#include <stdint.h>
#include "Encoders/encoders.h"


Encoder::Encoder(const uint8_t channelA, const uint8_t channelB) {
    this->channelA = channelA;
    this->channelB = channelB;
};


void Encoder::connect() {
    pinMode(channelA, INPUT);
    pinMode(channelB, INPUT);
};


void Encoder::updatePosition() {
    bool rotatingForward = !digitalRead(channelB);
    position += (rotatingForward ? 1 : -1);
}


int64_t Encoder::readPosition() {
    return position;
}
