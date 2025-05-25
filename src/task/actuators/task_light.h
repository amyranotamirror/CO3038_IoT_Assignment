#ifndef LIGHT_H
#define LIGHT_H

#include <ThingsBoard.h>
#include <Arduino.h>
#include <Arduino_MQTT_Client.h>
#include "./core/config.h"
#include "./core/state.h"
// Initialize light pin
void InitLight();

// RPC handler for toggling light
RPC_Response handleLightToggle(const RPC_Data &data);

#endif