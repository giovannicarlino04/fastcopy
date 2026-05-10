#ifndef LOG_H
#define LOG_H

#include <stdio.h>

typedef enum {
    INFO = 0,
    WARNING,
    ERROR
} LOG_TYPE;

#ifdef STUFF_IMPLEMENTED

// TODO(Giovanni): Allow formatting in the future!!!
static inline void log(const char* message, LOG_TYPE log_type){
    
    switch(log_type){
        case INFO:{
            printf("INFO: %s\n", message);
        }
        break;
        case WARNING:{
            printf("WARNING: %s\n", message);
        }
        break;
        case ERROR:{
            printf("ERROR: %s\n", message);
        }
        break;
    }
}

#endif //STUFF_IMPLEMENTED
#endif //LOG_H
