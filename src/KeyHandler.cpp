#include <FastLED.h>
#include <Keypad.h>
#include "Config.h"
#include "Globals.h"
#include "Animations.h"
#include "KeyHandler.h"
#include "IRHandler.h"

#define DEBOUNCE_MS   200UL

unsigned long tKey=0;

const byte ROWS = 4, COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','D'},
  {'4','5','6','P'},
  {'7','8','9','L'},
  {'R','0','#','E'}
};
byte rowPins[ROWS] = {2,3,4,5};
byte colPins[COLS] = {6,7,8,9};
Keypad kpd(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

char lastKeyPressed = '\0';

void handleKey() {

    unsigned long ms = millis();

    char k = kpd.getKey();
    if (!k) return;

    if (ms - tKey < DEBOUNCE_MS && k == lastKeyPressed) return;

    tKey = ms;
    lastKeyPressed = k;

    resetModes();

    switch (k)
    {
        case '0':
            Serial.println(F("Pressed Zero"));        
            break;
        case '1':
            Serial.println(F("Start Time Travel Mode"));        
            timeTravel = true; delaySpeed = 113;
            break;

        case '2':
            Serial.println(F("Start Smooth Mode"));        
            smoothChase = true; delaySpeed = 80; 
        break;

        default:
            Serial.println(k);
            break;
    }

}