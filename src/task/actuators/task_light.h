#ifndef LIGHT_H
#define LIGHT_H

#include "./core/config.h"
#include "./core/state.h"
#include "./core/utils.h"

// Initialize light pin
void InitLight();

// Shared attributes for toggling light
void SetLightActuatorStatus(JsonPairConst json);
void SetLightActuatorWhiteStatus(JsonPairConst json);
void SetLightActuatorWarmStatus(JsonPairConst json);

#endif