#include "SDwrite.h"

/*
 * Создание и запись данных в файл формата .CSV
 *  _________________________________
 * | Time | Temp | Hum | Press |.....|
 * |______|______|_____|_______|.....|
 * |......|......|.....|.......|.....|
 * 
 */

SDwrite::SDwrite(){}

void SDwrite::createFile() {
  RTC.getTime();
  sprintf(filename, "%02u%02u%02u%02u.csv", RTC.month, RTC.date, RTC.hour, RTC.minute);
  if(SD.create(filename)) {
    USB.print(F("File created: "));
    USB.println(filename);
    sd_answer = SD.append(filename, "Time,Temp,Hum,Press,");
    if(sd_answer == 1){
      USB.println(F("\nData saved"));
    }else{
      USB.println(F("\nAppend data error!"));
    }
    #ifdef MODEL_GREEN
    SD.appendln(filename, "CO,NO,CO2,NO2");
    #elif defined MODEL_BLUE
    SD.appendln(filename, "NH3,H2S,CH4");
    #endif
  }else{
    USB.println(F("File NOT created"));
  }
}

void SDwrite::writeToFile() {
  RTC.getTime();
  sprintf(writetime, "20%02u-%02u-%02u %02u:%02u:%02u", RTC.year, RTC.month, RTC.date, RTC.hour, RTC.minute, RTC.second);
  SD.append(filename, writetime);
  SD.append(filename, ",");
  SD.append(filename, WPM.temperature);
  SD.append(filename, ",");
  SD.append(filename, WPM.humidity);
  SD.append(filename, ",");
  SD.append(filename, WPM.pressure);
  SD.append(filename,",");
  #ifdef MODEL_GREEN
  SD.append(filename, WPM.concentration_CO);
  SD.append(filename,",");
  SD.append(filename, WPM.concentration_NO);
  SD.append(filename,",");
  SD.append(filename, WPM.concentration_CO2);
  SD.append(filename,",");
  SD.appendln(filename, WPM.concentration_NO2);
  #elif defined MODEL_BLUE
  SD.append(filename, WPM.concentration_NH3);
  SD.append(filename,",");
  SD.append(filename, WPM.concentration_H2S);
  SD.append(filename,",");
  SD.appendln(filename, WPM.concentration_CH4);
  #endif

  SD.showFile(filename);
}

SDwrite SDW = SDwrite();
