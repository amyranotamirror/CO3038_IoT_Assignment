#include "task_rpc.h"

const std::array<RPC_Request_Callback, 1U> rpc_request_callbacks = {};

const std::array<RPC_Callback, 1U> rpc_callbacks = {
    RPC_Callback{"processRPC", processRPC}
};

void processRPC(const JsonVariantConst& variant, JsonDocument& document) {
  const size_t jsonSize = Helper::Measure_Json(variant);
  char buffer[jsonSize];
  serializeJson(variant, buffer, jsonSize);
  LogInfo("RPC received", buffer);
  if (variant.containsKey("CO2Detected")) {
    BuzzerCO2DetectedControl(variant);
    AlertCO2DetectedControl(variant);
  }
}