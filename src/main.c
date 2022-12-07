//
//  main.c
//  silmarils-unpacker
//

#include "debug.h"
#include "platform.h"
#include "unpack.h"

void usage(void) {
    printf("%s v%s\nUsage:\n\t%s <data_path>\n\t%s <script_path>\n",
           kProgName, kProgVersion, kProgName, kProgName);
}

void unpack(const char * packed_path) {

    DIR * dir = NULL;
    struct dirent *ent;

    const char* kDepackExtension = "alis";
    const int kPathLen = 256;

    if((dir = opendir(packed_path)) != NULL) {
        // path is a folder
        char unpacked_path[kPathLen] = {0};
        sprintf(unpacked_path, "%s%s", packed_path, "unpacked/");
        sPlatform* platform = pl_guess(packed_path);
        if(pl_supported(platform)) {
            // platform is supported
            while ((ent = readdir(dir)) != NULL) {
                if(ent->d_type == DT_REG) {
                    // it's a file
                    char packed_file[kPathLen] = {0};
                    sprintf(packed_file, "%s%s", packed_path, ent->d_name);
                    size_t size = 0;

                    u8* data = NULL;
                    size = unpack_script(packed_file, platform->is_little_endian, &data);
                    if(size >= 0) {
                        char unpacked_file[kPathLen] = {0};
                        sprintf(unpacked_file, "%s%s", unpacked_path, ent->d_name);
                        *(strrchr(unpacked_file, '.') + 1) = 0;
                        strcat(unpacked_file, kDepackExtension);
                        FILE * unpak_fp = fopen(unpacked_file, "w");
                        if(unpak_fp) {
                            fwrite(data, sizeof(u8), size, unpak_fp);
                            fclose(unpak_fp);
                            debug(EDebugVerbose, "Wrote unpacked file: %s\n", unpacked_file);
                        }
                        free(data);
                    }
                    else {
                        debug(EDebugError, "ERROR: unsupported file, check input folder.\n");
                    }
                }
            }
        }
        else {
            debug(EDebugWarning, "WARNING: unsupported platform, check input folder.\n");
        }
        closedir(dir);
    }
    else {
        // might be a script file
        sPlatform* platform = pl_guess(packed_path);
        if(pl_supported(platform)) {
            // platform is supported
            u8* data = NULL;
            size_t size = unpack_script(packed_path, platform->is_little_endian, &data);
            if(size >= 0) {
                char unpacked_file[kPathLen] = {0};
                sprintf(unpacked_file, "%s.%s", packed_path, kDepackExtension);
                FILE * unpak_fp = fopen(unpacked_file, "w");
                if(unpak_fp) {
                    fwrite(data, sizeof(u8), size, unpak_fp);
                    fclose(unpak_fp);
                    debug(EDebugVerbose, "Wrote unpacked file: %s\n", unpacked_file);
                }
                free(data);
            }
            else {
                debug(EDebugError, "ERROR: unsupported file, check input folder.\n");
            }
        }
    }
}


int main(int argc, const char* argv[]) {
    if (argc != 2) {
        usage();
    }
    else {
        unpack(argv[1]);
    }
    return 0;
}
