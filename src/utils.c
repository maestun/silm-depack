//
//  utils.c
//  silm-depack
//

#include "utils.h"

uint32_t reverse_bytes_32(uint32_t value) {
    return (value & 0x000000FFU) << 24 | (value & 0x0000FF00U) << 8 | (value & 0x00FF0000U) >> 8 | (value & 0xFF000000U) >> 24;
}

long get_file_size(char * file_name) {
    long sz = -1;
    FILE * fp = fopen(file_name, "r");
    if(fp) {
        fseek(fp, 0L, SEEK_END);
        sz = ftell(fp);
        fclose(fp);
    }
    return sz;
}


char * strlower(char * str) {
    char * ptr = str;
    if(ptr) {
        for ( ; *ptr; ++ptr)
            *ptr = tolower(*ptr);
    }
    return str;
}


char * strupper(char * str) {
    char * ptr = str;
    if(ptr) {
        for ( ; *ptr; ++ptr)
            *ptr = toupper(*ptr);
    }
    return str;
}
