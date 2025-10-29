#include <FastLED.h>
#include "Config.h"
#include "Globals.h"
#include "Animations.h"

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