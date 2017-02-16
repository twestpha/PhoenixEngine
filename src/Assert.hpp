#include <windows.h>
#include <stdio.h>

#pragma once

// Linux Color Codes
// http://stackoverflow.com/a/3219471
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// Windows Color Codes
// no source because windows is fucking stupid
#define WINDOWS_COLOR_RED    12
#define WINDOWS_COLOR_YELLOW 14
#define WINDOWS_COLOR_RESET  7

#define BUFFER_SIZE 256

extern bool winapi;

inline void Assert_(bool condition, const char* message, const char* data = NULL ...){
    if(!condition){
		char buffer[BUFFER_SIZE];
		sprintf(buffer, message, data);

        if(winapi){
        	HANDLE  hConsole;
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    		SetConsoleTextAttribute(hConsole, WINDOWS_COLOR_RED);
    		printf("[ASSERT ERROR]: %s\n", buffer);
    		SetConsoleTextAttribute(hConsole, WINDOWS_COLOR_RESET);
            MessageBox(NULL, buffer, "Assertion Failed", MB_ICONEXCLAMATION | MB_OK);
        } else {
        	printf("%s[ASSERT ERROR]: %s%s\n", ANSI_COLOR_RED, buffer, ANSI_COLOR_RESET);
        }
    }
}

inline void WriteWarning_(const char* message, const char* data = NULL ...){
    char buffer[BUFFER_SIZE];
    sprintf(buffer, message, data);

    if(winapi){
        HANDLE  hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        SetConsoleTextAttribute(hConsole, WINDOWS_COLOR_YELLOW);
        printf("[WARNING]: %s\n", buffer);
        SetConsoleTextAttribute(hConsole, WINDOWS_COLOR_RESET);
    } else {
        printf("%s[WARNING]: %s%s\n", ANSI_COLOR_YELLOW, buffer, ANSI_COLOR_RESET);
    }
}
