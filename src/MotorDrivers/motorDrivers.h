#pragma once
#include <stdint.h>


class MotorDriver {
    uint8_t enaPin, enbPin, inaPin, inbPin, incPin, indPin;
public:
    MotorDriver(
        const uint8_t enaPin, 
        const uint8_t enbPin, 
        const uint8_t inaPin, 
        const uint8_t inbPin, 
        const uint8_t incPin, 
        const uint8_t indPin
    );
    void connect();
    void driveLeftMotor(int16_t controlSignal);
    void driveRightMotor(int16_t controlSignal);
    void stopLeftMotor();
    void stopRightMotor();
};
