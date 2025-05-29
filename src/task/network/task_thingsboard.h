#ifndef THINGSBOARD_HANDLER_H
#define THINGSBOARD_HANDLER_H

#include <Arduino_MQTT_Client.h>
#include <Attribute_Request.h>
#include <Client_Side_RPC.h>
#include <HardwareSerial.h>
#include <OTA_Firmware_Update.h>
#include <Server_Side_RPC.h>
#include <Shared_Attribute_Update.h>
#include <ThingsBoard.h>
#include <WiFi.h>

#include "task_rpc.h"
#include "task_shared_attr.h"
#include "task_wifi.h"
#include "./core/config.h"

extern Client_Side_RPC<1U, 2U> client_rpc;
extern Server_Side_RPC<1U, 0U> server_rpc;
extern Shared_Attribute_Update<1U, ThingsBoardConfig::maxAttribute> attr_update;
extern Attribute_Request<1U, ThingsBoardConfig::maxAttribute> attr_request;
extern OTA_Firmware_Update<> ota;
extern const std::array<IAPI_Implementation*, 5U> apis;

extern Arduino_MQTT_Client mqttClient;
extern ThingsBoard thingsboard;

void TaskThingsBoard(void *pvParameters);
void TaskThingsBoardLoop(void *pvParameters);

#endif