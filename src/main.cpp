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
#define CHANNEL_B 3
// Controller's parameters
#define KP 0.5
#define KI 5e-3
#define KD 5e-3

#define MIN_CONTROL_SIGNAL 50
#define MAX_CONTROL_SIGNAL 200

#define PULSE_PER_REVOLUTION 450
#define BAUDRATE 9600
#define WARMUP_TIME 5000
#define SETTLE_CONDITION 0.99


Controller g_controller(KP, KI, KD, MIN_CONTROL_SIGNAL, MAX_CONTROL_SIGNAL);
Encoder g_encoder(CHANNEL_A, CHANNEL_B, PULSE_PER_REVOLUTION);
MotorDriver g_driver(ENA_PIN, ENB_PIN, INA_PIN, INB_PIN, INC_PIN, IND_PIN);


void onInterrupt() {
   g_encoder.updatePulseCount();
}


bool reachSettleCondition(float setPoint, float feedback, float settleCondition) {
    return 1 - abs(setPoint - feedback) / setPoint > settleCondition;
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
  float setAngle = 270;
  float feedbackAngle = g_encoder.readAngle();

  if (reachSettleCondition(setAngle, feedbackAngle, SETTLE_CONDITION)) {  
      Serial.println("Settle condition reached.");
      g_driver.stopLeftMotor();
      return;
  }

  g_controller.receiveSetPoint(setAngle);
  g_controller.receiveFeedback(feedbackAngle);
  
  float controlSignal = g_controller.sendControlSignal();

  g_driver.driveLeftMotor(controlSignal);

  Serial.print("Feedback: ");
  Serial.print(feedbackAngle);
  Serial.print("\tControl signal: ");
  Serial.println(controlSignal);
}
