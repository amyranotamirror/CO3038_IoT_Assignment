#ifndef RPC_HANDLER_H
#define RPC_HANDLER_H

#include <RPC_Callback.h>
#include <RPC_Request_Callback.h>

#include "../actuators/task_alert.h"
#include "../actuators/task_buzzer.h"

// Define your ThingsBoard RPC callback type
extern const std::array<RPC_Request_Callback, 1U> rpc_request_callbacks;
extern const std::array<RPC_Callback, 1U> rpc_callbacks;

void processRPC(const JsonVariantConst& variant, JsonDocument& document);

#endif