#ifndef CONFIG_H
#define CONFIG_H

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

#endif
