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
#include <IRremote.hpp>
#include <FastLED.h>
// #include "SoftwareSerial.h"
// #include "DFRobotDFPlayerMini.h"

/********************************************************************
 *  CONFIGURATION
 ********************************************************************/

// ----------------- DFPlayer -----------------
// SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
// DFRobotDFPlayerMini myDFPlayer;

// ----------------- IR -----------------
#define IR_RECEIVE_PIN 3

// Remote button codes
#define BTN_0       104
#define BTN_1       48
#define BTN_2       24
#define BTN_3       122
#define BTN_4       16
#define BTN_5       56
#define BTN_6       90
#define BTN_7       66
#define BTN_8       74
#define BTN_9       82
#define BTN_STOP    168
#define BTN_VOL_UP  2
#define BTN_VOL_DWN 152
#define BTN_UP      224  // previous
#define BTN_DOWN    144  // next
#define BTN_POWER   162

// ----------------- LEDS -----------------
#define NUM_LEDS   22
#define DATA_PIN   5
#define CLOCK_PIN  13
#define LED_POWER_LIMIT_MA 500

// ----------------- Misc -----------------
#define SINGLE_LED_PIN 12


/********************************************************************
 *  VARIABLES
 ********************************************************************/

CRGB leds[NUM_LEDS];

uint8_t hue = 0;
int delaySpeed = 80;
float movieSpeed = 34.45;

// Animation mode flags
bool timeTravel = false;
bool smoothChase = false;
bool movieChase = false;
bool movieChaseSimple = false;
bool thirtyChase = false;
bool radChase = false;
bool radChase2 = false;
bool rainbowChase = false;

// Timers
unsigned long previousTime = 0;


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
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
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


/********************************************************************
 *  IR HANDLER
 ********************************************************************/
void handleIRRemote() {
  if (!IrReceiver.decode()) return;

  uint8_t cmd = IrReceiver.decodedIRData.command;
  Serial.print(F("IR Command: "));
  Serial.println(cmd);

  // myDFPlayer.stop(); // generic stop before switching mode

  // Reset all modes
  resetModes();

  switch (cmd) {
    case BTN_1:  timeTravel = true; delaySpeed = 113; break;
    case BTN_POWER: FastLED.clear(); FastLED.show(); break;
    case BTN_2:  smoothChase = true; delaySpeed = 80; break;
    case BTN_3:  thirtyChase = true; movieSpeed = 33.33; break;
    case BTN_4:  movieChase = true; movieSpeed = 22.97; break;
    case BTN_5:  movieChaseSimple = true; movieSpeed = 34.45; break;
    case BTN_6:  radChase = true; movieSpeed = 66.66; break;
    case BTN_7:  radChase2 = true; movieSpeed = 66.66; break;
    case BTN_8:  rainbowChase = true; movieSpeed = 66.66; break;

    case BTN_UP:
      if (movieSpeed > 24) movieSpeed -= 10;
      if (delaySpeed > 20) delaySpeed -= (delaySpeed <= 20 ? 4 : 20);
      Serial.println(F("↑ Speed up"));
      break;

    case BTN_DOWN:
      if (movieSpeed < 200) movieSpeed += 10;
      if (delaySpeed < 160) delaySpeed += 20;
      Serial.println(F("↓ Slow down"));
      break;

    case BTN_9:
      // myDFPlayer.playMp3Folder(6);
      break;
  }

  IrReceiver.resume();
}


/********************************************************************
 *  MODE MANAGEMENT
 ********************************************************************/
void resetModes() {
  timeTravel = smoothChase = movieChase = movieChaseSimple =
  thirtyChase = radChase = radChase2 = rainbowChase = false;
}


/********************************************************************
 *  ANIMATION HANDLER
 ********************************************************************/
void handleAnimations() {
  if (smoothChase)       runSmoothChase();
  else if (movieChase)   runMovieChase();
  else if (movieChaseSimple) runMovieChaseSimple();
  else if (thirtyChase)  runThirtyChase();
  else if (radChase)     runRadChase();
  else if (radChase2)    runRadChase2();
  else if (timeTravel)   runTimeTravel();
  else if (rainbowChase) runRainbowChase();
}


/********************************************************************
 *  ANIMATION FUNCTIONS
 ********************************************************************/

void runSmoothChase() {
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j <= 6; j++) {
      if (i - j >= 0) leds[i - j] = CHSV(32, 128, 20 + j * 30);
    }
    FastLED.show();
    delay(delaySpeed);
    FastLED.clear();
  }
}

void runMovieChase() {
  for (int i = 0; i < 6; i++) {
    int idx = i * 2;
    leds[idx] = leds[idx + 1] = CHSV(22, 200, 100);
    FastLED.show();
    delay(movieSpeed);
    FastLED.clear();
  }
}

void runMovieChaseSimple() {
  for (int i = 2; i <= 8; i += 2) {
    leds[i] = CHSV(22, 200, 100);
    FastLED.show();
    delay(movieSpeed);
    FastLED.clear();
  }
}

void runThirtyChase() {
  for (int i = 0; i < 4; i++) {
    int base = i * 2;
    leds[base] = CHSV(32, 128, 100);
    leds[base + 1] = CHSV(32, 128, 100);
    FastLED.show();
    delay(movieSpeed);
    FastLED.clear();
  }
}

void runRadChase() {
  for (int i = 0; i < 5; i++) {
    int base = i * 2;
    leds[base] = leds[base + 1] = CHSV(28, 120, 100);
    FastLED.show();
    delay(movieSpeed);
    FastLED.clear();
  }
}

void runRadChase2() {
  for (int i = 0; i < 10; i++) {
    leds[i] = CHSV(28, 200, 120);
    if (i > 0) leds[i - 1] = CHSV(28, 200, 30);
    if (i < NUM_LEDS - 1) leds[i + 1] = CHSV(28, 200, 30);
    FastLED.show();
    delay(movieSpeed);
    FastLED.clear();
  }
}

void runRainbowChase() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue + i * 10, 255, 200);
  }
  EVERY_N_MILLISECONDS(5) { hue++; }
  FastLED.show();
}

void runTimeTravel() {
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j <= 6; j++) {
      if (i - j >= 0) leds[i - j] = CHSV(28, 150, 60 + j * 30);
    }
    FastLED.show();
    delay(delaySpeed);
    FastLED.clear();
  }

  delaySpeed *= 0.837;

  if (delaySpeed < 1) {
    digitalWrite(SINGLE_LED_PIN, HIGH);
    fill_solid(leds, NUM_LEDS, CRGB::Blue);
    FastLED.show();
    delay(3300);
    FastLED.clear();
    FastLED.show();
    digitalWrite(SINGLE_LED_PIN, LOW);
    delaySpeed = 80;
    timeTravel = false;
    smoothChase = true;
  }
}