#include <windows.h>
#include <stdio.h>

extern bool winapi;

void _Assert(bool condition, const char* message){
    if(!condition){
        if(winapi){
            MessageBox(NULL, message, "Error!", MB_ICONEXCLAMATION | MB_OK);
        } else {
            printf("Error: %s\n", message);
        }
    }
}
