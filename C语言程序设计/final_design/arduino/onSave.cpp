#include "framework.h"

#include "controller.h"
#include "global.h"

#ifdef TARGET_ARDUINO
#include <EEPROM.h>
#endif

int addr = 0;

int time_1=0,time_2=0,time_3=0,time_4=0,time_5=0,time_6=0;
void onSave()
{
    time_3=time_2;
    time_2=time_1;
    time_1=nowtime;

    time_6=time_5;
    time_5=time_4;
    time_4=milliseconds;
    #ifdef TARGET_ARDUINO
    EEPROM.write(addr,time_1);
    EEPROM.write(addr+1,time_2);
    EEPROM.write(addr+2,time_3);
    EEPROM.write(addr+3,time_4);
    EEPROM.write(addr+4,time_5);
    EEPROM.write(addr+5,time_6);
    #endif
    #ifdef TARGET_51MCU
    EEPROM_write(addr,time_1);
    EEPROM_write(addr+1,time_2);
    EEPROM_write(addr+2,time_3);
    EEPROM_write(addr+3,time_4);
    EEPROM_write(addr+4,time_5);
    EEPROM_write(addr+5,time_6);
    #endif
}
