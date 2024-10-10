#ifndef CLARCHIVER_BITMAPFILESINFO_H
#define CLARCHIVER_BITMAPFILESINFO_H
#include <stdio.h>

struct BitMapFilesInfo{
    unsigned char nameOfFile[20];
    size_t sizeOfFile;
    unsigned int sizeOfAlphabet;
    unsigned char* symbols;
    unsigned char* countOfThatSymbol;
};



#endif //CLARCHIVER_BITMAPFILESINFO_H
