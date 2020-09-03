//
//  depack.h
//  silm-depack
//

#ifndef depak_h
#define depak_h

#include "config.h"
#include "utils.h"
#include "platform.h"
#include "asm.h"

void        depack(char * path);
void        depack_file(char * pak_name, char * depak_name, sPlatform platform);
uint8_t *   depack_buffer(uint8_t * pak_buffer);
int         depack_is_packed(uint8_t * pak_buffer);
uint32_t    depack_get_size(uint8_t * pak_buffer);

#endif /* depak_h */
