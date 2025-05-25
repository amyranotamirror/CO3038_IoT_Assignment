#include "task_light.h"

void InitLight(){
    pinMode(ActuatorConfig::lightPin, OUTPUT);
    digitalWrite(ActuatorConfig::lightPin, LOW);
    
}

RPC_Response RPCLightActuatorControl(const RPC_Data &data){
    lightActuatorState.status = data;
    digitalWrite(ActuatorConfig::lightPin, lightActuatorState.status);
    return RPC_Response("controlLight", lightActuatorState.status);
}

bool GetLightActuatorStatus(){
    return lightActuatorState.status;
}