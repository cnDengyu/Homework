#include "framework.h"
#include "controller.h"
#include "global.h"

#ifdef TARGET_ARDUINO
#include <EEPROM.h>
#endif

void onLoad()
{  
  static int times=1;
  #ifdef TARGET_ARDUINO
    time_1 = EEPROM.read(addr);
    time_2 = EEPROM.read(addr+1);
    time_3 = EEPROM.read(addr+2);
    time_4 = EEPROM.read(addr+3);
    time_5 = EEPROM.read(addr+4);
    time_6 = EEPROM.read(addr+5);
  #endif
  #ifdef TARGET_51MCU
    time_1 = EEPROM_read(addr);
    time_2 = EEPROM_read(addr+1);
    time_3 = EEPROM_read(addr+2);
    time_4 = EEPROM_read(addr+3);
    time_5 = EEPROM_read(addr+4);
    time_6 = EEPROM_read(addr+5);
  #endif
   if (times==1)
   {
    nowtime = time_1;
    milliseconds = time_4;
    times++;
   }
   else if (times==2)
   {
    nowtime = time_2;
    milliseconds = time_5;
    times++;
   }
   else if (times==3)
   {
    nowtime = time_3;
    milliseconds = time_6;
    times++;
   }
   else
   {
    nowtime = time_1;
    milliseconds = time_4;
    times=2;
   }
}
