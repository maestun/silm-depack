//
//  config.h
//  silmarils-unpacker
//

#pragma once

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <libgen.h>
#include <ctype.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/termios.h>
#include <sys/mman.h>


#define kProgName           "silmarils-unpacker"
#define kProgVersion        "0.9.0"
#define kPathMaxLen         (256)
#define kNameMaxLen         (16)
#define kDescMaxLen         (1024)
#define kMainScriptName     "MAIN"
#define kMainScriptID       (0)


#ifdef _WIN32
#  define kPathSeparator    "\\"
#else
#  define kPathSeparator    "/"
#endif

typedef unsigned char       u8;
typedef uint16_t            u16;
typedef uint32_t            u32;
typedef int8_t              s8;
typedef int16_t             s16;
typedef int32_t             s32;

#define BIT_CLR(v, b)       (v &= ~(1UL << b))
#define BIT_SET(v, b)       (v |= (1UL << b))
#define BIT_CHG(v, b)       (v ^= (1UL << b))
#define BIT_CHK(v, b)       ((v >> b) & 1U)

typedef enum {
    EDebugFatal = 0,
    EDebugError,
    EDebugWarning,
    EDebugInfo,
    EDebugVerbose,
} EDebugLevel;

#define DEBUG_LEVEL EDebugVerbose
