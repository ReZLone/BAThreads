#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>
#include "functions.h"

int main(int argc, char* argv[]) {
    if (argc >= 2) {
        if (strcmp(argv[1], "global") == 0 && argc >= 3) {
            const char* variableName = argv[2];
            
            char variableValue[256];
            GetVariable(variableName, variableValue, sizeof(variableValue));
            
            bool force = false;

            if (argc >= 4 && strcmp(argv[3], "-f") == 0) {
                force = true;
            }

            BroadcastVariable(variableName, variableValue, "global",force);
        } else if (strcmp(argv[1], "update") == 0) {
            UpdateThread();
        } else if (strcmp(argv[1], "new") == 0 && argc >= 3) {
            return 0;
        } else if (strcmp(argv[1], "stop") == 0) {
            if (argc >= 3) {
                const char* threadName = argv[2];
                StopThread(threadName);
            } else if (argc >= 2 && strcmp(argv[2], "all") == 0) {
                return 0;
            }
        }
    }

    return 0;
}
