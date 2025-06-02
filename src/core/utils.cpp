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
    char buffer[128 + strlen(tag) + strlen(message)];
    snprintf(buffer, sizeof(buffer), "[ERROR] %s: %s\n", tag, message);
    Serial.print(buffer);
}

void LogWarn(const char* tag, const char* message) {
    char buffer[128 + strlen(tag) + strlen(message)];
    snprintf(buffer, sizeof(buffer), "[WARN] %s: %s\n", tag, message);
    Serial.print(buffer);
}

void LogInfo(const char* tag, const char* message) {
    char buffer[128 + strlen(tag) + strlen(message)];
    snprintf(buffer, sizeof(buffer), "[INFO] %s: %s\n", tag, message);
    Serial.print(buffer);
}

void LogSuccess(const char* tag, const char* message) {
    char buffer[128 + strlen(tag) + strlen(message)];
    snprintf(buffer, sizeof(buffer), "[SUCCESS] %s: %s\n", tag, message);
    Serial.print(buffer);
}

void LogUpdate(const char* tag, const char* message, const char* value, const char* unit) {
    char buffer[128 + strlen(tag) + strlen(message) + strlen(value) + strlen(unit)];
    if (unit == "") {
        snprintf(buffer, sizeof(buffer), "[UPDATE] %s: %s %s\n", tag, message, value);
    } else {
        snprintf(buffer, sizeof(buffer), "[UPDATE] %s: %s %s %s\n", tag, message, value, unit);
    }
    Serial.print(buffer);
}

void LogRead(const char* key, const char* value, const char* unit) {
    char buffer[128 + strlen(key) + strlen(value) + strlen(unit)];
    snprintf(buffer, sizeof(buffer), "[READ] %s = %s %s\n", key, value, unit);
    Serial.print(buffer);
}

void LogSend(const char* key, const char* value) {
    char buffer[128 + strlen(key) + strlen(value)];
    snprintf(buffer, sizeof(buffer), "[SEND] %s = %s\n", key, value);
    Serial.print(buffer);
}