#include "storage.h"
#include <Arduino.h>
//1byte for eeprom space
#define eeprom_size 1
//pic_count
unsigned int pic_count=0;

void eeprom_init(){
  //eeprom init
  EEPROM.begin(eeprom_size);
  pic_count=EEPROM.read(0);
}
/*
void initMicroSDcard(){
  //start sd card
  Serial.println("mounting sd card");
  if(!SD_MMC.begin()){
    Serial.println("micro sd card mounting failed");
    return;
  }
  uint8_t cardType=SD_MMC.cardType();
  if(cardType == CARD_NONE){
    Serial.println("no sdcard found");
    return;
  }
}
*/
