#include "functions.h"
#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void GetVariable(const char* variableName, char* resultBuffer, size_t bufferSize) {
    GetEnvironmentVariable(variableName, resultBuffer, (DWORD)bufferSize);
}

void PrintVariableSet(const char* filePath) {
    FILE* file = fopen(filePath, "r"); // Open the file for reading
    if (file) {
        char buffer[256]; // Buffer to store each line
        while (fgets(buffer, sizeof(buffer), file)) {
            printf("%s", buffer); // Print each line
        }
        fclose(file); // Close the file
    } else {
        printf("Failed to open file for reading.\n");
    }
}

void BroadcastVariable(const char* variableName, const char* variableValue, const char* dbName, bool force) {
    // Get the executable path
    char exePath[MAX_PATH];
    GetModuleFileName(NULL, exePath, sizeof(exePath));
    
    // Extract the directory path
    char* lastBackslash = strrchr(exePath, '\\');
    if (lastBackslash) {
        *lastBackslash = '\0';
    }
    
    // Create the folder
    char folderPath[MAX_PATH];
    snprintf(folderPath, sizeof(folderPath), "%s\\.threads", exePath);
    if (CreateDirectory(folderPath, NULL) || GetLastError() == ERROR_ALREADY_EXISTS) {
        // Folder created or already exists
        
        // Create data structure files (e.g., .db files)
        char dbPath[MAX_PATH];
        snprintf(dbPath, sizeof(dbPath), "%s\\%s.db", folderPath, dbName);
        FILE* db = fopen(dbPath, "a+");
        if (db) {
            // Check if the lines are already present
            bool containsNotDefinedLine = false;
            bool containsSetLine = false;
            char line[512];
            char notDefinedLine[512];
            char setLine[512];
            snprintf(notDefinedLine, sizeof(notDefinedLine), "if not defined %s set %s=%s\n", variableName, variableName, variableValue);
            snprintf(setLine, sizeof(setLine), "set %s=%s\n", variableName, variableValue);
            
            while (fgets(line, sizeof(line), db)) {
                if (!containsNotDefinedLine && strstr(line, notDefinedLine) != NULL) {
                    containsNotDefinedLine = true;
                }
                if (!containsSetLine && strstr(line, setLine) != NULL) {
                    containsSetLine = true;
                }
            }
            
            // Write data structure contents to the file
            if (!containsNotDefinedLine && !containsSetLine) {
                if (force) {
                    fprintf(db, "set %s=%s\n", variableName, variableValue);
                } else {
                    fprintf(db, "if not defined %s set %s=%s\n", variableName, variableName, variableValue);
                }
            }
            
            fclose(db);
        }
    } else {
        // Folder creation failed
        printf("Failed to create data folder.\n");
    }
}

void UpdateThread() {
	// Get the executable path
    char exePath[MAX_PATH];
    GetModuleFileName(NULL, exePath, sizeof(exePath));
    
    // Extract the directory path
    char* lastBackslash = strrchr(exePath, '\\');
    if (lastBackslash) {
        *lastBackslash = '\0';
    }
    
    // Create the folder
    char folderPath[MAX_PATH];
    snprintf(folderPath, sizeof(folderPath), "%s\\.threads", exePath);
    
    // Create data structure files (e.g., .db files)
    char globalPath[MAX_PATH];
    snprintf(globalPath, sizeof(globalPath), "%s\\global.db", folderPath);
    
    PrintVariableSet(globalPath);
}


void StopThread(const char* threadName) {
    // Implementation to stop a thread based on its custom name
    // You might need a thread management mechanism like an array
    // of handles and mapping custom thread names to those handles.
}
