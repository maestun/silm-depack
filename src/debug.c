//
//  debug.c
//  silmarils-unpacker
//

#include "debug.h"

void debug(EDebugLevel level, char * format, ...) {
    if(level <= DEBUG_LEVEL) {
        va_list arg;
        va_start(arg, format);
        vfprintf(stdout, format, arg);
        fflush(stdout);
        va_end(arg);
    }
}
