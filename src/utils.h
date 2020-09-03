//
//  utils.h
//  silm-depack
//

#ifndef utils_h
#define utils_h

#include "config.h"

long        get_file_size(char * file_name);
char *      strlower(char * str);
char *      strupper(char * str);
uint32_t    reverse_bytes_32(uint32_t value);

#endif /* utils_h */
