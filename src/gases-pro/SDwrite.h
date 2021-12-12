#include "WaspMote.h"
#include <WaspUSB.h>
#include <WaspSD.h>
#include <WaspRTC.h>
#include <stdio.h>
#include "toggle.h"

class SDwrite {
  public:
    uint8_t sd_answer;
    char filename[13];
    char writetime[20];
    
    SDwrite();
    void createFile();
    void writeToFile();
};

extern SDwrite SDW;
