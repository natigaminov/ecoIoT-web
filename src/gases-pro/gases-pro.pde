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
byte delay_warm_up = 2;
// пауза для рабочего режима - нужна для частоты измерений 1 раз в минуту
byte delay_work = 1;
char time_delay[20];

void setup() {
  USB.ON();
  SD.ON();
  RTC.ON();
  USB.print(F("Time: "));
  USB.println(RTC.getTime());
  USB.print("Battery level: ");
  USB.print(PWR.getBatteryLevel(), DEC);
  USB.println("%");
  USB.print(F("Delay of work: "));
  sprintf(time_delay, "00:00:0%d:00", delay_work);
  USB.println(time_delay);
  USB.print(F("Delay of warm up: "));
  sprintf(time_delay, "00:00:0%d:00", delay_warm_up);
  USB.println(time_delay);
  USB.println(F("Initialization..."));
  WPM.turnMeteON();
  WPM.turnGasON();
  SDW.createFile();
  USB.println(F("Warm up delay..."));
  //PWR.deepSleep(time_delay, RTC_OFFSET, RTC_ALM1_MODE1, ALL_ON); // пока что это не работает и мы не знаем почему
  delay(delay_warm_up * 60 * 1000);                                // так что довольствуемся этим
  sprintf(time_delay, "00:00:0%d:00", delay_work);
}

void loop() {
  WPM.getMeasurements();
  SDW.writeToFile();
  //PWR.deepSleep("00:00:00:10", RTC_OFFSET, RTC_ALM1_MODE1, ALL_OFF); // пока что это не работает и мы не знаем почему
  delay(delay_work * 60 * 1000);                                       // так что довольствуемся этим
}
