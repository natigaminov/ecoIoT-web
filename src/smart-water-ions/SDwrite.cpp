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
  sprintf(filename, "%02u%02u%02u%02u.csv", RTC.month, RTC.date, RTC.hour, RTC.minute);
  if(SD.create(filename)) {
    USB.print(F("File created: "));
    USB.println(filename);
    sd_answer = SD.appendln(filename, "Time,Ammonium,Nitrite,Nitrate");
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
  SD.append(filename, writetime);
  SD.append(filename, ",");
  SD.append(filename, Ammonium);
  SD.append(filename, ",");
  SD.append(filename, Nitrite);
  SD.append(filename, ",");
  SD.appendln(filename, Nitrate);

  // SD.showFile(filename);
}

SDwrite SDW = SDwrite();
