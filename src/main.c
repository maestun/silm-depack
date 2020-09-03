//
//  main.c
//  silm-depack
//

#include "depack.h"


static void usage() {
    printf("%s v%s\n",
           kProgName, kProgVersion);
    printf("An experimental Silmarils ALIS file depacker.\n");
    printf("This program will try to guess the platform by checking the file extensions.\n");
    printf("Usage:\n%s <input_file>\n%s <input_folder>\n",
           kProgName, kProgName);
}


int main(int argc, const char * argv[]) {
    if(argc > 1) {
        depack((char *)argv[1]);
    }
    else {
        usage();
    }
}
