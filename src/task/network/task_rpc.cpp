#include "task_rpc.h"

const std::array<RPC_Callback, 1U> callbacks = {
    RPC_Callback{ "RPCLightActuatorControl", RPCLightActuatorControl }
    // RPC_Callback{ "controlAircon", handleAirconCommand }
};

void InitRPC() {
  thingsboard.RPC_Subscribe(callbacks.cbegin(), callbacks.cend());
}