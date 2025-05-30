#include "task_thingsboard.h"

Client_Side_RPC<RPCAttributeConfig::MaxSubscription, RPCAttributeConfig::MaxRequestRPC> client_rpc;
Server_Side_RPC<RPCAttributeConfig::MaxSubscription, RPCAttributeConfig::MaxRPC> server_rpc;
Shared_Attribute_Update<RPCAttributeConfig::MaxSubscription, RPCAttributeConfig::maxAttribute> attr_update;
Attribute_Request<RPCAttributeConfig::MaxSubscription, RPCAttributeConfig::maxAttribute> attr_request;
OTA_Firmware_Update<> ota;
const std::array<IAPI_Implementation*, 5U> apis = {&client_rpc, &server_rpc, &attr_update, &attr_request, &ota};

Arduino_MQTT_Client mqttClient(wifiClient);
ThingsBoard thingsboard(mqttClient, MessageConfig::maxMessageReceiveSize, MessageConfig::maxMessageSendSize, Default_Max_Stack_Size, apis);

void TaskThingsBoard(void *pvParameters) {
  while (1) {
    if (!wifiState.isConnected) {
      // Connection
      thingsboard.disconnect();
      thingsBoardState.isConnected = false;
      thingsBoardState.isAttempting = false;
      thingsBoardState.connectionAttempts = 0;
      // RPC
      server_rpc.RPC_Unsubscribe();
      thingsBoardState.isServerRPC = false;
      // Shared attributes
      attr_update.Shared_Attributes_Unsubscribe();
      thingsBoardState.isSharedAttributesUpdated = false;
      thingsBoardState.isSharedAttributesRequested = false;
      thingsBoardState.isSharedAttributesRequestProcessed = false;
    } else {
      if (thingsboard.connected()) {
        if (!thingsBoardState.isConnected) {
          Serial.println();
          Serial.println("[INFO] ThingsBoard: Established connection.");
          // RPC
          if (!thingsBoardState.isServerRPC) {
            thingsBoardState.isServerRPC = server_rpc.RPC_Subscribe(callbacks.cbegin(), callbacks.cend());
            Serial.print("[INFO] Server RPC subscribed: "); Serial.println(thingsBoardState.isServerRPC ? "succeeded" : "failed");
          }
          // Shared attributes
          if (!thingsBoardState.isSharedAttributesUpdated) {
            thingsBoardState.isSharedAttributesUpdated = attr_update.Shared_Attributes_Subscribe(shared_attribute_callback);
            Serial.print("[INFO] Shared attributes updated: "); Serial.println(thingsBoardState.isSharedAttributesUpdated ? "succeeded" : "failed");
          }
          if (!thingsBoardState.isSharedAttributesRequested) {
            thingsBoardState.isSharedAttributesRequested = attr_request.Shared_Attributes_Request(attribute_request_callback);
            Serial.print("[INFO] Shared attributes requested: "); Serial.println(thingsBoardState.isSharedAttributesRequested ? "succeeded" : "failed");
          }
        }
        thingsBoardState.isConnected = true;
        thingsBoardState.isAttempting = false;
        thingsBoardState.connectionAttempts = 0;
      } else {
        if (!thingsBoardState.isAttempting) {
          Serial.print("[UPDATE] ThingsBoard: Connecting ...");
          thingsboard.disconnect();
          thingsboard.connect(ThingsBoardConfig::server, ThingsBoardConfig::token, ThingsBoardConfig::port);
          thingsBoardState.isAttempting = true;
          thingsBoardState.connectionAttempts = 0;
        } else {
          Serial.print(".");
          thingsBoardState.connectionAttempts++;
          if (thingsBoardState.connectionAttempts >= ThingsBoardConfig::maxConnectionAttempt) {
            Serial.println();
            Serial.println("[ERROR] ThingsBoard: Failed to connect. Will retry later.");
            WiFi.disconnect();
            thingsBoardState.isAttempting = false;
          }
        }
        thingsBoardState.isConnected = false;
      }
    }
    if (thingsBoardState.isAttempting) {
      vTaskDelay(ThingsBoardConfig::connectionAttemptInterval);
    } else {
      vTaskDelay(ThingsBoardConfig::reconnectInterval);
    }
  }
}

void TaskThingsBoardLoop(void *pvParameters) {
  while(1) {
    thingsboard.loop();
    vTaskDelay(SystemConfig::defaultTaskDelay);
  }
}