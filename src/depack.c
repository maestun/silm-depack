//
//  depak.c
//  silm-depack
//
//  Silmarils resource files depacker
//  Dumb-reversed from Atari ST version
//  No clue about what decompression algorithm this is :(
//
#include "depack.h"


void depak_2(void);
void depak_6(void);
void depak_11(void);
void get_moar_data(void) {}

uint8_t * p_depak = NULL;
uint8_t * p_depak_end = NULL;
uint8_t * p_pak = NULL;
uint8_t * p_pak_end = NULL;
uint8_t * p_dic;

uint32_t depak_counter = 0;
uint32_t pak_counter = 0;

void depak(uint8_t * aPakBuffer, // A0
           uint8_t * aDepakBuffer, // A1 -> pointe sur byte courant, A2 pointe sur dernier byte
           size_t aPakSize,
           size_t aDepakSize, // D1
           uint8_t * aDic) { // A5
    
    
    printf("DEPACK: unpacking...\n");
//    printf("PAK buffer start: 0x%08x\n", (uint32_t) aPakBuffer);
//    printf("PAK buffer size: %ld\n", aPakSize);
//    printf("PAK buffer end: 0x%08x\n", (uint32_t)(aPakBuffer + aPakSize));
//    printf("DEPAK buffer start: 0x%08x\n", (uint32_t)aDepakBuffer);
//    printf("DEPAK buffer size: %ld\n", aDepakSize);
//    printf("DEPAK buffer end: 0x%08x\n", (uint32_t)(aDepakBuffer + aDepakSize));
    
    int16_t offset = 0;
    uint8_t tmp_b = 0;
    
    p_depak = aDepakBuffer; // A1
    p_depak_end = aDepakBuffer + aDepakSize - 1; // A2
    p_pak = aPakBuffer; // A0
    p_pak_end = aPakBuffer + aPakSize; // A4
    p_dic = aDic;

    CLRREG_W(d7);
    
_depak_start:
//    printf("depak_start ($1632e)\n");
    if(p_depak > p_depak_end) {     // CMPA.L    A2,A1
        goto _depak_end;            // BGT       FN_DEPACK_END ; si a2 (adresse fin decrunch) > a1 (adresse debut decrunch) alors fin
    }
    MOVEQ(1, d0);                   // MOVEQ     #1,D0    
    depak_2();                      // BSR.S     _DEPACK_2
    if(BYTE(d5) == 0) {             // TST.B     D5
        goto _depak_3;              // BEQ.S     _DEPACK_3
    }
    MOVEQ(0, d2);                   // MOVEQ     #0,D2
    
_depak_4:
//    printf("depak_4 ($1633e)\n");
    MOVEQ(2, d0);                   // MOVEQ     #2,D0
    depak_2();                      // BSR.S     _DEPACK_2
    ADDREG_W(d5, d2);               // ADD.W     D5,D2
    if(WORD(d5) == 3) {             // CMP.W     #3,D5
        goto _depak_4;              // BEQ.S     _DEPACK_4
    }
    
_depak_5:
//    printf("depak_5 ($1634a)\n");
    MOVEQ(8, d0);                   // MOVEQ     #8,D0
    depak_2();                      // BSR.S     _DEPACK_2
    *p_depak = BYTE(d5);            // MOVE.B    D5,(A1)+      ; ecriture d'un octet depack :)
    
//    printf("depak5: wrote %uth byte (0x%02x) at address 0x%08x\n", depak_counter++, BYTE(d5), (uint32_t)p_depak);
    
    p_depak++;
    SUB_W(1, d2);
    if((int16_t)WORD(d2) >= 0) {             // DBF       D2,_DEPACK_5
        goto _depak_5;
    }
    
    if(p_depak > p_depak_end) {     // CMPA.L    A2,A1
        goto _depak_end;            // BGT       FN_DEPACK_END ; si a2 (adresse fin decrunch) > a1 (adresse debut decrunch) alors fin
    }
    
_depak_3:
//    printf("depak_3 ($1635a)\n");
    depak_6();                      // BSR.S     _DEPACK_6
    CLRREG_W(d0);                      // CLR.W     D0
    
//    printf("Dic: byte %d is 0x%02x\n", WORD(d5), p_dic[WORD(d5)]);
    MOVE_B(p_dic[WORD(d5)], d0);    // MOVE.B    0(A5,D5.W),D0

    ANDI_W(3, d5);                  // ANDI.W    #3,D5
    if(WORD(d5) == 0) {
        goto _depak_7;              // BEQ       _DEPACK_7
    }
//    MOVEREG_W(d5, d2);              // MOVE.W    D5,D2
    MOVE(W, 0, d5, d2);
    
    depak_2();                      // BSR.S     _DEPACK_2

_depak_8:
//    printf("depak_8 ($1636e)\n");
    NEG_W(d5);                      // NEG.W     D5
    
_depak_9:

    // MOVE.B    -1(A1,D5.W),(A1)+ ; ecriture d'un octet depack :)
    offset = WORD(d5) * -1;
    offset++;
    tmp_b = *(p_depak - offset);
    *p_depak = tmp_b;
//    printf("depak9: wrote %uth byte (0x%02x) at address 0x%08x\n", depak_counter++, tmp_b, (uint32_t)p_depak);
    p_depak++;

    
    SUB_W(1, d2);
    if((int16_t)WORD(d2) >= 0) {    // DBF       D2,_DEPACK_9
        goto _depak_9;
    }
    goto _depak_start;              // BRA       _DEPACK_START

_depak_7:
//    printf("depak_7\n");
    depak_2();                      // BSR       _DEPACK_2
    // MOVEREG_W(d5, d3);              // MOVE.W    D5,D3
    MOVE(W, 0, d5, d3);

    CLRREG_W(d2);                      // CLR.W     D2

_depak_10:
//    printf("depak_10\n");
    depak_6();                      // BSR.S     _DEPACK_6
    
    ADDREG_W(d5, d2);               // ADD.W     D5,D2
    if(WORD(d5) == 7) {             // CMP.W     #7,D5
        goto _depak_10;             // BEQ.S     _DEPACK_10
    }

//    MOVEREG_W(d3, d5);              // MOVE.W    D3,D5
    MOVE(W, 0, d3, d5);

    ADDQ_W(4, d2);                  // ADDQ.W    #4,D2
    
    goto _depak_8;                  // BRA.S     _DEPACK_8
    
_depak_end:
//    printf("depak_end\n");
    return;
}


