#include "WaspMote.h"

WaspMote::WaspMote(){}

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

void WaspMote::getGasValues() {
  #ifdef MODEL_GREEN
  Utils.float2String(gas_sensor_CO.getConc(), concentration_CO, 10);
  Utils.float2String(gas_sensor_NO.getConc(), concentration_NO, 10);
  Utils.float2String(gas_sensor_CO2.getConc(), concentration_CO2, 10);
  Utils.float2String(gas_sensor_NO2.getConc(), concentration_NO2, 10);
  #elif defined MODEL_BLUE
  Utils.float2String(gas_sensor_NH3.getConc(), concentration_NH3, 10);
  Utils.float2String(gas_sensor_H2S.getConc(), concentration_H2S, 10);
  Utils.float2String(gas_sensor_CH4.getConc(), concentration_CH4, 10);
  #endif
}

void WaspMote::turnMeteON() {
  bme.ON();
}

void WaspMote::getMeteoValues() {
  Utils.float2String(bme.getTemperature(), temperature, 6);
  Utils.float2String(bme.getHumidity(), humidity, 6);
  Utils.float2String(bme.getPressure(), pressure, 6);
}

WaspMote WPM = WaspMote();