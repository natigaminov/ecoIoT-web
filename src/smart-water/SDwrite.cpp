#include "SDwrite.h"

/*
 * Создание и запись данных в файл формата .CSV
 *  _______________________________________
 * | Time | Temp | pHValue | ECValue |.....|
 * |______|______|_________|_________|.....|
 * |......|......|.........|.........|.....|
 * 
 */

SDwrite::SDwrite(){}

void SDwrite::createFile() {
  RTC.getTime();
  sprintf(filename, "%02u%02u%02u%02u.csv", RTC.month, RTC.date, RTC.hour, RTC.minute);
  if(SD.create(filename)) {
    USB.print(F("File created: "));
    USB.println(filename);
    sd_answer = SD.appendln(filename, "Time,Temp,pH Estimated,Conductivity,DO Percent");
    if(sd_answer == 1){
      USB.println(F("\nData saved"));
    }else{
      USB.println(F("\nAppend data error!"));
    }
  }else{
    USB.println(F("File NOT created"));
  }
}

void SDwrite::writeToFile(char temp[20], char pHValue[20], char ECValue[20], char DOValue[20]) {
  RTC.getTime();
  sprintf(writetime, "20%02u-%02u-%02u %02u:%02u:%02u", RTC.year, RTC.month, RTC.date, RTC.hour, RTC.minute, RTC.second);
  SD.append(filename, writetime);
  SD.append(filename, ",");
  SD.append(filename, temp);
  SD.append(filename, ",");
  SD.append(filename, pHValue);
  SD.append(filename, ",");
  SD.append(filename, ECValue);
  SD.append(filename,",");
  SD.appendln(filename, DOValue);

  // SD.showFile(filename);
}

SDwrite SDW = SDwrite();
