#include "task_ota.h"

Espressif_Updater<> updater;
const OTA_Update_Callback ota_update_callback(OTAConfig::title, OTAConfig::version, &updater, &FinishedCallback, &ProgressCallback, &UpdateStartingCallback, OTAConfig::maxFailureAttempt, OTAConfig::firmwarePacketSize);

void UpdateStartingCallback() {
    LogInfo("OTA update", "start now");
}
void FinishedCallback(const bool &success) {
    if (success) {
        LogSuccess("OTA update", "done, reboot now");
        esp_restart();
    } else {
        LogError("OTA update", "downloading firmware failed");
    }
}
void ProgressCallback(const size_t &current, const size_t &total) {
    LogUpdate("OTA update", "progress", String(static_cast<double>(current * 100U) / total, 4).c_str(), "%");
}