#pragma once
#include <stdint.h>


class Encoder {
    uint8_t channelA, channelB;
    uint16_t pulsePerRevolution;
    int64_t pulseCount = 0;
public:
    Encoder(const uint8_t channelA, const uint8_t channelB, const uint16_t pulsePerRevolution);
    void connect();
    void updatePulseCount();
    int64_t readAngle();
};
