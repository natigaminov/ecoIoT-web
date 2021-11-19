#include <WaspSensorGas_Pro.h>


Gas gas_PRO_sensor_A(SOCKET_A);
Gas gas_PRO_sensor_B(SOCKET_B);
Gas gas_PRO_sensor_C(SOCKET_C);
Gas gas_PRO_sensor_F(SOCKET_F);

bmeGasesSensor bme;


char concentration_A[20];
char concentration_B[20];
char concentration_C[20];
char concentration_F[20]; // Stores the concentration level in ppm

char temperature[20];  // Stores the temperature in ºC
char humidity[20];   // Stores the realitve humidity in %RH
char pressure[20];   // Stores the pressure in Pa


uint8_t sd_answer;

char smth[20];
char filename[23];

void setup() {
  
  // Open USB port
  USB.ON();

  // Set SD ON
  SD.ON();

  // Power on sensors
  //gas_PRO_sensor_A.ON();
  //gas_PRO_sensor_B.ON();
  //gas_PRO_sensor_F.ON();
  bme.ON();

  USB.println(F("Final test multi example"));

  // Powers RTC up, init I2C bus and read initial values
  USB.println(F("Init RTC"));
  RTC.ON();  
  USB.print(F("Time: "));
  USB.println(RTC.getTime());
  
  sprintf(filename, "%02u%02u%02u%02u.TXT", RTC.date, RTC.hour, RTC.minute, RTC.second);
  
  if(SD.create(filename)) {    
    USB.print(F("File created: "));
    USB.println(filename);
  }
  else {
    USB.println(F("File NOT created")); // only one file per second
  } 
  
  // First sleep time
  //PWR.deepSleep("00:00:02:00", RTC_OFFSET, RTC_ALM1_MODE1, ALL_ON);
  //delay(120000);
}


void loop() {

  // Power on sensors
  gas_PRO_sensor_A.ON();
  gas_PRO_sensor_B.ON();
  gas_PRO_sensor_C.ON();
  gas_PRO_sensor_F.ON();


  // Gas sensors needs a warm up time at least 120 seconds  
  // To reduce the battery consumption, use deepSleep instead delay
  // After 2 minutes, Waspmote wakes up thanks to the RTC Alarm
  //PWR.deepSleep("00:00:02:00", RTC_OFFSET, RTC_ALM1_MODE1, ALL_ON);
  delay(120000);

  Utils.float2String(gas_PRO_sensor_A.getConc(), concentration_A, 10);
  Utils.float2String(gas_PRO_sensor_B.getConc(), concentration_B, 10);
  Utils.float2String(gas_PRO_sensor_C.getConc(), concentration_C, 10);
  Utils.float2String(gas_PRO_sensor_F.getConc(), concentration_F, 10);

  // Read enviromental variables  
  Utils.float2String(bme.getTemperature(), temperature, 6);
  Utils.float2String(bme.getHumidity(), humidity, 6);
  Utils.float2String(bme.getPressure(), pressure, 6);

  // And print the values via USB
  sd_answer = SD.appendln(filename, "***************************************");
  if( sd_answer == 1 ){
    USB.println(F("\ndata saved"));
  }
  else {
    USB.println(F("\nappend error"));
  }
  
    SD.append(filename, "Time: ");
    SD.appendln(filename, RTC.getTime());
    
    SD.appendln(filename, "***");
       
    SD.append(filename, "Temperature: ");
    SD.append(filename, temperature);
    SD.appendln(filename, " C");
    USB.println(temperature);
    
    SD.append(filename, "RH: ");
    SD.append(filename, humidity);
    SD.appendln(filename, " %");
    USB.println(humidity);
    
    SD.append(filename, "Pressure: ");
    SD.append(filename, pressure);
    SD.appendln(filename," Pa");
    USB.println(pressure);
       
    SD.appendln(filename, "***");
    
    SD.append(filename, "A Gas concentration: ");
    SD.append(filename, concentration_A);
    SD.appendln(filename," ppm");
    USB.println(concentration_A);
    
    SD.append(filename, "B Gas concentration: ");
    SD.append(filename, concentration_B);
    SD.appendln(filename," ppm");
    USB.println(concentration_B);
    
    SD.append(filename, "C Gas concentration: ");
    SD.append(filename, concentration_C);
    SD.appendln(filename," ppm");
    USB.println(concentration_C);
    
    SD.append(filename, "F Gas concentration: ");
    SD.append(filename, concentration_F);
    SD.appendln(filename," ppm");
    USB.println(concentration_F);

  // Power off sensors. If there aren't more gas sensors powered,
  // turn off the board automatically
  gas_PRO_sensor_A.OFF();
  gas_PRO_sensor_B.OFF();
  gas_PRO_sensor_C.OFF();
  gas_PRO_sensor_F.OFF();
  
  SD.showFile(filename);
  
  // Go to deepsleep  
  // After 2 minutes, Waspmote wakes up thanks to the RTC Alarm
  //PWR.deepSleep("00:00:02:00", RTC_OFFSET, RTC_ALM1_MODE1, ALL_OFF);
  //delay(120000);
}
