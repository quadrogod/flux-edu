/********************************************************************
*  FLUX CAPACITOR CONTROLLER
 *  -------------------------------------
 *  Created by RadBench (youtube.com/radbenchyt)
 *  Refactored with clean structure, comments, and best practices.
 *
 *  Features:
 *  - IR Remote control via IRremote.hpp
 *  - LED animation modes with FastLED
 *  - DFPlayer Mini MP3 control (commented for Wokwi)
 *
 ********************************************************************/

#include "Arduino.h"
#include "FastLED.h"
#include "IRremote.hpp"
// #include "SoftwareSerial.h"
// #include "DFRobotDFPlayerMini.h"

#include "Config.h"
#include "Globals.h"
#include "IRHandler.h"
#include "Animations.h"

/********************************************************************
 *  SETUP
 ********************************************************************/
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
  IrReceiver.begin(IR_RECEIVE_PIN);
  Serial.println(F("IR Receiver Ready."));

  // ---------------- LED Setup ----------------
  // FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, LED_POWER_LIMIT_MA);
  FastLED.clear();
  FastLED.show();

  radChase2 = true; // initial demo effect
  Serial.println(F("Setup Completed.\n"));
}


/********************************************************************
 *  MAIN LOOP
 ********************************************************************/
void loop() {
  handleIRRemote();
  handleAnimations();
}