void depak_6() {
//    printf("depak_6 ($1639c)\n");
    MOVEQ(3, d0);                   // MOVEQ     #3,D0
    depak_2();
}


void depak_2() {
//    printf("depak_2 ($1639e)\n");
    SUBREG_B(d0, d7);               // SUB.B     D0,D7
    if((int8_t)BYTE(d7) < 0) {      // BMI.S     _DEPACK_11
        depak_11();
    }
    else {
        CLRREG_W(d5);                      // CLR.W     D5
        ROLREG_L(d0, d5);               // ROL.L     D0,D5
    }
    return;                         // RTS
}


void depak_11() {
//    printf("depak_11 ($163a8)\n");
    ADDREG_B(d0, d7);               // ADD.B     D0,D7
    CLRREG_W(d5);                      // CLR.W     D5
    ROLREG_L(d7, d5);               // ROL.L     D7,D5
    SWAP(d5);                       // SWAP      D5
    if(p_pak > p_pak_end) {         // CMPA.L    A4,A0
        get_moar_data(); // BGE       _DEPACK_GET_MORE_DATA ; read 32k bytes
    }

// _DEPACK_12:
    uint16_t w = *p_pak;
    w <<= 8;
    w += *(p_pak + 1);
//    printf("depak11: read word 0x%x at address 0x%x\n", w, (uint32_t)p_pak);
    p_pak += 2;
    MOVE_W(w, d5);                  // MOVE.W    (A0)+,D5
//    MOVE(W, 0, p_pak++, d5)

    
    SWAP(d5);                       // SWAP      D5
    
    SUBREG_B(d7, d0);               // SUB.B     D7,D0
    MOVEQ(16, d7);                  // MOVEQ     #$10,D7
    ROLREG_L(d0, d5);               // ROL.L     D0,D5
    
    SUBREG_B(d0, d7);               // SUB.B     D0,D7
    return;                         // RTS ($163c2)
}

//#define HEADER_MAGIC_SZ     (sizeof(uint8_t))
#define HEADER_MAGICLEN_SZ  (sizeof(uint32_t))
#define HEADER_CHECK_SZ     (sizeof(uint16_t))
#define HEADER_DIC_SZ       (2 * sizeof(uint32_t))
#define HEADER_MAIN_SZ      (4 * sizeof(uint32_t))


size_t getDepackedSize(FILE * aPakFile, sPlatform aPlatform) {
    rewind(aPakFile);
    // skip magic word
    fgetc(aPakFile);
    size_t depak_sz = (fgetc(aPakFile) << 16) + (fgetc(aPakFile) << 8) + fgetc(aPakFile);
    return depak_sz - (HEADER_MAGICLEN_SZ + HEADER_CHECK_SZ);
}


uint16_t getMagic(FILE * aPakFile, sPlatform aPlatform) {
    uint8_t magic = 0;
    rewind(aPakFile);
    magic = fgetc(aPakFile);
    return magic;
}


