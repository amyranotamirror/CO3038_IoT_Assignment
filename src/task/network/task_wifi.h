#ifndef WIFI_HANDLER_H
#define WIFI_HANDLER_H

#include <HardwareSerial.h>
#include <WiFi.h>
#include "./core/config.h"

extern WiFiClient wifiClient;

void InitWiFi();
void TaskWiFi(void *pvParameters);

#endif