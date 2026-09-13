#ifndef CONTROL_SERVO_H
#define CONTROL_SERVO_H
#include "esp_http_server.h"
void registercontrolHandler(httpd_handle_t server);
void initservo();
#endif
