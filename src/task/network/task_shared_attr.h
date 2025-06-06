#ifndef TASK_SHARED_ATTR_H
#define TASK_SHARED_ATTR_H

#include <Attribute_Request_Callback.h>
#include <Shared_Attribute_Callback.h>

#include "./core/state.h"
#include "./core/utils.h"
#include "../actuators/task_curtain.h"
#include "../actuators/task_light.h"

constexpr std::array<const char *, 3U> shared_attribute_list = {"curtainActuatorMode", "lightActuatorWhite", "lightActuatorWarm"};
// constexpr std::array<const char *, 2U> shared_attribute_list = {"curtainActuatorMode", "lightActuatorMode"};
extern const Shared_Attribute_Callback<RPCAttributeConfig::maxAttribute> shared_attribute_callback;
extern const Attribute_Request_Callback<RPCAttributeConfig::maxAttribute> attribute_request_callback;

void RequestTimedOut();
void processSharedAttributes(const JsonObjectConst &data);
void processSharedAttributeUpdate(const JsonObjectConst &data);
void processSharedAttributeRequest(const JsonObjectConst &data);

#endif