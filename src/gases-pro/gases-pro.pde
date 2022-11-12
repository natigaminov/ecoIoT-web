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

#define DELAY_WARM_UP 2 // пауза для первого включения - нужна для нагрева сенсоров CH4 (1 минута) и CO2 (2 минуты) после включения
#define DELAY_WORK 1 // пауза для рабочего режима - нужна для частоты измерений 1 раз в минуту
#define COUNT_MEASURE_FOR_SYNC 10 // количество измерений, через которое произойдет отправка локального файла на FTP сервер и создание нового лок.файла
byte counter_sync = 1; // счетчик для периодической отправки файла по FTP на сервер и создания нового файла
char time_delay[20];

// APN settings
char apn[] = "";
char apn_login[] = "";
char apn_pass[] = "";

// FTP-server settings
char ftp_server[] = "158.160.40.63";
uint16_t ftp_port = 21;
char ftp_user[] = "";
char ftp_pass[] = "";

// HTTP-server settings
char http_server[] = "158.160.40.63";
uint16_t http_port = 8090;
#ifdef MODEL_GREEN
    char http_resource[] = "/gasesdata1/oxides";
#elif defined MODEL_BLUE
    char http_resource[] = "/gasesdata1/hydrides";
#endif 
char api_access_token[] = "g7nerQVv9F0qQre4vkmBfiqe4V3gJ49k";
char http_data[800];

void setup() {
    USB.ON();

    SD.ON();
    
    RTC.ON();
    WLS.set_APN(apn, apn_login, apn_pass);
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
    // delay(DELAY_WARM_UP * 60000);
    sprintf(time_delay, "00:00:0%d:00", DELAY_WORK);
}

void loop() {
    // PWR.deepSleep("00:00:00:10", RTC_OFFSET, RTC_ALM1_MODE1, ALL_OFF);
    char timestamp[20];
    RTC.getTime();
    
    WPM.getMeasurements();
    SDW.writeToFile();

    #ifdef MODEL_GREEN
        sprintf(http_data, "api_token=%s&timestamp=%s&temperature=%s&humidity=%s&pressure=%s&co=%s&no=%s&co2=%s&no2=%s",
                api_access_token, timestamp, WPM.temperature, WPM.humidity, WPM.pressure,
                WPM.concentration_CO, WPM.concentration_NO, WPM.concentration_CO2, WPM.concentration_NO2);
    #elif defined MODEL_BLUE
        sprintf(http_data, "api_token=%s&timestamp=%s&temperature=%s&humidity=%s&pressure=%s&nh3=%s&h2s=%s&ch4=%s",
                api_access_token, timestamp, WPM.temperature, WPM.humidity, WPM.pressure,
                WPM.concentration_NH3, WPM.concentration_H2S, WPM.concentration_CH4);
    #endif
    WLS.httpSendRequest(http_server, http_port, http_resource, http_data);

    if(counter_sync == COUNT_MEASURE_FOR_SYNC) {
        SDW.createFile();
        counter_sync = 1;
    }
    counter_sync++;

    // delay(DELAY_WORK * 60000);
}
