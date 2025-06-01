#ifndef CURTAIN_H
#define CURTAIN_H

#include "./core/config.h"
#include "./core/state.h"
#include "./core/utils.h"
#include <Servo.h>

extern Servo curtain;

// Initialize curtain pin and channel
void InitCurtain();

// Shared attributes for toggling light
void SetCurtainActuatorStatus(JsonPairConst json);

#endif