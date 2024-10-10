#ifndef CLARCHIVER_BITMAPFILECL_H
#define CLARCHIVER_BITMAPFILECL_H
#include <stdio.h>

/*Header of '*.cl' archive*/
struct BitMapFileCL{
    unsigned int countOfFiles;
    size_t* offsetOfFiles;
};

/*Write header of archive to file*/
void WriteBitMapFileCL(struct BitMapFileCL* bitMapFileCl, FILE* file){
    fseek(file,0,SEEK_SET);
    fwrite(&bitMapFileCl->countOfFiles,sizeof(unsigned int),1,file);

    for(unsigned int i=0;i<bitMapFileCl->countOfFiles;i++){
        fwrite(&bitMapFileCl->offsetOfFiles[i],sizeof(size_t),1,file);
    }
}

/*Read header of archive from file*/
void ReadBitMapFileCL(struct BitMapFileCL* bitMapFileCl, FILE* file){
    fseek(file,0,SEEK_SET);
    fread(&bitMapFileCl->countOfFiles, sizeof(unsigned int),1,file);

    bitMapFileCl->offsetOfFiles = (size_t*)malloc(sizeof(size_t)*bitMapFileCl->countOfFiles);

    for(unsigned int i=0;i<bitMapFileCl->countOfFiles;i++){
        fread(&bitMapFileCl->offsetOfFiles[i],sizeof(size_t),1,file);
    }
}
#endif //CLARCHIVER_BITMAPFILECL_H
