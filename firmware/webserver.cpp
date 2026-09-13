//libraries
#include <Arduino.h>
#include "webserver.h"
#include "esp_http_server.h"
#include <WiFi.h>
#include "stream.h"
#include "home.h"
//#include "webpage.h"
//#include "capture.h"
#include "control_servo.h"

//wifi-credentials
const char* ssid="xyz-2.4G";
const char* password="*******";

//http sever handle
static httpd_handle_t server_stream=NULL;
static httpd_handle_t server_camera=NULL;
void startWebServer(){
  //connect wifi
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println(WiFi.localIP());
  //configure http server
  httpd_config_t config=HTTPD_DEFAULT_CONFIG();
   if(httpd_start(&server_camera,&config)==ESP_OK){
    Serial.println("http server started for camera");
  }
  config.server_port+=1;
  config.ctrl_port+=1;
  //config.max_open_sockets=7;
  //config.max_uri_handlers=8;
  if(httpd_start(&server_stream,&config)==ESP_OK){
    Serial.println("http server started for streamimg");
  }
  //register
  registerHomeHandler(server_camera);
  //registerCaptureHandler(server_camera);
  registerStreamHandler(server_stream);
  registercontrolHandler(server_camera);
}
