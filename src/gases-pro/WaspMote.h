#pragma once
#include <WaspSensorGas_Pro.h>
#include <WaspUtils.h>
#include "toggle.h"

class WaspMote {
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
    #elif defined MODEL_BLUE
    Gas gas_sensor_NH3{SOCKET_A};
    Gas gas_sensor_H2S{SOCKET_B};
    Gas gas_sensor_CH4{SOCKET_C};
    char concentration_NH3[20];
    char concentration_H2S[20];
    char concentration_CH4[20];
    #endif
    bmeGasesSensor bme;
    char temperature[20];
    char humidity[20];
    char pressure[20];

    WaspMote();
    void turnGasON();
    void turnGasOFF();
    void getGasValues();
    void turnMeteON();
    void getMeteoValues();
};

extern WaspMote WPM;