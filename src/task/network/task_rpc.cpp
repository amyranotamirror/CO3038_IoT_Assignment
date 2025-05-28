// #include "task_rpc.h"

// const std::array<RPC_Callback, 1U> callbacks = {
//     RPC_Callback{"RPCLightActuatorControl", RPCLightActuatorControl}
// };

// void InitRPC() {
//   if(!thingsboard.RPC_Subscribe(callbacks.cbegin(), callbacks.cend())) {
//     Serial.println("Failed to subscribe for RPC");
//   };
// }