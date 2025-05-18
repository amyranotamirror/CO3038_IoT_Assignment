#ifndef OTA_UPDATE_H
#define OTA_UPDATE_H

#include <ThingsBoard.h>
#include <ArduinoOTA.h>
#include <Espressif_Updater.h>
#include <OTA_Firmware_Update.h>
#include "./core/config.h"
#include "./core/state.h"
#include "./task/network/task_thingsboard.h"

extern const std::array<IAPI_Implementation *, 3U> apis;

void TaskOTAUpdate(void *pvParameters); 
void RequestTimedOut();
void UpdateStartingCallback();
void FinishedCallback(const bool &success);
void ProgressCallback(const size_t &current, const size_t &total);
void ProcessSharedAttributeUpdate(const JsonObjectConst &data);
void ProcessSharedAttributeRequest(const JsonObjectConst &data);
#endif