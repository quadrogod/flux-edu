#include <FastLED.h>
#include <IRremote.hpp>
#include "Config.h"
#include "Globals.h"
#include "IRHandler.h"

void initIR() {
    IrReceiver.begin(IR_RECEIVE_PIN);
}

void resetModes() {
    timeTravel = smoothChase = movieChase = movieChaseSimple =
    thirtyChase = radChase = radChase2 = rainbowChase = false;
}

void handleIRRemote() {
    if (!IrReceiver.decode()) return;

    uint8_t cmd = IrReceiver.decodedIRData.command;
    Serial.print(F("IR Command: "));
    Serial.println(cmd);

    // myDFPlayer.stop(); // generic stop before switching mode

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

        default: break;
    }

    IrReceiver.resume();
}
