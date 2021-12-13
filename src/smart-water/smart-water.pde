#include <WaspSensorSW.h>
#include "SDwrite.h"

char temp[20];

// pH sensor
float pHVol;
char pHValue[20];
// pH sensor calibration values
#define cal_point_10  2.0144176483
#define cal_point_7   2.1123514175
#define cal_point_4   2.2006096839

// Conductivity sensor
float ECRes;
char ECValue[20];

// Values used to calibrate the conductivity sensor
#define point1_cond 84
#define point2_cond 1413
// Points of the calibration the conductivity sensor
#define point1_cal 13738.4707031250
#define point2_cal 820.3084106445

// Dissolved Oxygen (DO) sensor
float DOVol;
char DOValue[20];
// Calibration of the DO sensor in normal air
#define air_calibration 3.3985300064
// Calibration of the DO sensor under 0% solution
#define zero_calibration 0.1873572444


// Temperature at which calibration was carried out (for pH sensor)
#define cal_temp 20.1

pt1000Class temperatureSensor;
pHClass pHSensor;
conductivityClass conductivitySensor;
DOClass DOSensor;

void setup()
{
  // Open USB port
  USB.ON();
  // Set SD ON
  SD.ON();
  // Turn ON the Smart Water sensor board 
  Water.ON();
  
  USB.println(F("Initialization"));
  
  // Powers RTC up, init I2C bus and read initial values
  RTC.ON();  
  USB.print(F("Time: "));
  USB.println(RTC.getTime());

  SDW.createFile();
  
  // Store the calibration values
  pHSensor.setCalibrationPoints(cal_point_10, cal_point_7, cal_point_4, cal_temp);
  conductivitySensor.setCalibrationPoints(point1_cond, point1_cal, point2_cond, point2_cal);
  DOSensor.setCalibrationPoints(air_calibration, zero_calibration); 
}

void loop()
{ 
  
  // Read the temperature sensor
  Utils.float2String(temperatureSensor.readTemperature(), temp, 4);
  // Read the pH sensor (voltage value)
  pHVol = pHSensor.readpH();
  // Convert the value read with the information obtained in calibration
  Utils.float2String(pHSensor.pHConversion(pHVol, temperatureSensor.readTemperature()), pHValue, 4);
  // Reading of the Conductivity sensor
  ECRes = conductivitySensor.readConductivity();
  // Conversion from resistance into us/cm
  Utils.float2String(conductivitySensor.conductivityConversion(ECRes), ECValue, 4);
  // Reading of the DO sensor
  DOVol = DOSensor.readDO();
  // Conversion from volts into dissolved oxygen percentage
  Utils.float2String(DOSensor.DOConversion(DOVol), DOValue, 4);
  
  // And print the values via USB
  SDW.writeToFile(temp, pHValue, ECValue, DOValue);
  
  USB.print(F("Temperature: "));
  USB.print(temp);
  USB.println(F(" C"));  

  USB.print(F("pH Estimated: "));
  USB.print(pHValue);
  USB.println(F(" pH"));

  USB.print(F("Conductivity of the solution: "));
  USB.print(ECValue); 
  USB.println(" (uS/cm)");

  USB.print(F("DO Percentage: "));
  USB.print(DOValue);
  USB.println(" %");
}
