#ifndef RPC_HANDLER_H
#define RPC_HANDLER_H

#include <HardwareSerial.h>
#include <RPC_Callback.h>
#include <RPC_Request_Callback.h>
#include <ThingsBoard.h>

// #include "../actuators/task_air_cond.h"
// #include "../actuators/task_buzzer.h"
// #include "../actuators/task_curtain.h"
#include "../actuators/task_light.h"
// #include "../actuators/task_relay.h"
#include "../network/task_thingsboard.h"

// Define your ThingsBoard RPC callback type
extern const std::array<RPC_Request_Callback, 1U> request_callbacks;
extern const std::array<RPC_Callback, 1U> callbacks;

#endif