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
    void driveLeftMotorForward(uint8_t controlSignal);
    void driveRightMotorForward(uint8_t controlSignal);
    void driveLeftMotorBackward(uint8_t controlSignal);
    void driveRightMotorBackward(uint8_t controlSignal);
    void stopLeftMotor();
    void stopRightMotor();
};
