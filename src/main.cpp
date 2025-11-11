#include <Arduino.h>
#include <FastLED.h>
// #include <IRremote.hpp>
// #include <SoftwareSerial.h>
// #include <DFRobotDFPlayerMini.h>

#include "Config.h"
#include "Globals.h"
#include "IRHandler.h"
#include "KeyHandler.h"
#include "TemperatureHandler.h"
#include "SerialHandler.h"
#include "Animations.h"
#include "TimeCircuits.h"

void setup() {
    pinMode(SINGLE_LED_PIN, OUTPUT);

    Serial.begin(115200);
    Serial.println(F("\n=== Flux Capacitor Setup Starting ==="));

    // ---------------- DFPlayer (commented for Wokwi) ----------------
    // mySoftwareSerial.begin(9600);
    // if (!myDFPlayer.begin(mySoftwareSerial)) {
    //   Serial.println(F("Unable to begin DFPlayer Mini!"));
    //   while (true);
    // }
    // myDFPlayer.volume(29);
    // myDFPlayer.play(2); // startup sound
    // delay(600);

    // ---------------- IR Receiver ----------------
    initIR();
    Serial.println(F("IR Receiver Ready."));

    // ---------------- LED Setup ----------------
    FastLED.addLeds<WS2812B, DATA_RING_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, LED_POWER_LIMIT_MA);
    FastLED.clear();
    FastLED.show();

    timeCircuits.init();
    initKeypad();
    initTemperatureSensor();

    // radChase2 = true; // initial demo effect
    Serial.println(F("Setup Completed.\n"));

    // запускаем свет
    // smoothChase = true; delaySpeed = 80; 
    // Serial.println(F("Start Time Travel Mode")); 
    resetModes();       
    // timeTravel = true; delaySpeed = 113;

}

void loop() {
    handleIRRemote();
    handleKey();
    handleSerial();
    handleAnimations();
    handleTemperatureSensor();
    timeCircuits.update(); 
}