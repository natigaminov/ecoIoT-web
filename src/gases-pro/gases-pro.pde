#include "WaspMote.h"
#include "SDwrite.h"
#include "WLess.h"

/*
 * Переключатель моделей - в файле toggle.h
 *
 * Данный проект построен с использованием условной компиляции (https://clck.ru/ZEjah)
 * для простоты переключения между наборами датчиков (моделями) без лишнего кода в памяти платы
 * Если у вас есть время реализовать переключение через ООП без лишнего расхода памяти, то будем рады вашим пул реквестам
 */

// пауза для первого включения - нужна для нагрева сенсоров CH4 (1 минута) и CO2 (2 минуты) после включения
#define DELAY_WARM_UP 2
// пауза для рабочего режима - нужна для частоты измерений 1 раз в минуту
#define DELAY_WORK 1
#define COUNT_MEASURE_FOR_SYNC 10 // количество измерений, через которое произойдет отправка локального файла на FTP сервер и создание нового лок.файла
char time_delay[20];

// APN settings
char apn[] = "internet.megafon";
char login[] = "";
char password[] = "";

// SERVER settings
char ftp_server[] = "";
uint16_t ftp_port = 21;
char ftp_user[] = "";
char ftp_pass[] = "";

// Счетчик для периодической отправки файла по FTP на сервер и создания нового файла
byte counter_sync = 1;


void setup() {
  USB.ON();
  SD.ON();
  RTC.ON();
  WLS.init_Network(apn, login, password);
  WLS.init_FTP(ftp_server, ftp_port, ftp_user, ftp_pass);
  WLS.setTimeFrom4G();
  
  USB.print(F("Time: "));
  USB.println(RTC.getTime());
  USB.print("Battery level: ");
  USB.print(PWR.getBatteryLevel(), DEC);
  USB.println("%");
  USB.print(F("Delay of work: "));
  sprintf(time_delay, "00:00:0%d:00", DELAY_WORK);
  USB.println(time_delay);
  USB.print(F("Delay of warm up: "));
  sprintf(time_delay, "00:00:0%d:00", DELAY_WARM_UP);
  USB.println(time_delay);
  USB.println(F("Initialization..."));
  WPM.turnMeteON();
  WPM.turnGasON();
  SDW.createFile();
  USB.println(F("Warm up delay..."));
// PWR.deepSleep(time_delay, RTC_OFFSET, RTC_ALM1_MODE1, ALL_ON);
  delay(DELAY_WARM_UP * 60000);
  sprintf(time_delay, "00:00:0%d:00", DELAY_WORK);
}

void loop() {
  WPM.getMeasurements();
  SDW.writeToFile();
// PWR.deepSleep("00:00:00:10", RTC_OFFSET, RTC_ALM1_MODE1, ALL_OFF);

  if(counter == COUNT_MEASURE_FOR_SYNC) {
    WLS.setTimeFrom4G();
    WLS.ftpUpload(SDW.getFilename(), SDW.getFilename());
    SDW.createFile();
    counter = 1;
  }
  counter++;
  delay(DELAY_WORK * 60000);
}
