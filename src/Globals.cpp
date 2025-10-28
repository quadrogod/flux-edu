#include "Globals.h"

/********************************************************************
 *  GLOBAL VARIABLES DEFINITIONS
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
