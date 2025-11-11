#include <Arduino.h>
#include <FastLED.h>
#include "Config.h"
#include "TimeCircuits.h"
#include "TemperatureHandler.h"

const float BETA_THERM = 3950;

float getTemperature() {
  int raw = analogRead(NTC_PIN);
  float tempC = 1 / (log(1 / (1023. / raw - 1)) / BETA_THERM + 1.0 / 298.15) - 273.15;
  return tempC;
}

void initTemperatureSensor() {
  pinMode(NTC_PIN, INPUT);
  Serial.println(F("Temperature Sensor Ready"));
}

void handleTemperatureSensor() {
  float tC = getTemperature();
  
  // Проверка условия прыжка во времени
  if (tC >= 58.0 && timeCircuits.canTimeTravel()) {
    timeCircuits.timeTravel();
  }
  
  // Сброс блокировки при снижении температуры
  if (tC < 34.0 && timeCircuits.isJumpLocked()) {
    timeCircuits.unlockJump();
    Serial.println(F("Jump unlocked"));
  }
}
