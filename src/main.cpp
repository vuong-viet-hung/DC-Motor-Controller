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
#define KI 5e-3
#define KD 5e-3

#define MAX_APPLY_VOLTAGE 200
#define MIN_APPLY_VOLTAGE 50

#define BAUDRATE 9600
#define WARMUP_TIME 5000
#define SETTLE_CONDITION 0.99


Controller g_controller(KP, KI, KD);
Encoder g_encoder(CHANNEL_A, CHANEEL_B);
MotorDriver g_driver(ENA_PIN, ENB_PIN, INA_PIN, INB_PIN, INC_PIN, IND_PIN);


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
  float setAngle = 180;
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

  if (controlSignal > 0) {
      controlSignal = min(controlSignal, MAX_APPLY_VOLTAGE);
      controlSignal = max(controlSignal, MIN_APPLY_VOLTAGE);
  }
  else {
      controlSignal = max(controlSignal, -MAX_APPLY_VOLTAGE);
      controlSignal = min(controlSignal, -MIN_APPLY_VOLTAGE);
  }
  g_driver.driveLeftMotor(controlSignal);

  uint8_t feedbackAngle = map(feedback, 0, 450, 0, 360);
  Serial.print("Feedback: ");
  Serial.print((int32_t)feedbackAngle);
  Serial.print("\tControl signal: ");
  Serial.println(controlSignal);
}
