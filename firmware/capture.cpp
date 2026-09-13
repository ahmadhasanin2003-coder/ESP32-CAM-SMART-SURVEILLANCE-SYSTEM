#include "capture.h"
//#include "webpage.h"
#include "camera.h"
#include <Arduino.h>
#include "storage.h"
void takepic(String path){
  //setup frame buffer
  camera_fb_t* fb = esp_camera_fb_get();
  if(!fb){
    Serial.println("camera capture failed");
    return;
  }
  //save picture to sd card
  fs::FS &fs=SD_MMC;
  File file =fs.open(path.c_str(),FILE_WRITE);
  if(!file){
    Serial.println("failed to open in write mode");
  }
  else{
    file.write(fb->buf, fb->len);
    Serial.printf("saved file to path: %s\n",path.c_str());
  //close the file
  file.close();
  }
  esp_camera_fb_return(fb);//returning the frame buffer back to driver for reuse
}
static esp_err_t CaptureHandler(httpd_req_t* req){
  httpd_resp_set_hdr(req,"Access-Control-Allow-Origin","*");
  httpd_resp_set_type(req,"text/plain");
  httpd_resp_send(req,"photo_clicked!!!",HTTPD_RESP_USE_STRLEN);
 
  
  String path="/image"+String(pic_count)+".jpg";
  //take and save pic
  takepic(path);
  //update eeprom counter
  //pic_count++;
  EEPROM.write(0,pic_count);
  EEPROM.commit();
  pic_count=EEPROM.read(0)+1;  
  return ESP_OK;
}
static httpd_uri_t capture_uri={
  .uri="/capture",
  .method=HTTP_GET,
  .handler=CaptureHandler,
  .user_ctx=NULL
};
void registerCaptureHandler(httpd_handle_t server)
{
  httpd_register_uri_handler(server,&capture_uri);
}
