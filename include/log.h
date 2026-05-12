#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define MAXARGS     31
#define COLOR_DEFAULT 	"\x1B[0m"
#define COLOR_INFO 	"\x1B[1;34m"
#define COLOR_WARNING 	"\x1B[1;33m"
#define COLOR_ERROR 	"\x1B[31m"

typedef enum {
    INFO = 0,
    WARNING,
    ERROR
} LOG_TYPE;

#ifdef STUFF_IMPLEMENTED


// NOTE(Giovanni): WARNING: UGLY CODE, WRITTEN THIS IN A RUSH
static inline void log(LOG_TYPE log_type, char* message, ...){
    switch(log_type){
        case INFO:{
            va_list args;
            va_start(args, message);
            printf("%sINFO: ", COLOR_INFO);
            vfprintf(stderr, message, args);
            printf("%s\n", COLOR_DEFAULT);
            va_end(args);
        }
        break;
        case WARNING:{
            va_list args;
            va_start(args, message);
            printf("%sWARNING: ", COLOR_WARNING);
            vfprintf(stderr, message, args);
            printf("%s\n", COLOR_DEFAULT);
            va_end(args);
        }
        break;
        case ERROR:{
            va_list args;
            va_start(args, message);
            printf("%sERROR: ", COLOR_ERROR);
            vfprintf(stderr, message, args);
            printf("%s\n", COLOR_DEFAULT);
            va_end(args);
        }
        break;
    }


}

#endif //STUFF_IMPLEMENTED
#endif //LOG_H
