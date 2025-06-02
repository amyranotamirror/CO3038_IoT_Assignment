#ifndef WIFI_HANDLER_H
#define WIFI_HANDLER_H

#include <WiFi.h>

#include "./core/config.h"
#include "./core/state.h"
#include "./core/utils.h"

extern WiFiClient wifiClient;

void InitWiFi();
void TaskWiFi(void *pvParameters);

#endif