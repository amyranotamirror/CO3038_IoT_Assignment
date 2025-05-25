#include "task_rpc.h"

std::vector<RPC_Callback> rpc_callbacks = {
    // RPC_Callback{ "toggleLight", handleLightToggle },
    // RPC_Callback{ "controlAircon", handleAirconCommand }
};

void initRPC(ThingsBoard &tb) {
  tb.RPC_Subscribe(rpc_callbacks.begin(), rpc_callbacks.end());
}