#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

bool TakeMutex(SemaphoreHandle_t mutex, TickType_t waitTicks, const char* tag);
void GiveMutex(SemaphoreHandle_t mutex, const char* tag);

void LogError(const char* tag, const char* message);
void LogWarn(const char* tag, const char* message);
void LogInfo(const char* tag, const char* message);
void LogSuccess(const char* tag, const char* message);

void LogUpdate(const char* tag, const char* message, const char* value, const char* unit);

void LogRead(const char* key, const char* value, const char* unit);
void LogSend(const char* key, const char* value);

#endif