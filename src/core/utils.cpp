#include "utils.h"

bool TakeMutex(SemaphoreHandle_t mutex, TickType_t waitTicks, const char* tag) {
    if (mutex == nullptr) {
        LogError(tag, "Mutex is not initialized");
        return false;
    }
    if (xSemaphoreTake(mutex, waitTicks) != pdTRUE) {
        LogError(tag, "Failed to take mutex");
        return false;
    }
    return true;
}

void GiveMutex(SemaphoreHandle_t mutex, const char* tag) {
    if (mutex != nullptr) {
        xSemaphoreGive(mutex);
    } else {
        LogWarn(tag, "Tried to give null mutex");
    }
}

void LogError(const char* tag, const char* message) {
    Serial.print("[ERROR] "); Serial.print(tag); Serial.print(": "); Serial.println(message);
}

void LogWarn(const char* tag, const char* message) {
    Serial.print("[WARN] "); Serial.print(tag); Serial.print(": "); Serial.println(message);
}

void LogInfo(const char* tag, const char* message) {
    Serial.print("[INFO] "); Serial.print(tag); Serial.print(": "); Serial.println(message);
}

void LogSuccess(const char* tag, const char* message) {
    Serial.print("[SUCCESS] "); Serial.print(tag); Serial.print(": "); Serial.println(message);
}