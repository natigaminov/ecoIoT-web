#include <WaspUSB.h>
#include <WaspSD.h>
#include <WaspRTC.h>
#include <stdio.h>

class SDwrite {
  protected:
    uint8_t sd_answer;
    char filename[13];
    char writetime[20];
  public:
    SDwrite();
    void createFile();
    void writeToFile(char Ammonium[26], char Nitrite[26], char Nitrate[26]);
};

extern SDwrite SDW;
