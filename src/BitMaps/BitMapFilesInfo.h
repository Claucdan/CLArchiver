#ifndef CLARCHIVER_BITMAPFILESINFO_H
#define CLARCHIVER_BITMAPFILESINFO_H
#include <stdio.h>
#include <stdint.h>

struct BitMapFilesInfo{
    uint8_t nameOfFile[20];
    uint32_t sizeOfFile;
    uint16_t sizeOfAlphabet;
    uint8_t * symbols;
    uint32_t * countOfThatSymbol;
};



void WriteBitMapFileInfo(const struct BitMapFilesInfo* bitMapFilesInfo,FILE* file,const __int32* offsetOfFile){
    fseek(file,*offsetOfFile,SEEK_SET);
    fwrite(&bitMapFilesInfo,
           sizeof(uint8_t)*20 + sizeof(uint32_t) + sizeof(uint16_t),
           1,
           file);
    fwrite(&bitMapFilesInfo->symbols,
           sizeof(uint8_t) * bitMapFilesInfo->sizeOfAlphabet,
           1,
           file);
    fwrite(&bitMapFilesInfo->countOfThatSymbol,
           sizeof(uint32_t) * bitMapFilesInfo->sizeOfAlphabet,
           1,
           file);
}

void ReadBitMapFileInfo(struct BitMapFilesInfo* bitMapFilesInfo,FILE* file,const __int32* offsetOfFile){
    fseek(file,*offsetOfFile,SEEK_SET);
    fread(&bitMapFilesInfo,
           sizeof(uint8_t)*20 + sizeof(uint32_t) + sizeof(uint16_t),
           1,
           file);

    bitMapFilesInfo->symbols = (uint8_t*) malloc(sizeof(uint8_t)*bitMapFilesInfo->sizeOfAlphabet);
    bitMapFilesInfo->countOfThatSymbol = (uint32_t*) malloc(sizeof(uint32_t)*bitMapFilesInfo->sizeOfAlphabet);
    fread(&bitMapFilesInfo->symbols,
           sizeof(uint8_t) * bitMapFilesInfo->sizeOfAlphabet,
           1,
           file);
    fread(&bitMapFilesInfo->countOfThatSymbol,
           sizeof(uint32_t) * bitMapFilesInfo->sizeOfAlphabet,
           1,
           file);
}

#endif //CLARCHIVER_BITMAPFILESINFO_H
