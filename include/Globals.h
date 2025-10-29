#pragma once
#include "FastLED.h"
#include "Config.h"

/********************************************************************
 *  GLOBAL VARIABLES
 ********************************************************************/
extern CRGB leds[NUM_LEDS];

extern uint8_t hue;
extern int delaySpeed;
extern float movieSpeed;

// Animation mode flags
extern bool timeTravel;
extern bool smoothChase;
extern bool movieChase;
extern bool movieChaseSimple;
extern bool thirtyChase;
extern bool radChase;
extern bool radChase2;
extern bool rainbowChase;

// Timer
extern unsigned long previousTime;