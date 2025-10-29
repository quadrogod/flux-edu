#include <FastLED.h>
#include "Config.h"

CRGB leds[NUM_LEDS];

uint8_t hue = 0;
int delaySpeed = 80;
float movieSpeed = 34.45;

bool timeTravel = false;
bool smoothChase = false;
bool movieChase = false;
bool movieChaseSimple = false;
bool thirtyChase = false;
bool radChase = false;
bool radChase2 = false;
bool rainbowChase = false;

unsigned long previousTime = 0;