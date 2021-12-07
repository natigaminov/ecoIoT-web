#include "WaspMote.h"
#include "SDwrite.h"

/*
 * Переключатель моделей - файл toggle.h
 */

byte delay_warm_up = 02;
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
  /* 
   * Gas sensors needs a warm up time at least 120 seconds  
   * To reduce the battery consumption, use deepSleep instead delay
   * After 2 minutes, Waspmote wakes up thanks to the RTC Alarm
   * PWR.deepSleep("00:00:02:00", RTC_OFFSET, RTC_ALM1_MODE1, ALL_ON);
  */
  WPM.getGasValues();
  WPM.getMeteoValues();
  PWR.deepSleep(time_delay, RTC_OFFSET, RTC_ALM1_MODE1, ALL_ON);
  SDW.writeToFile();
}
