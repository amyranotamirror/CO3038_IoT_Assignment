#ifndef TASK_SHARED_ATTR_H
#define TASK_SHARED_ATTR_H

#include <Attribute_Request.h>
#include <Attribute_Request_Callback.h>
#include <HardwareSerial.h>
#include <Shared_Attribute_Callback.h>

#include "../actuators/task_light.h"
#include "../network/task_thingsboard.h"

constexpr std::array<const char *, 1U> SHARED_ATTRIBUTES_LIST = {"lightActuatorStateStatus"};
extern const Shared_Attribute_Callback<ThingsBoardConfig::maxAttribute> shared_attribute_callback;
extern const Attribute_Request_Callback<ThingsBoardConfig::maxAttribute> attribute_request_callback;

void processSharedAttributeUpdate(const JsonObjectConst &data);
void processSharedAttributeRequest(const JsonObjectConst &data);

#endif