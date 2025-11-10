#include <FastLED.h>
#include <GTimer.h>
#include "Config.h"
#include "Globals.h"
#include "Animations.h"

CRGB leds[NUM_LEDS];
uint8_t hue = 0;

// Глобальные переменные для анимаций
int delaySpeed = 80;
float movieSpeed = 34.45;

// Флаги режимов
bool timeTravel = false;
bool movieTimeTravel = false;
bool smoothChase = false;
bool movieChase = false;
bool movieChaseSimple = false;
bool thirtyChase = false;
bool radChase = false;
bool radChase2 = false;
bool rainbowChase = false;

// Таймеры для анимаций
GTimer<millis> animTimer;
GTimer<millis> hueTimer(5, true); // для rainbow

// Счетчики кадров анимаций
int animStep = 0;
int animSubStep = 0;

void resetModes() {
    timeTravel = smoothChase = movieChase = movieChaseSimple =
    thirtyChase = radChase = radChase2 = rainbowChase = movieTimeTravel = false;
    animStep = 0;
    animSubStep = 0;
    animTimer.stop();
}

void setSmoothChase() {
    resetModes();
    smoothChase = true;
    delaySpeed = 80;
    animTimer.setTime(delaySpeed);
    animTimer.start();
}

void setMovieChase() {
    resetModes();
    movieChase = true;
    movieSpeed = 22.97;
    animTimer.setTime(movieSpeed);
    animTimer.start();
}

void setMovieChaseSimple() {
    resetModes();
    movieChaseSimple = true;
    movieSpeed = 34.45;
    animTimer.setTime(movieSpeed);
    animTimer.start();
}

void setThirtyChase() {
    resetModes();
    thirtyChase = true;
    movieSpeed = 33.33;
    animTimer.setTime(movieSpeed);
    animTimer.start();
}

void setRadChase() {
    resetModes();
    radChase = true;
    movieSpeed = 66.66;
    animTimer.setTime(movieSpeed);
    animTimer.start();
}

void setRadChase2() {
    resetModes();
    radChase2 = true;
    movieSpeed = 66.66;
    animTimer.setTime(movieSpeed);
    animTimer.start();
}

void setTimeTravel() {
    resetModes();
    timeTravel = true;
    delaySpeed = 113;
    animTimer.setTime(delaySpeed);
    animTimer.start();
}

void setMovieTimeTravel() {
    resetModes();
    movieTimeTravel = true;
    delaySpeed = 113;
    animTimer.setTime(delaySpeed);
    animTimer.start();
}

void setRainbowChase() {
    resetModes();
    rainbowChase = true;
    movieSpeed = 66.66;
}

void setOff() {
    resetModes();
    FastLED.clear();
    FastLED.show();
}

void handleAnimations() {
    if (smoothChase) runSmoothChase();
    else if (movieChase) runMovieChase();
    else if (movieChaseSimple) runMovieChaseSimple();
    else if (thirtyChase) runThirtyChase();
    else if (radChase) runRadChase();
    else if (radChase2) runRadChase2();
    else if (timeTravel) runTimeTravel();
    else if (movieTimeTravel) runMovieTimeTravel();
    else if (rainbowChase) runRainbowChase();
}

void runSmoothChase() {
    if (!animTimer.tick()) return;
    
    FastLED.clear();
    for (int j = 0; j <= 6; j++) {
        if (animStep - j >= 0) {
            leds[animStep - j] = CHSV(32, 128, 20 + j * 30);
        }
    }
    FastLED.show();
    
    animStep++;
    if (animStep >= NUM_LEDS) animStep = 0;
}

void runMovieChase() {
    if (!animTimer.tick()) return;
    
    FastLED.clear();
    int idx = animStep * 2;
    if (idx < NUM_LEDS - 1) {
        leds[idx] = leds[idx + 1] = CHSV(22, 200, 100);
    }
    FastLED.show();
    
    animStep++;
    if (animStep >= 6) animStep = 0;
}

