//
// Created by elija on 12/3/2025.
//

#ifndef MULTITHREAD_PARALLEL_DATA_ANALYSIS_WORKER_H
#define MULTITHREAD_PARALLEL_DATA_ANALYSIS_WORKER_H
#include "Statistics.h"
#include <pthread.h>


extern pthread_mutex_t lock;

typedef struct {
    char track_id[64];
    char track_name[64];
    char artist[64];
    char album[64];
    char release_date[64];
    float numeric[numFields];





}musicRow;

void* Chunk_Thread(void *arg);

typedef struct {
    musicRow *rows; // pointer to parsed rows in CSV file
    int startIndex;
    int endIndex;
    int typesum;
    float sum[numFields];
    float min[numFields];
    float max[numFields];
    float avg[numFields];


}SpotArgs;

#endif //MULTITHREAD_PARALLEL_DATA_ANALYSIS_WORKER_H