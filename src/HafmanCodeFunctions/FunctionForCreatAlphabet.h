#ifndef CLARCHIVER_FUNCTIONFORCREATALPHABET_H
#define CLARCHIVER_FUNCTIONFORCREATALPHABET_H
#include <stdio.h>
#include <stdint.h>
#include <malloc.h>


struct Node{
    struct Node* next;
    uint16_t data;
};
struct Queue{
    struct Node* head;
    struct Node* tail;
    size_t size;
};

struct Dictionary{
    uint16_t** mass;
    size_t size;
};


void DictionaryAdd(struct Queue* queue,const uint16_t* data){
    if(queue->head == NULL){
        queue->head = (struct Node*)malloc(sizeof(struct Node));
        queue->tail = queue->head;
        queue->head->data = *data;
        queue->head->next = NULL;
    }
    else {
        queue->tail->next = (struct Node *) malloc(sizeof(struct Node));
        queue->tail = queue->tail->next;
        queue->tail->data = *data;
        queue->tail->next = NULL;
    }
    ++queue->size;
}


struct Dictionary* CreatDictionary(FILE* file){
    fseek(file,0,SEEK_SET);

    uint16_t dataToDictionary = 0;
    int8_t bufferForRead;
    int8_t flagToAdd = 0;

    struct Queue queue;
    queue.head = NULL;
    queue.tail = NULL;
    queue.size = 0;


    uint16_t* HashMap = (uint16_t*)malloc(65536*sizeof(uint16_t));
    for(int i=0;i<65536;i++)
        HashMap[i]=0;

    while(1){
        bufferForRead = fgetc(file);
        if(bufferForRead == EOF){
            break;
        }
        dataToDictionary<<=8;
        dataToDictionary+=bufferForRead;
        if(flagToAdd){
            if(HashMap[dataToDictionary] == 0) {
                DictionaryAdd(&queue,&dataToDictionary);
            }
            ++HashMap[dataToDictionary];
            dataToDictionary = 0;
        }
        flagToAdd=!flagToAdd;
    }

    struct Dictionary* dictionary = (struct Dictionary*) malloc(sizeof(struct Dictionary));
    dictionary->mass = (uint16_t**)malloc(sizeof(uint16_t*)*2);
    dictionary->size = 0;
    dictionary->mass[0] = (uint16_t*)malloc(sizeof(uint16_t)*queue.size);
    dictionary->mass[1] = (uint16_t*)malloc(sizeof(uint16_t)*queue.size);
    struct Node* now = queue.head;


    while (now != NULL){
        dictionary->mass[0][dictionary->size] = now->data;
        dictionary->mass[1][dictionary->size] = HashMap[now->data];
        struct Node* temp = now;
        now = now->next;
        free(temp);
        dictionary->size++;
    }

    free(HashMap);
    return dictionary;
}

#endif //CLARCHIVER_FUNCTIONFORCREATALPHABET_H