uint16_t getCheck(FILE * aPakFile, sPlatform aPlatform) {
    
    uint16_t check = 0;
    rewind(aPakFile);
    fseek(aPakFile, HEADER_MAGICLEN_SZ, SEEK_SET);
    check = (fgetc(aPakFile) << 8) + fgetc(aPakFile);
    return check;
}


void getDic(FILE * aPakFile, int aIsMainScript, sPlatform aPlatform, uint8_t * aBytes) {
    rewind(aPakFile);
    fseek(aPakFile, HEADER_MAGICLEN_SZ + HEADER_CHECK_SZ + (aIsMainScript ? HEADER_MAIN_SZ : 0), SEEK_SET);
    for(int i = 0; i < HEADER_DIC_SZ; i++) {
        aBytes[i] = fgetc(aPakFile);
    }
}


void getMainHeader(FILE * aPakFile, sPlatform aPlatform, uint8_t * aBytes) {
    rewind(aPakFile);
    fseek(aPakFile, HEADER_MAGICLEN_SZ + HEADER_CHECK_SZ, SEEK_SET);
    for(int i = 0; i < HEADER_MAIN_SZ; i++) {
        aBytes[i] = fgetc(aPakFile);
    }
}


size_t getMainHeaderSize() {
    return HEADER_MAGICLEN_SZ + HEADER_CHECK_SZ + HEADER_MAIN_SZ + HEADER_DIC_SZ;
}


size_t getHeaderSize() {
    return HEADER_MAGICLEN_SZ + HEADER_CHECK_SZ + HEADER_DIC_SZ;
}


size_t getPackedSize(FILE * aPakFile, int aIsMain, sPlatform aPlatform) {
    fseek(aPakFile, 0, SEEK_END);
    long num_bytes = ftell(aPakFile);
    return num_bytes - (aIsMain ? getMainHeaderSize() : getHeaderSize());
}


size_t readPackedBytes(FILE * aPakFile, int aIsMain, sPlatform aPlatform, uint8_t * aBytes) {
    size_t pak_size = getPackedSize(aPakFile, aIsMain, aPlatform);
    rewind(aPakFile);
    fseek(aPakFile, aIsMain ? getMainHeaderSize() : getHeaderSize(), SEEK_SET);
    size_t read = fread(aBytes, sizeof(uint8_t), pak_size, aPakFile);
    if(read != pak_size) {
        printf("ERROR: bad read !\n");
    }
    return read;
}


void depack_file(char * pak_name, char * depak_name, sPlatform platform) {
    FILE * pak_file = fopen(pak_name, "r");
    
    if(pak_file) {
        printf("Packed file: %s (%s)\n", pak_name, platform.desc);

        // other info
        uint8_t magic = getMagic(pak_file, platform);
        if(magic != 0xa1) {
            // error !
            printf("WARNING: invalid header (0x%02x), skipping...\n\n", magic);
            return;
        }
        uint16_t ismain = !getCheck(pak_file, platform);
        uint8_t * dic = (uint8_t *)malloc(HEADER_DIC_SZ);
        uint8_t * mainh = (uint8_t *)malloc(HEADER_MAIN_SZ);
        
        // get sizes
        size_t pak_size = getPackedSize(pak_file, ismain, platform);
        size_t depak_size = getDepackedSize(pak_file, platform);
        printf("Packed size: %zu / Depacked size : %zu (ratio %ld%%)\n", pak_size, depak_size, 100 - (100 * pak_size) / depak_size);

        uint8_t * pak_data = (uint8_t *)malloc(sizeof(uint8_t) * pak_size);
        uint8_t * depak_data = (uint8_t *)malloc(sizeof(uint8_t) * depak_size);
        
        // dictionary
        getDic(pak_file, ismain, platform, dic);
        
        // print info
        printf("Magic: 0x%02x / Dic bytes: ", magic);
        for(uint8_t idx = 0; idx < HEADER_DIC_SZ; idx++) {
            printf("%02x ", dic[idx]);
        }
        printf("\n");
        if(ismain) {
            getMainHeader(pak_file, platform, mainh);
            printf("MAIN SCRIPT / Header bytes: ");
            for(uint8_t idx = 0; idx < HEADER_MAIN_SZ; idx++) {
                printf("%02x ", mainh[idx]);
            }
            printf("\n");
        }

        // depack !
        if(readPackedBytes(pak_file, ismain, platform, pak_data) != pak_size) {
            printf("ERROR: packed bytes size error !!\n");
        }
        else {
            depak(pak_data, depak_data, pak_size, depak_size, dic);
        }

        // produce depack file
        FILE * outfile = fopen(depak_name, "w");
        uint32_t i = 0;
        for(i = 0; i < depak_size; i++) {
            fputc(depak_data[i], outfile);
        }
        printf("Wrote %u bytes to file %s\n\n", i, depak_name);
        fclose(outfile);
        
        // cleanup
        free(pak_data);
        free(depak_data);
        free(dic);
        free(mainh);
    }
    else {
        printf("ERROR: cannot open %s !\n\n", pak_name);
    }
}



