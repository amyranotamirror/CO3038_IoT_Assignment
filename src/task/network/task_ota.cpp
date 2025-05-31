#include "task_ota.h"

Espressif_Updater<> updater;
const OTA_Update_Callback ota_update_callback(OTAConfig::title, OTAConfig::version, &updater, &FinishedCallback, &ProgressCallback, &UpdateStartingCallback, OTAConfig::maxFailureAttempt, OTAConfig::firmwarePacketSize);

void UpdateStartingCallback() {
    LogInfo("OTA update", "Start now");
}
void FinishedCallback(const bool &success) {
    if (success) {
        LogSuccess("OTA update", "Done, reboot now");
        esp_restart();
    } else {
        LogError("OTA update", "Downloading firmware failed");
    }
}
void ProgressCallback(const size_t &current, const size_t &total) {
    LogUpdate("OTA update", "progress", String(static_cast<float>(current * 100U) / total, 4).c_str(), "%");
}