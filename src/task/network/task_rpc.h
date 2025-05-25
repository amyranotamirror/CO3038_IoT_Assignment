#ifndef RPC_HANDLER_H
#define RPC_HANDLER_H

#include <ThingsBoard.h>
#include <vector>

#include "../actuators/task_air_cond.h"
#include "../actuators/task_buzzer.h"
#include "../actuators/task_curtain.h"
#include "../actuators/task_light.h"
#include "../actuators/task_relay.h"

// Define your ThingsBoard RPC callback type
extern std::vector<RPC_Callback> rpc_callbacks;

// Initializes and subscribes RPCs with ThingsBoard
void InitRPC(ThingsBoard &tb);

#endif