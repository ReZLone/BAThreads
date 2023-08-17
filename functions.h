#ifndef FUNCTIONS
#define FUNCTIONS

#include <stddef.h>
#include <stdbool.h>


void GetVariable(const char* variableName, char* resultBuffer, size_t bufferSize);
void PrintVariableSet(const char* filePath);
void BroadcastVariable(const char* variableName, const char* variableValue, const char* dbName, bool force);
void UpdateThread();
void StopThread(const char* threadName);

#endif