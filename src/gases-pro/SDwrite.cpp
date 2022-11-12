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
  sprintf(foldername, "%02u-%02u-%02u", RTC.year, RTC.month, RTC.date);
  SD.mkdir(foldername);
  sprintf(filename, "%02u-%02u-%02u.csv", RTC.hour, RTC.minute, RTC.second);
  sprintf(filepath, "%s/%s", foldername, filename);
  if(SD.create(filepath)) {
    USB.print(F("File created: "));
    USB.println(filepath);
    sd_answer = SD.append(filepath, "Time,Temp,Hum,Press,");
    if(sd_answer == 1){
      USB.println(F("\nData saved"));
    }else{
      USB.println(F("\nAppend data error!"));
    }
    #ifdef MODEL_GREEN
    SD.appendln(filepath, "CO,NO,CO2,NO2");
    #elif defined MODEL_BLUE
    SD.appendln(filepath, "NH3,H2S,CH4");
    #endif
  }else{
    USB.println(F("File NOT created"));
  }
}

void SDwrite::writeToFile() {
  RTC.getTime();
  sprintf(writetime, "20%02u-%02u-%02u %02u:%02u:%02u", RTC.year, RTC.month, RTC.date, RTC.hour, RTC.minute, RTC.second);
  SD.append(filepath, writetime);
  SD.append(filepath, ",");
  SD.append(filepath, WPM.temperature);
  SD.append(filepath, ",");
  SD.append(filepath, WPM.humidity);
  SD.append(filepath, ",");
  SD.append(filepath, WPM.pressure);
  SD.append(filepath,",");
  #ifdef MODEL_GREEN
  SD.append(filepath, WPM.concentration_CO);
  SD.append(filepath,",");
  SD.append(filepath, WPM.concentration_NO);
  SD.append(filepath,",");
  SD.append(filepath, WPM.concentration_CO2);
  SD.append(filepath,",");
  SD.appendln(filepath, WPM.concentration_NO2);
  #elif defined MODEL_BLUE
  SD.append(filepath, WPM.concentration_NH3);
  SD.append(filepath,",");
  SD.append(filepath, WPM.concentration_H2S);
  SD.append(filepath,",");
  SD.appendln(filepath, WPM.concentration_CH4);
  #endif

  SD.showFile(filepath);
}

char* SDwrite::getFilename() {
  return filename;
}

SDwrite SDW = SDwrite();
