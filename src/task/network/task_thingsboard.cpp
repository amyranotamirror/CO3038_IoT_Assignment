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
      // Shared attributes
      thingsBoardState.isSharedAttributesRequested = false;
      thingsBoardState.isSharedAttributesRequestProcessed = false;
      // OTA
      thingsBoardState.isOTACurrentFirmwareSent = false;
    } else {
      if (thingsboard.connected()) {
        if (!thingsBoardState.isConnected) {
          LogInfo("ThingsBoard", "Established connection");
        }
        thingsBoardState.isConnected = true;
        thingsBoardState.isAttempting = false;
        thingsBoardState.connectionAttempts = 0;
        // RPC
        if (!thingsBoardState.isServerRPC) {
          bool newIsServerRPC = server_rpc.RPC_Subscribe(rpc_callbacks.cbegin(), rpc_callbacks.cend());
          if (newIsServerRPC) {
            LogSuccess("Server RPC", "subscribed successfully");
          } else {
            LogError("Server RPC", "can not subscribed");
          }
          thingsBoardState.isServerRPC = newIsServerRPC;
        }
        // Shared attributes
        if (!thingsBoardState.isSharedAttributesUpdated) {
          bool newIsSharedAttributesUpdated = attr_update.Shared_Attributes_Subscribe(shared_attribute_callback);
          if (newIsSharedAttributesUpdated) {
            LogSuccess("Shared attributes", "updated successfully");
          } else {
            LogError("Shared attributes", "can not updated");
          }
          thingsBoardState.isSharedAttributesUpdated = newIsSharedAttributesUpdated;
        }
        if (!thingsBoardState.isSharedAttributesRequested) {
          bool newIsSharedAttributesRequested = attr_request.Shared_Attributes_Request(attribute_request_callback);
          if (newIsSharedAttributesRequested) {
            LogSuccess("Shared attributes", "requested successfully");
          } else {
            LogError("Shared attributes", "can not requested");
          }
          thingsBoardState.isSharedAttributesRequested = newIsSharedAttributesRequested;
        }
        // OTA
        if (thingsBoardState.isSharedAttributesRequestProcessed) {
          if (!thingsBoardState.isOTACurrentFirmwareSent) {
            bool newIsOTACurrentFirmwareSent = ota.Firmware_Send_Info(OTAConfig::title, OTAConfig::version);
            if (newIsOTACurrentFirmwareSent) {
              LogSuccess("OTA current firmware", "sent successfully");
            } else {
              LogError("OTA current firmware", "can not sent");
            }
            thingsBoardState.isOTACurrentFirmwareSent = newIsOTACurrentFirmwareSent;
          }
          if (!thingsBoardState.isOTAUpdateRequestSent) {
            bool newIsOTAUpdateRequestSent = ota.Subscribe_Firmware_Update(ota_update_callback);
            if (newIsOTAUpdateRequestSent) {
              LogSuccess("OTA update request", "sent successfully");
            } else {
              LogError("OTA update request", "can not sent");
            }
            thingsBoardState.isOTAUpdateRequestSent = newIsOTAUpdateRequestSent;
          }
        }
      } else {
        if (!thingsBoardState.isAttempting) {
          LogInfo("ThingsBoard", "Connecting ...");
          thingsboard.disconnect();
          thingsboard.connect(ThingsBoardConfig::server, ThingsBoardConfig::token, ThingsBoardConfig::port);
          thingsBoardState.isAttempting = true;
          thingsBoardState.connectionAttempts = 0;
        } else {
          thingsBoardState.connectionAttempts++;
          if (thingsBoardState.connectionAttempts >= ThingsBoardConfig::maxConnectionAttempt) {
            LogError("ThingsBoard", "Failed to connect after max attempts");
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