// TODO: valid only for big endian
int depack_is_packed(uint8_t * pak_buffer) {
    return pak_buffer[0] == 0xa1;
}
uint32_t depack_get_size(uint8_t * pak_buffer) {
    return (pak_buffer[1] << 16) + (pak_buffer[2] << 8) + pak_buffer[3];
}
int depack_is_main(uint8_t * pak_buffer) {
    return !((pak_buffer[HEADER_MAGICLEN_SZ] << 8) + pak_buffer[HEADER_MAGICLEN_SZ + 1]);
}
uint8_t * depack_get_dic(uint8_t * pak_buffer) {
    uint8_t * dic = (uint8_t *)malloc(sizeof(uint8_t) * HEADER_DIC_SZ);
    printf("DEPACK: found dictionary ");
    uint8_t offset = HEADER_MAGICLEN_SZ + HEADER_CHECK_SZ;
    if(depack_is_main(pak_buffer)) {
        offset += HEADER_MAIN_SZ;
    }
    
    for(uint8_t idx = 0; idx < HEADER_DIC_SZ; idx++) {
        dic[idx] = pak_buffer[offset + idx];
        printf("%02x ", dic[idx]);
    }
    printf("\n");
    return dic;
}

uint8_t * depack_get_main_header(uint8_t * pak_buffer) {
    printf("DEPACK: found main header ");
    uint8_t offset = HEADER_MAGICLEN_SZ + HEADER_CHECK_SZ;
    uint8_t * main_header = (uint8_t *)malloc(sizeof(uint8_t) * HEADER_MAIN_SZ);
    for(uint8_t idx = 0; idx < HEADER_MAIN_SZ; idx++) {
        main_header[idx] = pak_buffer[offset + idx];
        printf("%02x ", main_header[idx]);
    }
    printf("\n");
    return main_header;
}


uint8_t * depack_buffer(uint8_t * pak_buffer) {
    uint8_t * depak_buffer = NULL;
    if(depack_is_packed(pak_buffer)) {
        // read headers
        uint32_t len = depack_get_size(pak_buffer);
        depak_buffer = (uint8_t *)malloc(sizeof(uint8_t) * len);
        uint16_t ismain = depack_is_main(pak_buffer);
        uint8_t * dic = depack_get_dic(pak_buffer);
        if(ismain) {
            // main header
            uint8_t * main_header = depack_get_main_header(pak_buffer);
            
            // TODO: j'en fais quoi ???
            free(main_header);
        }
        
        uint8_t * ptr = pak_buffer + (ismain ? getMainHeaderSize() : getHeaderSize());
        depak(ptr, depak_buffer, 0, len, dic);
        free(dic);
    }
    return depak_buffer;
}


void depack(char * path) {
    DIR * dir = NULL;
    FILE * file = NULL;
    struct dirent *ent;
    
    char pack_path[kPathLen] = {0};
    char depack_path[kPathLen] = {0};
    const char * depack_folder = kDepackFolder;
    const char sep = path[strlen(path) - 1] == '/' ? '\0' : kPathSeparator;
    
    if((dir = opendir(path)) != NULL) {
        // path is a folder
        // create output path
        memset(depack_path, 0, kPathLen);
        sprintf(depack_path, "%s%c%s", path, sep, depack_folder);
        mkdir(depack_path, 0777);
        
        while ((ent = readdir(dir)) != NULL) {
            if(ent->d_type == DT_REG) {
                // it's a file
                memset(pack_path, 0, kPathLen);
                sprintf(pack_path, "%s%c%s", path, sep, ent->d_name);
                sPlatform platform = guess_platform(pack_path);
                if(is_supported(platform)) {
                    memset(depack_path, 0, kPathLen);
                    sprintf(depack_path, "%s%c%s%c%s.%s", path, sep, depack_folder, sep, ent->d_name, kDepackExtension);
                    depack_file(pack_path, depack_path, platform);
                }
                else {
                    printf("WARNING: unsupported file: %s\n", ent->d_name);
                }
            }
        }
        closedir(dir);
    }
    else if((file = fopen(path, "r")) != NULL) {
        // path is a single file
        sPlatform platform = guess_platform(path);
        if(is_supported(platform)) {
            sprintf(depack_path, "%s.%s", path, kDepackExtension);
            depack_file(path, depack_path, platform);
        }
        else {
            printf("ERROR: unsupported file: %s\n", strrchr(path, kPathSeparator) + 1);
        }
    }
    else {
        // cannot open path or file
        printf("ERROR: cannot open path or file %s\n", path);
    }
}
