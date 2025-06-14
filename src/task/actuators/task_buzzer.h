#ifndef TASK_BUZZER_H
#define TASK_BUZZER_H

#include <Buzzer.h>

#include "./core/config.h"
#include "./core/state.h"
#include "./core/utils.h"

void InitBuzzer();
void TaskBuzzer(void *pvParameters);

void BuzzerCo2DetectedControl(const JsonVariantConst& variant);

extern Buzzer::Melody_t melody;
extern Buzzer buzzer;
#endif