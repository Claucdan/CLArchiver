#ifndef CLARCHIVER_BITMAPFILESINFO_H
#define CLARCHIVER_BITMAPFILESINFO_H
#include <stdio.h>
#include <stdint.h>


/*Header of file information*/
struct BitMapFilesInfo{
    uint8_t nameOfFile[20];
    uint32_t sizeOfFile;
    uint16_t sizeOfAlphabet;
    uint16_t * symbols;
    uint32_t * countOfThatSymbol;
};


/*Write header of file into archive*/
void WriteBitMapFileInfo(const struct BitMapFilesInfo* bitMapFilesInfo,FILE* file,const uint32_t* offsetOfFile){
    fseek(file,*offsetOfFile,SEEK_SET);
    fwrite(bitMapFilesInfo->nameOfFile,
          sizeof(uint8_t)*20,
          1,
          file);
    fwrite(&bitMapFilesInfo->sizeOfFile,
          sizeof(uint32_t),
          1,
          file);
    fwrite(&bitMapFilesInfo->sizeOfAlphabet,
          sizeof(uint16_t),
          1,
          file);
    fwrite(bitMapFilesInfo->symbols,
           sizeof(uint16_t) * bitMapFilesInfo->sizeOfAlphabet,
           1,
           file);
    fwrite(bitMapFilesInfo->countOfThatSymbol,
           sizeof(uint32_t) * bitMapFilesInfo->sizeOfAlphabet,
           1,
           file);
}

/*Read header of file from archive*/
void ReadBitMapFileInfo(struct BitMapFilesInfo* bitMapFilesInfo,FILE* file,const uint32_t* offsetOfFile){
    fseek(file,*offsetOfFile,SEEK_SET);
    fread(bitMapFilesInfo->nameOfFile,
           sizeof(uint8_t)*20,
           1,
           file);
    fread(&bitMapFilesInfo->sizeOfFile,
          sizeof(uint32_t),
          1,
          file);
    fread(&bitMapFilesInfo->sizeOfAlphabet,
          sizeof(uint16_t),
          1,
          file);
    bitMapFilesInfo->symbols = (uint16_t*) malloc(sizeof(uint16_t)*bitMapFilesInfo->sizeOfAlphabet);
    bitMapFilesInfo->countOfThatSymbol = (uint32_t*) malloc(sizeof(uint32_t)*bitMapFilesInfo->sizeOfAlphabet);
    fread(bitMapFilesInfo->symbols,
           sizeof(uint16_t) * bitMapFilesInfo->sizeOfAlphabet,
           1,
           file);
    fread(bitMapFilesInfo->countOfThatSymbol,
           sizeof(uint32_t) * bitMapFilesInfo->sizeOfAlphabet,
           1,
           file);
}

#endif //CLARCHIVER_BITMAPFILESINFO_H
