#include <FastLED.h>
#include "Config.h"
#include "Animations.h"
// #include "Globals.h"
// #include "IRHandler.h"

void handleSerial() {
    if (!Serial.available()) return;
    
    char k = Serial.read();
    
    // Очистка буфера от лишних символов (например \n)
    while (Serial.available()) Serial.read();
    
    Serial.print(F("Received: "));
    Serial.println(k);
    
    switch (k) {
        case '1':
            setTimeTravel();
            Serial.println(F("Time Travel activated"));
            break;
            
        case '2':
            setSmoothChase();
            Serial.println(F("Smooth Chase activated"));
            break;
            
        case '3':
            setRainbowChase();
            Serial.println(F("Rainbow activated"));
            break;
            
        case '0':
            setOff();
            Serial.println(F("LEDs cleared"));
            break;
            
        default:
            Serial.println(F("Unknown command"));
            break;
    }
}
