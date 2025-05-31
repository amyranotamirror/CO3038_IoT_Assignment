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
          Serial.println();
          LogInfo("ThingsBoard", "Established connection");
        }
        thingsBoardState.isConnected = true;
        thingsBoardState.isAttempting = false;
        thingsBoardState.connectionAttempts = 0;
// RPC
if (!thingsBoardState.isServerRPC) {
  thingsBoardState.isServerRPC = server_rpc.RPC_Subscribe(callbacks.cbegin(), callbacks.cend());
  if (thingsBoardState.isServerRPC) {
    LogSuccess("Server RPC", "subscribed successfully");
  } else {
    LogError("Server RPC", "can not subscribed");
  }
}
// Shared attributes
if (!thingsBoardState.isSharedAttributesUpdated) {
  thingsBoardState.isSharedAttributesUpdated = attr_update.Shared_Attributes_Subscribe(shared_attribute_callback);
  if (thingsBoardState.isSharedAttributesUpdated) {
    LogSuccess("Shared attributes", "updated successfully");
  } else {
    LogError("Shared attributes", "can not updated");
  }
}
if (!thingsBoardState.isSharedAttributesRequested) {
  thingsBoardState.isSharedAttributesRequested = attr_request.Shared_Attributes_Request(attribute_request_callback);
  if (thingsBoardState.isSharedAttributesRequested) {
    LogSuccess("Shared attributes", "requested successfully");
  } else {
    LogError("Shared attributes", "can not requested");
  }
}
// OTA
if (thingsBoardState.isSharedAttributesRequestProcessed) {
  if (!thingsBoardState.isOTACurrentFirmwareSent) {
    thingsBoardState.isOTACurrentFirmwareSent = ota.Firmware_Send_Info(OTAConfig::title, OTAConfig::version);
    if (thingsBoardState.isOTACurrentFirmwareSent) {
      LogSuccess("OTA current firmware", "sent successfully");
    } else {
      LogError("OTA current firmware", "can not sent");
    }
  }
  if (!thingsBoardState.isOTAUpdateRequestSent) {
    thingsBoardState.isOTAUpdateRequestSent = ota.Subscribe_Firmware_Update(ota_update_callback);
    if (thingsBoardState.isOTAUpdateRequestSent) {
      LogSuccess("OTA update request", "sent successfully");
    } else {
      LogError("OTA update request", "can not sent");
    }
  }
}
      } else {
        if (!thingsBoardState.isAttempting) {
          Serial.print("[UPDATE] ThingsBoard: Connecting ...");
          thingsboard.disconnect();
          thingsboard.connect(ThingsBoardConfig::server, ThingsBoardConfig::token, ThingsBoardConfig::port);
          thingsBoardState.isAttempting = true;
          thingsBoardState.connectionAttempts = 0;
        } else {
          thingsBoardState.connectionAttempts++;
          if (thingsBoardState.connectionAttempts >= ThingsBoardConfig::maxConnectionAttempt) {
            Serial.println();
            LogError("ThingsBoard", "Failed to connect");
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