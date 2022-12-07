//
//  utils.c
//  silmarils-unpacker
//

#include "utils.h"

int is_host_le() {
    static unsigned int x = 1;
    char* c = (char*)&x;
    return (int)*c;
}

u32 swap32(u32 value, u8 is_le) {
    return is_le == is_host_le() ? value : ((value >> 24) & 0xff) |
                                           ((value <<  8) & 0xff0000) |
                                           ((value >>  8) & 0xff00) |
                                           ((value << 24) & 0xff000000);
}

u32 fread32(FILE* fp, u8 is_le) {
    u32 v = 0;
    fread(&v, sizeof(u32), 1, fp);
    return swap32(v, is_le);
}

u16 swap16(u16 value, u8 is_le) {
    return is_le == is_host_le() ? value : (value <<  8) |
                                           (value >>  8);
}

u16 fread16(FILE* fp, u8 is_le) {
    u16 v = 0;
    fread(&v, sizeof(u16), 1, fp);
    return swap16(v, is_le);
}