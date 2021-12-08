#include "WaspMote.h"
#include <WaspUSB.h>
#include <WaspSD.h>
#include <WaspRTC.h>
#include <stdio.h>
#include "toggle.h"

class SDwrite {
  private:
    uint8_t sd_answer;
    char filename[20];
  public:
    SDwrite();
    void createFile();
    void writeToFile();
};

extern SDwrite SDW;