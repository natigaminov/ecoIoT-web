#include "WaspMote.h"
#include "SDwrite.h"

/*
 * Переключатель моделей - в файле toggle.h
 *
 * Данный проект построен с использованием условной компиляции (https://clck.ru/ZEjah)
 * для простоты переключения между наборами датчиков (моделями) без лишнего кода в памяти платы
 * Если у вас есть время реализовать переключение через ООП без лишнего расхода памяти, то будем рады вашим пул реквестам
 */

// пауза для первого включения - нужна для нагрева сенсоров CH4 (1 минута) и CO2 (2 минуты) после включения
byte delay_warm_up = 02;
// пауза для рабочего режима - нужна для частоты измерений 1 раз в минуту
byte delay_work = 01;
char time_delay[20];

void setup() {
  USB.ON();
  SD.ON();
  RTC.ON();
  WPM.turnMeteON();
  WPM.turnGasON();
  SDW.createFile();
  USB.println(sprintf(time_delay, "00:00:%d:00", delay_warm_up));
  PWR.deepSleep(time_delay, RTC_OFFSET, RTC_ALM1_MODE1, ALL_ON);
  sprintf(time_delay, "00:00:%d:00", delay_work);
}

void loop() {
  WPM.getMeasurements();
  SDW.writeToFile();
  PWR.deepSleep(time_delay, RTC_OFFSET, RTC_ALM1_MODE1, ALL_ON);
}
