#ifndef STORAGE_H
#define STORAGE_H
//microSD card libraties
#include "FS.h"
#include "SD_MMC.h"
extern unsigned int pic_count;
//eeprom lib
#include "EEPROM.h"
void initMicroSDcard();
void eeprom_init();
#endif
