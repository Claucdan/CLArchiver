#ifndef CLARCHIVER_BITMAPFILECL_H
#define CLARCHIVER_BITMAPFILECL_H
#include <stdio.h>
#include <stdint.h>

/*Header of '*.cl' archive*/
struct BitMapFileCL{
    uint16_t countOfFiles;
    uint32_t* offsetOfFiles;
};


/*Write header of archive to file*/
void WriteBitMapFileCL(const struct BitMapFileCL* bitMapFileCl, FILE* file){
    fseek(file,0,SEEK_SET);
    fwrite(&bitMapFileCl->countOfFiles,sizeof(uint16_t),1,file);

    fwrite(bitMapFileCl->offsetOfFiles,sizeof(uint32_t)*bitMapFileCl->countOfFiles,1,file);
}

/*Read header of archive from file*/
void ReadBitMapFileCL(struct BitMapFileCL* bitMapFileCl, FILE* file){
    fseek(file,0,SEEK_SET);
    fread(&bitMapFileCl->countOfFiles, sizeof(uint16_t),1,file);

    bitMapFileCl->offsetOfFiles = (uint32_t*)malloc(sizeof(uint32_t)*bitMapFileCl->countOfFiles);
    fread(bitMapFileCl->offsetOfFiles,sizeof(uint32_t) * bitMapFileCl->countOfFiles,1,file);
}
#endif //CLARCHIVER_BITMAPFILECL_H
