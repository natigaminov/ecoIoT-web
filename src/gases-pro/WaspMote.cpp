#include "WaspMote.h"

WaspMote::WaspMote(){}

// Инициализация всех сокетов для сенсоров
void WaspMote::turnGasON() {
    #ifdef MODEL_GREEN
    gas_sensor_CO.ON();
    gas_sensor_NO.ON();
    gas_sensor_CO2.ON();
    gas_sensor_NO2.ON();
    #elif defined MODEL_BLUE
    gas_sensor_NH3.ON();
    gas_sensor_H2S.ON();
    gas_sensor_CH4.ON();
    #endif
}

// Деинициализация всех сокетов для сенсоров
void WaspMote::turnGasOFF() {
    #ifdef MODEL_GREEN
    gas_sensor_CO.OFF();
    gas_sensor_NO.OFF();
    gas_sensor_CO2.OFF();
    gas_sensor_NO2.OFF();
    #elif defined MODEL_BLUE
    gas_sensor_NH3.OFF();
    gas_sensor_H2S.OFF();
    gas_sensor_CH4.OFF();
    #endif
}

float WaspMote::ppmToMgm(float ppm, float molar, float temp, float pres) {
    float mgm = ppm * (molar / 22.4) * (273 / (273 + temp)) * (pres / 101300);
    return mgm;
}

/*
 * Конвертация значений сенсоров из ppm в мг/м3 и перевод в строковый тип
 * Данный метод класса WaspMote является protected, т.к. идет в жесткой связке после метода
 * getMeteoValues() и не должен быть вызван отдельно во избежание некорректных
 * значений. 
 * Для вызова данного метода в связке с getMeteoValues() используется
 * метод-враппер getMeasurements()
 */
void WaspMote::convGasValues() {
    #ifdef MODEL_GREEN
    conv_CO = ppmToMgm(gas_sensor_CO.getConc(), 28.01, temp, pres);
    conv_NO = ppmToMgm(gas_sensor_NO.getConc(), 30.01, temp, pres);
    conv_CO2 = ppmToMgm(gas_sensor_CO2.getConc(), 44.01, temp, pres);
    conv_NO2 = ppmToMgm(gas_sensor_NO2.getConc(), 46.0055, temp, pres);
    Utils.float2String(conv_CO, concentration_CO, 10);
    Utils.float2String(conv_NO, concentration_NO, 10);
    Utils.float2String(conv_CO2, concentration_CO2, 10);
    Utils.float2String(conv_NO2, concentration_NO2, 10);
    #elif defined MODEL_BLUE
    conv_NH3 = ppmToMgm(gas_sensor_NH3.getConc(), 17.031, temp, pres);
    conv_H2S = ppmToMgm(gas_sensor_H2S.getConc(), 34.08, temp, pres);
    conv_CH4 = ppmToMgm(10000 * gas_sensor_CH4.getConc(), 16.04, temp, pres);
    Utils.float2String(conv_NH3, concentration_NH3, 10);
    Utils.float2String(conv_H2S, concentration_H2S, 10);
    Utils.float2String(conv_CH4, concentration_CH4, 10);
    #endif
}

// Измерение значений
void WaspMote::getMeasurements() {
    getMeteoValues();
    convGasValues();
}

// Инициализация сенсора температуры, влажности и давления BME280
void WaspMote::turnMeteON() {
    bme.ON();
}

// Получение данных с сенсора BME280
void WaspMote::getMeteoValues() {
    temp = bme.getTemperature();
    hum = bme.getHumidity();
    pres = bme.getPressure();
    Utils.float2String(temp, temperature, 6);
    Utils.float2String(hum, humidity, 6);
    Utils.float2String(pres, pressure, 6);
}

WaspMote WPM = WaspMote();
