#include "task_ota.h"

Espressif_Updater<> updater;

void TaskOTAUpdate(void *pvParameters) {
    while (1) {
        if (thingsboard.connected() && WiFi.status() == WL_CONNECTED) {
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
                Serial.println("[UPDATE] OTA Update: Firmware Update ...");
                // Start updating
                const OTA_Update_Callback callback(
                    OTAConfig::title, OTAConfig::version, &updater,
                    &FinishedCallback, &ProgressCallback,
                    &UpdateStartingCallback, OTAConfig::maxFailureAttempt,
                    OTAConfig::firmwarePacketSize);
                otaUpdateState.updateRequestSent =
                    ota.Start_Firmware_Update(callback);
                if (otaUpdateState.updateRequestSent) {
                    delay(500);
                    Serial.println(
                        "[UPDATE] OTA Update: Firmware Update "
                        "Subscription...");
                    otaUpdateState.updateRequestSent =
                        ota.Subscribe_Firmware_Update(callback);
                }
            }
        }
        vTaskDelay(pdMS_TO_TICKS(OTAConfig::otaUpdateInterval));
    }
}
void RequestTimedOut() {
    Serial.printf(
        "Attribute request timed out did not receive a response in (%llu) "
        "microseconds. Ensure client is connected to the MQTT broker and that "
        "the keys actually exist on the target device\n",
        OTAConfig::requestTimeoutMicroseconds);
}
void UpdateStartingCallback() {}
void FinishedCallback(const bool &success) {
    if (success) {
        Serial.println("Done, Reboot now");
        esp_restart();
        return;
    }
    Serial.println("Downloading firmware failed");
}
void ProgressCallback(const size_t &current, const size_t &total) {
    Serial.printf("Progress %.2f%%\n",
                  static_cast<float>(current * 100U) / total);
}