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
  sprintf(foldername, "%02u-%02u-%02u", RTC.year, RTC.month, RTC.date);
  SD.mkdir(foldername);
  sprintf(filename, "%02u-%02u-%02u.csv", RTC.hour, RTC.minute, RTC.second);
  sprintf(filepath, "%s/%s", foldername, filename);
  if(SD.create(filepath)) {
    USB.print(F("File created: "));
    USB.println(filepath);
    sd_answer = SD.appendln(filepath, "Time,Temp,pH Estimated,Conductivity,DO Percent");
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
  SD.append(filepath, writetime);
  SD.append(filepath, ",");
  SD.append(filepath, temp);
  SD.append(filepath, ",");
  SD.append(filepath, pHValue);
  SD.append(filepath, ",");
  SD.append(filepath, ECValue);
  SD.append(filepath,",");
  SD.appendln(filepath, DOValue);

  // SD.showFile(filepath);
}

SDwrite SDW = SDwrite();
