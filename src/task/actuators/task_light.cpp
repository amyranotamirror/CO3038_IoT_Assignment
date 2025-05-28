#include "task_light.h"

void InitLight(){
    lightSensor.begin();
    pinMode(ActuatorConfig::lightPin, OUTPUT);
    digitalWrite(ActuatorConfig::lightPin, true);
}

// RPC_Response RPCLightActuatorControl(const RPC_Data &data){
//     Serial.println("I don't want to stop being the person I am with her...");
//     // lightActuatorState.status = data;
//     // digitalWrite(ActuatorConfig::lightPin, lightActuatorState.status);
//     // return RPC_Response("controlLight", lightActuatorState.status);
//     bool status = data;
//     digitalWrite(ActuatorConfig::lightPin, status);
//     return RPC_Response("controlLight", status);
// }

bool GetLightActuatorStatus(){
    return lightActuatorState.status;
}