// TimeCircuits.h
#ifndef TIMECIRCUITS_H
#define TIMECIRCUITS_H

#include "Globals.h"

class TimeCircuits {
private:
  // Данные времени
  DateTime destT;
  DateTime presT;
  DateTime lastT;
  
  // Буфер дисплея
  byte buf[39];  // DIGITS_TOTAL = 39
  byte curDig;
  unsigned long tDig;
  unsigned long tBlink;
  unsigned long tMin;
  bool blinkTick;
  bool jumpLock;
  
  // Внутренние методы
  void showDigit(byte idx);
  void latchAll(const byte* data);
  void put2(byte off, int value);
  void put4(byte off, int value);
  void putMonth(byte off, int month);
  void fillDash(byte from, byte count);
  void toBufferDest(const DateTime& dt);
  void toBufferPres(const DateTime& dt);
  void toBufferLast(const DateTime& dt);
  void setLeds(const DateTime& dt, int pinAM, int pinPM, int pinS1, int pinS2, bool blinkSecs);
  void updatePresentTime();
  void incrementTime(DateTime& dt);
  int getDaysInMonth(int month, int year);

public:
  TimeCircuits();
  
  // Инициализация и основной цикл
  void init();
  void update();
  
  // Getters для Destination Time
  DateTime getDestTime() const { return destT; }
  bool isDestValid() const { return destT.valid; }
  
  // Setters для Destination Time
  void setDestTime(const DateTime& dt);
  void clearDestTime();
  
  // Getters для Present Time
  DateTime getPresTime() const { return presT; }
  bool isPresValid() const { return presT.valid; }
  
  // Setters для Present Time
  void setPresTime(const DateTime& dt);
  void clearPresTime();
  
  // Getters для Last Time
  DateTime getLastTime() const { return lastT; }
  bool isLastValid() const { return lastT.valid; }
  
  // Setters для Last Time
  void setLastTime(const DateTime& dt);
  void clearLastTime();
  
  // Управление прыжками во времени
  bool canTimeTravel() const { return destT.valid && presT.valid && !jumpLock; }
  void timeTravel();
  void unlockJump() { jumpLock = false; }
  bool isJumpLocked() const { return jumpLock; }
  
  // Обновление дисплея
  void refresh();
};

// Глобальный экземпляр (синглтон)
extern TimeCircuits timeCircuits;

#endif
