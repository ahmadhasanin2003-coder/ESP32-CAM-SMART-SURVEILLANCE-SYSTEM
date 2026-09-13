//#include "storage.h"
#include "camera.h"
#include "webserver.h"
#include <Arduino.h>
#include "control_servo.h"

void setup() {
  // 
  Serial.begin(115200);
  initservo();
  configESPcamera();
  //initMicroSDcard();
  //eeprom_init();
  startWebServer();


}

void loop() {
  // put your main code here, to run repeatedly:
}
