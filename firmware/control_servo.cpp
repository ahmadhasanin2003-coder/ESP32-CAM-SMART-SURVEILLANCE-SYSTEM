#include <ESP32Servo.h>
#include "control_servo.h"
#include <Arduino.h>
Servo myservo;
void initservo(){
  ESP32PWM::allocateTimer(2);
  myservo.setPeriodHertz(50);
  bool ok=myservo.attach(14,500,2400);
  Serial.println("result of servo is");
  Serial.println(ok);

  myservo.write(95);
}
static esp_err_t controlHandlerleft(httpd_req_t* req){
  httpd_resp_set_hdr(req,"Access-Control-Allow-Origin","*");
  Serial.println("left");
  myservo.write(110);
  delay(100);
  //myservo.write(95);
  httpd_resp_send(req,"left",HTTPD_RESP_USE_STRLEN);
  return ESP_OK;
}
static esp_err_t controlHandlerright(httpd_req_t* req){
  httpd_resp_set_hdr(req,"Access-Control-Allow-Origin","*");
  Serial.println("right");
  myservo.write(80);
  delay(100);
  //myservo.write(95);
    httpd_resp_send(req,"right",HTTPD_RESP_USE_STRLEN);
  return ESP_OK;
  
}
static esp_err_t controlHandlerstop(httpd_req_t* req){
  httpd_resp_set_hdr(req,"Access-Control-Allow-Origin","*");
  myservo.write(95);
  delay(100);
  httpd_resp_send(req,"stop",HTTPD_RESP_USE_STRLEN);
  return ESP_OK;
}
static httpd_uri_t control_uri_left={
  .uri="/control_left",
  .method=HTTP_GET,
  .handler=controlHandlerleft,
  .user_ctx=NULL
};
static httpd_uri_t control_uri_right={
  .uri="/control_right",
  .method=HTTP_GET,
  .handler=controlHandlerright,
  .user_ctx=NULL
};
static httpd_uri_t control_uri_stop={
  .uri="/control_stop",
  .method=HTTP_GET,
  .handler=controlHandlerstop,
  .user_ctx=NULL
};
void registercontrolHandler(httpd_handle_t server)
{
  httpd_register_uri_handler(server,&control_uri_left);
  httpd_register_uri_handler(server,&control_uri_right);
  httpd_register_uri_handler(server,&control_uri_stop);
}
