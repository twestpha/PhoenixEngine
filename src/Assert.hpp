#include <windows.h>
#include <stdio.h>

#pragma once

extern bool winapi;

inline void _Assert(bool condition, const char* message...){
    if(!condition){
        if(winapi){
            MessageBox(NULL, message, "Assert Error", MB_ICONEXCLAMATION | MB_OK);
        } else {
            printf("Assert Error: %s\n", message);
        }
    }
}
