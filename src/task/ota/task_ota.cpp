#include "task_ota.h"

Espressif_Updater<> updater;
const OTA_Update_Callback ota_update_callback(OTAConfig::title, OTAConfig::version, &updater, &FinishedCallback, &ProgressCallback, &UpdateStartingCallback, OTAConfig::maxFailureAttempt, OTAConfig::firmwarePacketSize);

void TaskOTAUpdate(void *pvParameters) {
    while (1) {
        if (thingsBoardState.isSharedAttributesRequestProcessed) {
            // Send current FW
            if(!otaUpdateState.currentFWSent){
                otaUpdateState.currentFWSent = ota.Firmware_Send_Info(
                    OTAConfig::title, OTAConfig::version);
            }
            // Send update request
            if(!otaUpdateState.updateRequestSent) {
                Serial.print(OTAConfig::title);
                Serial.print(" ");
                Serial.println(OTAConfig::version);
                LogUpdate("OTA update", "Firmware update...", "");
                // Start updating
                otaUpdateState.updateRequestSent =
                    ota.Start_Firmware_Update(ota_update_callback);
                if (otaUpdateState.updateRequestSent) {
                    delay(500);
                    LogUpdate("OTA update", "Firmware update subscription...", "");
                    otaUpdateState.updateRequestSent =
                        ota.Subscribe_Firmware_Update(ota_update_callback);
                }
            }
        }
        vTaskDelay(pdMS_TO_TICKS(OTAConfig::otaUpdateInterval));
    }
}
void UpdateStartingCallback() {}
void FinishedCallback(const bool &success) {
    if (success) {
        LogSuccess("OTA update", "Done, reboot now");
        esp_restart();
    } else {
        LogError("OTA update", "Downloading firmware failed");
    }
}
void ProgressCallback(const size_t &current, const size_t &total) {
    Serial.printf("Progress %.2f%%\n",
                  static_cast<float>(current * 100U) / total);
}