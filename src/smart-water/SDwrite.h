#include <WaspUSB.h>
#include <WaspSD.h>
#include <WaspRTC.h>
#include <stdio.h>

class SDwrite {
  protected:
    uint8_t sd_answer;
    char filename[13];
    char foldername[13];
    char filepath[26];
    char writetime[20];
  public:
    SDwrite();
    void createFile();
    void writeToFile(char temp[20], char pHValue[20], char ECValue[20], char DOValue[20]);
};

extern SDwrite SDW;
