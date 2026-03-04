//
// Created by elija on 12/3/2025.
//

#include "Worker.h"
#include <pthread.h>
#include <stdio.h>

int counter;


void* Chunk_Thread(void *arg) {
    SpotArgs *args = (SpotArgs*) arg;

    float sum = 0;

    for (int i = args->startIndex; i < args->endIndex; i++) {
       for (int f = 0; f < numFields; f++) {
           args->sum[f] += args->rows[i].numeric[f];
       }

        printf("Thread [%d - %d] running...\n", args->startIndex,args->endIndex);


    }

    args->typesum = sum;
    return NULL;
}

