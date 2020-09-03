//
//  platform.h
//  silm-depack
//

#ifndef platform_h
#define platform_h

#include "config.h"
#include "utils.h"


typedef enum {
    EPlatformAtari = 0,
    EPlatformFalcon,
    EPlatformAmiga,
    EPlatformAmigaAGA,
    EPlatformMac,
    EPlatformPC,
    EPlatformUnknown
} EPlatform;


typedef struct {
    EPlatform   kind;       
    char        desc[32];   // platform description
    char        ext[8];     // script file extension
    u16         width;      // screen info
    u16         height;
    u8          bpp;
} sPlatform;


sPlatform   guess_platform(char * folder_path);
int         is_supported(sPlatform platform);

#endif /* platform_h */
