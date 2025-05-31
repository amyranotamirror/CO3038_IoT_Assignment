#include "task_thingsboard.h"

Client_Side_RPC<1U, 2U> client_rpc;
Server_Side_RPC<1U, 0U> server_rpc;
Shared_Attribute_Update<1U, ThingsBoardConfig::maxAttribute> attr_update;
Attribute_Request<1U, ThingsBoardConfig::maxAttribute> attr_request;
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
    } else {
      if (thingsboard.connected()) {
        if (!thingsBoardState.isConnected) {
          LogInfo("ThingsBoard", "Connected to ThingsBoard.");
          // RPC
          if (!thingsBoardState.isServerRPC) {
            thingsBoardState.isServerRPC = server_rpc.RPC_Subscribe(callbacks.cbegin(), callbacks.cend());
            if (thingsBoardState.isServerRPC) {
              LogInfo("ThingsBoard", "Server RPC subscribed.");
            } else {
              LogError("ThingsBoard", "Failed to subscribe to Server RPC.");
            }
          }
          // Shared attributes
          if (!thingsBoardState.isSharedAttributesUpdated) {
            thingsBoardState.isSharedAttributesUpdated = attr_update.Shared_Attributes_Subscribe(shared_attribute_callback);
            if (thingsBoardState.isSharedAttributesUpdated) {
              LogInfo("ThingsBoard", "Shared attributes subscribed.");
            } else {
              LogError("ThingsBoard", "Failed to subscribe to Shared Attributes.");
            }
          }
          // if (!thingsBoardState.isSharedAttributesRequested) {
          //   thingsBoardState.isSharedAttributesRequested = attr_request.Shared_Attributes_Request(attribute_request_callback);
          //   Serial.print("[INFO] Shared attributes requested: "); Serial.println(thingsBoardState.isSharedAttributesRequested ? "succeeded" : "failed");
          // }
        }
        thingsBoardState.isConnected = true;
        thingsBoardState.isAttempting = false;
        thingsBoardState.connectionAttempts = 0;
      } else {
        if (!thingsBoardState.isAttempting) {
          LogInfo("ThingsBoard", "Connecting ...");
          thingsboard.disconnect();
          thingsboard.connect(ThingsBoardConfig::server, ThingsBoardConfig::token, ThingsBoardConfig::port);
          thingsBoardState.isAttempting = true;
          thingsBoardState.connectionAttempts = 0;
        } else {
          // Serial.print(".");
          thingsBoardState.connectionAttempts++;
          if (thingsBoardState.connectionAttempts >= ThingsBoardConfig::maxConnectionAttempt) {
            Serial.println();
            LogError("ThingsBoard", "Failed to connect to ThingsBoard after maximum attempts.");
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