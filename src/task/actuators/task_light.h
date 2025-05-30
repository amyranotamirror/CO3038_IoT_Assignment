#ifndef LIGHT_H
#define LIGHT_H

#include <HardwareSerial.h>
#include <ThingsBoard.h>
#include <Arduino.h>
#include <Arduino_MQTT_Client.h>

#include "./core/config.h"
#include "./core/state.h"
#include "./core/utils.h"

// Initialize light pin
void InitLight();

// Shared attributes for toggling light
void SetLightActuatorStatus(JsonPairConst json);

// RPC handler for toggling light
void RPCLightActuatorControl(const JsonVariantConst& variant, JsonDocument& document);

#endif