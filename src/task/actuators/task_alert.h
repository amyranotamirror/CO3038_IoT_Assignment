#ifndef TASK_ALERT_H
#define TASK_ALERT_H

#include "./core/config.h"
#include "./core/state.h"
#include "./core/utils.h"

void InitAlert();
void TaskAlert(void *pvParameters);

void AlertCo2DetectedControl(const JsonVariantConst& variant);

#endif
