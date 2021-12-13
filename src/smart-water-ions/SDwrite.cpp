#include "SDwrite.h"

/*
 * Создание и запись данных в файл формата .CSV
 *  ________________________________________
 * | Time | Temp | Ammonium | Nitrite |.....|
 * |______|______|__________|_________|.....|
 * |......|......|..........|.........|.....|
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
    sd_answer = SD.appendln(filepath, "Time,Ammonium,Nitrite,Nitrate");
    if(sd_answer == 1){
      USB.println(F("\nData saved"));
    }else{
      USB.println(F("\nAppend data error!"));
    }
  }else{
    USB.println(F("File NOT created"));
  }
}

void SDwrite::writeToFile(char Ammonium[26], char Nitrite[26], char Nitrate[26]) {
  RTC.getTime();
  sprintf(writetime, "20%02u-%02u-%02u %02u:%02u:%02u", RTC.year, RTC.month, RTC.date, RTC.hour, RTC.minute, RTC.second);
  SD.append(filepath, writetime);
  SD.append(filepath, ",");
  SD.append(filepath, Ammonium);
  SD.append(filepath, ",");
  SD.append(filepath, Nitrite);
  SD.append(filepath, ",");
  SD.appendln(filepath, Nitrate);

  // SD.showFile(filepath);
}

SDwrite SDW = SDwrite();
