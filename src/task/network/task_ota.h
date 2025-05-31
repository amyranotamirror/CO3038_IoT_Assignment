#ifndef OTA_UPDATE_H
#define OTA_UPDATE_H

#include <ArduinoOTA.h>
#include <Espressif_Updater.h>
#include "task_thingsboard.h"
#include "./core/config.h"
#include "./core/state.h"
#include "./core/utils.h"

extern const OTA_Update_Callback ota_update_callback;

void UpdateStartingCallback();
void FinishedCallback(const bool &success);
void ProgressCallback(const size_t &current, const size_t &total);
#endif