void runMovieChaseSimple() {
    if (!animTimer.tick()) return;
    
    FastLED.clear();
    int idx = 2 + animStep * 2;
    if (idx <= 8) {
        leds[idx] = CHSV(22, 200, 100);
    }
    FastLED.show();
    
    animStep++;
    if (animStep >= 4) animStep = 0;
}

void runThirtyChase() {
    if (!animTimer.tick()) return;
    
    FastLED.clear();
    int base = animStep * 2;
    if (base < NUM_LEDS - 1) {
        leds[base] = CHSV(32, 128, 100);
        leds[base + 1] = CHSV(32, 128, 100);
    }
    FastLED.show();
    
    animStep++;
    if (animStep >= 4) animStep = 0;
}

void runRadChase() {
    if (!animTimer.tick()) return;
    
    FastLED.clear();
    int base = animStep * 2;
    if (base < NUM_LEDS - 1) {
        leds[base] = leds[base + 1] = CHSV(28, 120, 100);
    }
    FastLED.show();
    
    animStep++;
    if (animStep >= 5) animStep = 0;
}

void runRadChase2() {
    if (!animTimer.tick()) return;
    
    FastLED.clear();
    if (animStep < NUM_LEDS) {
        leds[animStep] = CHSV(28, 200, 120);
        if (animStep > 0) leds[animStep - 1] = CHSV(28, 200, 30);
        if (animStep < NUM_LEDS - 1) leds[animStep + 1] = CHSV(28, 200, 30);
    }
    FastLED.show();
    
    animStep++;
    if (animStep >= 10) animStep = 0;
}

void runRainbowChase() {
    // Обновление hue каждые 5 мс
    if (hueTimer.tick()) hue++;
    
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(hue + i * 10, 255, 200);
    }
    FastLED.show();
}

void runTimeTravel() {
    if (!animTimer.tick()) return;
    
    FastLED.clear();
    for (int j = 0; j <= 6; j++) {
        if (animStep - j >= 0 && animStep - j < NUM_LEDS) {
            leds[animStep - j] = CHSV(28, 150, 60 + j * 30);
        }
    }
    FastLED.show();
    
    animStep++;
    
    if (animStep >= NUM_LEDS) {
        delaySpeed *= 0.837;
        animTimer.setTime(delaySpeed);
        animStep = 0;
        
        if (delaySpeed < 1) {
            // Финальная вспышка
            digitalWrite(SINGLE_LED_PIN, HIGH);
            fill_solid(leds, NUM_LEDS, CRGB::Blue);
            FastLED.show();
            delay(3300); // Единственный delay для финальной вспышки
            FastLED.clear();
            FastLED.show();
            digitalWrite(SINGLE_LED_PIN, LOW);
            
            // Переход на следующий режим
            delaySpeed = 80;
            setSmoothChase();
        }
    }
}

void runMovieTimeTravel() {
    if (!animTimer.tick()) return;
    
    FastLED.clear();
    for (int j = 0; j <= 6; j++) {
        if (animStep - j >= 0 && animStep - j < NUM_LEDS) {
            leds[animStep - j] = CHSV(22, 200, 60 + j * 30);
        }
    }
    FastLED.show();
    
    animStep++;
    
    if (animStep >= NUM_LEDS) {
        delaySpeed *= 0.837;
        animTimer.setTime(delaySpeed);
        animStep = 0;
        
        if (delaySpeed < 1) {
            // Финальная вспышка
            digitalWrite(SINGLE_LED_PIN, HIGH);
            fill_solid(leds, NUM_LEDS, CRGB::Blue);
            FastLED.show();
            delay(3300); // Единственный delay для финальной вспышки
            FastLED.clear();
            FastLED.show();
            digitalWrite(SINGLE_LED_PIN, LOW);
            
            // Переход на следующий режим
            delaySpeed = 80;
            movieSpeed = 66.66;
            setRadChase2();
        }
    }
}
