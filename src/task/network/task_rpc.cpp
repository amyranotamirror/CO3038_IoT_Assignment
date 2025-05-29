#include "task_rpc.h"

const std::array<RPC_Callback, 1U> callbacks = {
    RPC_Callback{"RPCLightActuatorControl", RPCLightActuatorControl}
};