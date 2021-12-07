#include "SDwrite.h"

SDwrite::SDwrite(){}

void SDwrite::createFile() {
  USB.print(F("Time: "));
  USB.println(RTC.getTime());
  sprintf(filename, "%02u%02u%02u.csv", RTC.date, RTC.hour, RTC.minute);
  if(SD.create(filename)) {    
    USB.print(F("File created: "));
    USB.println(filename);
  }else{
    USB.println(F("File NOT created")); // only one file per second
  }
}

void SDwrite::writeToFile() {
  sd_answer = SD.appendln(filename, "***");
  if( sd_answer == 1 ){
    USB.println(F("\ndata saved"));
  }else{
    USB.println(F("\nappend error"));
  }
  SD.append(filename, "Time: ");
  SD.appendln(filename, RTC.getTime());
  
  SD.appendln(filename, "***");
     
  SD.append(filename, "Temperature: ");
  SD.append(filename, WPM.temperature);
  SD.appendln(filename, " C");
  USB.println(WPM.temperature);
  
  SD.append(filename, "RH: ");
  SD.append(filename, WPM.humidity);
  SD.appendln(filename, " %");
  USB.println(WPM.humidity);
  
  SD.append(filename, "Pressure: ");
  SD.append(filename, WPM.pressure);
  SD.appendln(filename," Pa");
  USB.println(WPM.pressure);
     
  SD.appendln(filename, "***");
  
  #ifdef MODEL_GREEN
  SD.append(filename, "CO gas concentration: ");
  SD.append(filename, WPM.concentration_CO);
  SD.appendln(filename," ppm");
  USB.println(WPM.concentration_CO);
  
  SD.append(filename, "NO gas concentration: ");
  SD.append(filename, WPM.concentration_NO);
  SD.appendln(filename," ppm");
  USB.println(WPM.concentration_NO);
  
  SD.append(filename, "CO2 gas concentration: ");
  SD.append(filename, WPM.concentration_CO2);
  SD.appendln(filename," ppm");
  USB.println(WPM.concentration_CO2);
  
  SD.append(filename, "NO2 gas concentration: ");
  SD.append(filename, WPM.concentration_NO2);
  SD.appendln(filename," ppm");
  USB.println(WPM.concentration_NO2);
  #elif defined MODEL_BLUE
  SD.append(filename, "NH3 gas concentration: ");
  SD.append(filename, WPM.concentration_NH3);
  SD.appendln(filename," ppm");
  USB.println(WPM.concentration_NH3);
  
  SD.append(filename, "H2S gas concentration: ");
  SD.append(filename, WPM.concentration_H2S);
  SD.appendln(filename," ppm");
  USB.println(WPM.concentration_H2S);
  
  SD.append(filename, "CH4 gas concentration: ");
  SD.append(filename, WPM.concentration_CH4);
  SD.appendln(filename," ppm");
  USB.println(WPM.concentration_CH4);
  #endif
  SD.showFile(filename);
}

SDwrite SDW = SDwrite();