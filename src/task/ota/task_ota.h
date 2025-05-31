#ifndef OTA_UPDATE_H
#define OTA_UPDATE_H

#include <ThingsBoard.h>
#include <ArduinoOTA.h>
#include <Espressif_Updater.h>
#include "./core/config.h"
#include "./core/state.h"
#include "./core/utils.h"
#include "./task/network/task_thingsboard.h"

extern const OTA_Update_Callback ota_update_callback;

void TaskOTAUpdate(void *pvParameters);
void UpdateStartingCallback();
void FinishedCallback(const bool &success);
void ProgressCallback(const size_t &current, const size_t &total);
#endif