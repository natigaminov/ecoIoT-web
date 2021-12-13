#include <smartWaterIons.h>
#include "SDwrite.h"
// All Ion sensors can be connected in the four sockets
socket1Class ammoniumSensorB273;
char concentrationAmmonium[26];
socket2Class nitriteSensorB391;
char concentrationNitrite[26];
socket3Class nitrateSensorB351;
char concentrationNitrate[26];

// Calibration concentrations solutions used in the process Ammonium
#define point1_ammonium 4
#define point2_ammonium 20
#define point3_ammonium 40
// Calibration concentrations solutions used in the process Nitrite
#define point1_nitrite 10
#define point2_nitrite 100
#define point3_nitrite 1000
// Calibration concentrations solutions used in the process Nitrate
#define point1_nitrate 132
#define point2_nitrate 660
#define point3_nitrate 1320
// Calibration Voltage values Ammonium
#define point1_volt_ammonium 2.8590801239
#define point2_volt_ammonium 3.0262672901  
#define point3_volt_ammonium 3.0851874351
// Calibration Voltage values Nitrite
#define point1_volt_nitrite 3.0339171886
#define point2_volt_nitrite 2.8811624526
#define point3_volt_nitrite 2.7621338367
// Calibration Voltage values Nitrate
#define point1_volt_nitrate 3.2066533565
#define point2_volt_nitrate 3.0251250267
#define point3_volt_nitrate 2.9559038162
// Define the number of calibration points
#define numPoints 3
float calConcentrationsAmmonium[] = {point1_ammonium, point2_ammonium, point2_ammonium};
float calVoltagesAmmonium[] = {point1_volt_ammonium, point2_volt_ammonium, point3_volt_ammonium};

float calConcentrationsNitrite[] = {point1_nitrite, point2_nitrite, point3_nitrite};
float calVoltagesNitrite[] = {point1_volt_nitrite, point2_volt_nitrite, point3_volt_nitrite};

float calConcentrationsNitrate[] = {point1_nitrate, point2_nitrate, point3_nitrate};
float calVoltagesNitrate[] = {point1_volt_nitrate, point2_volt_nitrate, point3_volt_nitrate};

void setup()
{
  // Open USB port
  USB.ON();
  SD.ON();
  // Turn ON the Smart Water Ions Board and USB
  SWIonsBoard.ON();

  USB.println(F("Initialization"));
  
  // Powers RTC up, init I2C bus and read initial values
  RTC.ON();
  USB.print(F("Time: "));
  USB.println(RTC.getTime());

  SDW.createFile();
  
    // Store the calibration values
  ammoniumSensorB273.setCalibrationPoints(calVoltagesAmmonium, calConcentrationsAmmonium, numPoints);
  nitriteSensorB391.setCalibrationPoints(calVoltagesNitrite, calConcentrationsNitrite, numPoints);
  nitrateSensorB351.setCalibrationPoints(calVoltagesNitrate, calConcentrationsNitrate, numPoints);
  
}
void loop()
{
  // Reading of the Ammonium sensor
  float ammoniumVoltage = ammoniumSensorB273.read();
  // Conversion from resistance into mg * L-1
  Utils.float2String(ammoniumSensorB273.calculateConcentration(ammoniumVoltage), concentrationAmmonium, 6);
  // Reading of the Nitrite sensor
  float nitriteVoltage = nitriteSensorB391.read();
  // Conversion from resistance into mg * L-1
  Utils.float2String(nitriteSensorB391.calculateConcentration(nitriteVoltage), concentrationNitrite, 6);
  // Reading of the Nitrate sensor
  float nitrateVoltage = nitrateSensorB351.read();
  // Conversion from resistance into mg * L-1
  Utils.float2String(nitrateSensorB351.calculateConcentration(nitrateVoltage), concentrationNitrate, 6);

  SDW.writeToFile(concentrationAmmonium, concentrationNitrite, concentrationNitrate);
  
  // Print the output values
  USB.print(F("Ammonium: "));
  USB.print(concentrationAmmonium);
  USB.println(F(" mg * L-1"));  

  USB.print(F("Nitrite: "));
  USB.print(concentrationNitrite);
  USB.println(F(" mg * L-1"));  

  USB.print(F("Nitrate: "));
  USB.print(concentrationNitrate);
  USB.println(F(" mg * L-1"));  
  delay(1000);  
}
