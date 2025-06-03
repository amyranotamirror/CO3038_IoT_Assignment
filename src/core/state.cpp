#include "state.h"

volatile WifiState wifiState = {false, false, 0};
volatile ThingsBoardState thingsBoardState = {false, false, 0, false, false, false, false, false, false};

volatile AirQualitySensorState airQualitySensorState = {false, nullptr, 0, NAN};
volatile LightSensorState lightSensorState = {false, nullptr, 0, NAN};
volatile PresenceSensorState presenceSensorState = {false, nullptr, 0, false, 0};
volatile TempHumidSensorState tempHumidSensorState = {false, nullptr, 0, NAN, NAN};

volatile LightActuatorState lightActuatorState = {0};
volatile CurtainActuatorState curtainActuatorState = {0};

volatile BuzzerState buzzerState = {OFF};
volatile AlertState alertState = {OFF};

bool isSystemReady() {
    return wifiState.isConnected && thingsBoardState.isConnected && thingsBoardState.isServerRPC && thingsBoardState.isSharedAttributesUpdated && thingsBoardState.isSharedAttributesRequested && thingsBoardState.isSharedAttributesRequestProcessed && thingsBoardState.isOTACurrentFirmwareSent && thingsBoardState.isOTAUpdateRequestSent;
}