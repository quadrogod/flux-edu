#include <FastLED.h>
#include <Keypad.h>
#include "Config.h"
#include "Globals.h"
#include "Animations.h"
#include "KeyHandler.h"
#include "IRHandler.h"

// KEYPAD_AZ_DELIVERY Keypad pins (10 pin)
// NA C1 C2 C3 C4 R1 R2 R3 R4 NA

// Выберите тип клавиатуры (закомментируйте ненужный)
// #define KEYPAD_AZ_DELIVERY    // Для AZ-Delivery
#define KEYPAD_STANDARD    // Для стандартной Arduino keypad

#define DEBOUNCE_MS   200UL

unsigned long tKey=0;

const byte ROWS = 4, COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','D'},
  {'4','5','6','P'},
  {'7','8','9','L'},
  {'R','0','#','E'}
};

// sta
// byte rowPins[ROWS] = {2,3,4,5};
// byte colPins[COLS] = {6,7,8,9};
// https://cdn.shopify.com/s/files/1/1509/1638/files/4x4_Keypad_Tastatur_Datenblatt_AZ-Delivery_Vertriebs_GmbH.pdf?v=1608629136
// byte rowPins[ROWS] = {5, 4, 3, 2};    // R1=D5, R2=D4, R3=D3, R4=D2
// byte colPins[COLS] = {9, 8, 7, 6};    // C1=D9, C2=D8, C3=D7, C4=D6

// Автоматический выбор распиновки
#ifdef KEYPAD_AZ_DELIVERY
  // https://cdn.shopify.com/s/files/1/1509/1638/files/4x4_Keypad_Tastatur_Datenblatt_AZ-Delivery_Vertriebs_GmbH.pdf?v=1608629136
  // AZ-Delivery: Rows на D5-D2, Columns на D9-D6
  byte rowPins[ROWS] = {5, 4, 3, 2}; // R1=D5, R2=D4, R3=D3, R4=D2
  byte colPins[COLS] = {9, 8, 7, 6}; // C1=D9, C2=D8, C3=D7, C4=D6
#else
  // Стандартная: Rows на D2-D5, Columns на D6-D9
  byte rowPins[ROWS] = {2, 3, 4, 5};
  byte colPins[COLS] = {6, 7, 8, 9};
#endif

// or RIGHT pin connection for Standart Keypad, but physical AZ Delivery Keypad
// C1 (Pin 5 на разъеме) D6
// C2 (Pin 5 на разъеме) D7
// C3 (Pin 5 на разъеме) D8
// C4 (Pin 5 на разъеме) D9

// R1 (Pin 1 на разъеме) D2
// R2 (Pin 1 на разъеме) D3
// R3 (Pin 1 на разъеме) D4
// R4 (Pin 1 на разъеме) D5

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
        case '1':
            setTimeTravel();
            Serial.println(F("Time Travel activated"));
            break;
            
        case '2':
            setSmoothChase();
            Serial.println(F("Smooth Chase activated"));
            break;
            
        case '3':
            setThirtyChase();
            Serial.println(F("Thirty Chase activated"));
            break;

        case '4':
            setMovieChase();
            Serial.println(F("Movie Chase activated"));
            break;
          
        case '5':
            setMovieChaseSimple();
            Serial.println(F("Movie Chase Simple activated"));
            break;

        case '6':
            setRadChase();
            Serial.println(F("Rad Chase activated"));
            break;

        case '7':
            setRadChase2();
            Serial.println(F("Rad Chase 2 activated"));
            break;

        case '8':
            setRainbowChase();
            Serial.println(F("Rainbow activated"));
            break;

        case '9':
            setMovieTimeTravel();
            Serial.println(F("Movie Time Travel activated"));
            break;

        case '0':
            setOff();
            Serial.println(F("LEDs cleared"));
            break;
            
        default:
            Serial.println(F("Unknown command"));
            Serial.println(k);
            break;
    }

}