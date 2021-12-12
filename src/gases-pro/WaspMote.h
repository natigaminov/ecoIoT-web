#pragma once
#include <WaspSensorGas_Pro.h>
#include <WaspUtils.h>
#include "toggle.h"

class WaspMote {
  protected:
    void convGasValues();
    float ppmToMgm(float ppm, float molar, float temp, float pres);
  public:
    #ifdef MODEL_GREEN
    Gas gas_sensor_CO{SOCKET_A};
    Gas gas_sensor_NO{SOCKET_B};
    Gas gas_sensor_CO2{SOCKET_C};
    Gas gas_sensor_NO2{SOCKET_F};
    char concentration_CO[20];
    char concentration_NO[20];
    char concentration_CO2[20];
    char concentration_NO2[20];
    float conv_CO, conv_NO, conv_CO2, conv_NO2;
    #elif defined MODEL_BLUE
    Gas gas_sensor_NH3{SOCKET_A};
    Gas gas_sensor_H2S{SOCKET_B};
    Gas gas_sensor_CH4{SOCKET_C};
    char concentration_NH3[20];
    char concentration_H2S[20];
    char concentration_CH4[20];
    float conv_NH3, conv_H2S, conv_CH4;
    #endif
    bmeGasesSensor bme;
    char temperature[20];
    char humidity[20];
    char pressure[20];
    float temp, hum, pres;

    WaspMote();
    void turnGasON();
    void turnGasOFF();
    void turnMeteON();
    void getMeteoValues();
    void getMeasurements();
};

// объявляем внешнее имя заранее созданного объекта класса
extern WaspMote WPM;
