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
        Serial.print("[WARN] Tried to give null mutex for "); Serial.println(tag);
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

void LogUpdate(const char* tag, const char* message, const char* value) {
    Serial.print("[UPDATE] "); Serial.print(tag); Serial.print(": "); Serial.print(message); Serial.println(value);
}

void LogRead(const char* key, const char* value, const char* unit) {
    Serial.print("[INFO] Read "); Serial.print(key); Serial.print(" = "); Serial.print(value); Serial.print(" "); Serial.println(unit);
}

void LogSend(const char* key, const char* value) {
    Serial.print("[INFO] Send "); Serial.print(key); Serial.print(" = "); Serial.println(value);
}