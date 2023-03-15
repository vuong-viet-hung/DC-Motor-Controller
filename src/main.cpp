#include <Arduino.h>
#include <stdint.h>
#include "Controllers/controllers.h"
#include "Encoders/encoders.h"
#include "MotorDrivers/motorDrivers.h"
// Motor driver's pins
#define ENA_PIN 5
#define ENB_PIN 6
#define INA_PIN 4
#define INB_PIN 7
#define INC_PIN 8
#define IND_PIN 9
// Encoders' pins
#define CHANNEL_A 2
#define CHANEEL_B 3
// Controller's parameters
#define KP 0.5
#define KI 1e-4
#define KD 0

#define MAX_APPLY_VOLTAGE 210
#define MIN_APPLY_VOLTAGE 30

#define BAUDRATE 9600
#define WARMUP_TIME 5000
#define SETTLE_CONDITION 0.95


Controller g_controller(KP, KI, KD);
Encoder g_encoder(CHANNEL_A, CHANEEL_B);
MotorDriver g_driver(ENA_PIN, ENB_PIN, INA_PIN, INB_PIN, INC_PIN, IND_PIN);
bool g_settling = true;


void onInterrupt() {
  g_encoder.updatePosition();
}


void setup() {
  Serial.begin(BAUDRATE);
  Serial.println("Warming up...");
  delay(WARMUP_TIME);
  g_driver.connect();
  g_encoder.connect();
  attachInterrupt(digitalPinToInterrupt(CHANNEL_A), onInterrupt, RISING);
}


void loop() {
  float setAngle = 90;
  float setPoint = map(setAngle, 0, 360, 0, 450);
  int64_t feedback = g_encoder.readPosition();

  if (1 - abs(setPoint - feedback) / setPoint > SETTLE_CONDITION) {  
      Serial.println("Settle condition reached.");
      g_driver.stopLeftMotor();
      return;
  }

  g_controller.receiveSetPoint(setPoint);
  g_controller.receiveFeedback(feedback);
  float controlSignal = g_controller.sendControlSignal();
  uint8_t applyVoltage = abs(controlSignal);
  applyVoltage = min(applyVoltage, MAX_APPLY_VOLTAGE);
  applyVoltage = max(applyVoltage, MIN_APPLY_VOLTAGE);

  if (controlSignal > 0) {
      g_driver.driveLeftMotorForward(applyVoltage);
  }
  else {
      g_driver.driveLeftMotorBackward(applyVoltage);
  }

  Serial.print("Feedback: ");
  Serial.print((int32_t)feedback);
  Serial.print("\tControl signal: ");
  if (controlSignal > 0) {
      Serial.println(applyVoltage);
  }
  else {
      Serial.println("-");
      Serial.println(applyVoltage);
  }
}
