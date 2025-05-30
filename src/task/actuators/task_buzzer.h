#ifndef TASK_BUZZER_H
#define TASK_BUZZER_H

#include <Arduino.h>
#include "Buzzer.h"
#include "./core/config.h"
#include "./core/state.h"
#include "./core/utils.h"

void InitBuzzer();
bool GetBuzzerStatus();
void SetBuzzerStatus(bool status);
void TaskBuzzer(void *pvParameters);

void RPCBuzzerControl(const JsonVariantConst& variant, JsonDocument& document);

extern Buzzer::Melody_t melody;
extern Buzzer buzzer;
#endif