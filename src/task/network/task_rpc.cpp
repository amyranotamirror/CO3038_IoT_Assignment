#include "task_rpc.h"

const std::array<RPC_Request_Callback, 1U> rpc_request_callbacks = {};

const std::array<RPC_Callback, 1U> rpc_callbacks = {
    RPC_Callback{"RPCBuzzerControl", RPCBuzzerControl}
};