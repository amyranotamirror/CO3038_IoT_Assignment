#ifndef THINGSBOARD_HANDLER_H
#define THINGSBOARD_HANDLER_H

#include <Arduino_MQTT_Client.h>
#include <HardwareSerial.h>
#include <ThingsBoard.h>
#include <WiFi.h>

#include "task_wifi.h"
#include "./core/config.h"

extern Arduino_MQTT_Client mqttClient;
extern ThingsBoard thingsboard;

void InitThingsBoard();
void TaskThingsBoard(void *pvParameters);

#endif