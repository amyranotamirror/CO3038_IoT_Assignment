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

#include "task_ota.h"
#include "task_rpc.h"
#include "task_shared_attr.h"
#include "task_wifi.h"
#include "./core/config.h"
#include "./core/utils.h"

extern Client_Side_RPC<RPCAttributeConfig::MaxSubscription, RPCAttributeConfig::MaxRequestRPC> client_rpc;
extern Server_Side_RPC<RPCAttributeConfig::MaxSubscription, RPCAttributeConfig::MaxRPC> server_rpc;
extern Shared_Attribute_Update<RPCAttributeConfig::MaxSubscription, RPCAttributeConfig::maxAttribute> attr_update;
extern Attribute_Request<RPCAttributeConfig::MaxSubscription, RPCAttributeConfig::maxAttribute> attr_request;
extern OTA_Firmware_Update<> ota;
extern const std::array<IAPI_Implementation*, 5U> apis;

extern Arduino_MQTT_Client mqttClient;
extern ThingsBoard thingsboard;

void TaskThingsBoard(void *pvParameters);
void TaskThingsBoardLoop(void *pvParameters);

#endif