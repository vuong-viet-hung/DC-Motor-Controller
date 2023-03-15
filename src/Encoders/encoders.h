#pragma once
#include <stdint.h>


class Encoder {
    uint8_t channelA, channelB;
    int64_t position = 0;
public:
    Encoder(const uint8_t channelA, const uint8_t channelB);
    void connect();
    void updatePosition();
    int64_t readPosition();
};
