//
// Created by elija on 12/3/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <pthread.h>

#include "Worker.h"
#define MAX_ROW 1000
musicRow rowArray[MAX_ROW];
pthread_mutex_t lock;
int main(void) {
    int totalRows = 15;
    int totalCols = 49;
    char cwd[1024];
    _getcwd(cwd, sizeof(cwd));
    printf("Current working directory: %s\n", cwd);
    char buffer[1000];
    char *data;

    FILE *spotifyFile = fopen("C:\\Users\\elija\\CLionProjects\\Multithread Parallel Data Analysis\\spotify_analysis_dataset.csv", "r");
    if (spotifyFile == NULL) {
        printf("Error: Unable to open file.");
        exit(-1);


    }
    printf("Can open file");

    // read in lines

    // will count how many rows are loaded
    int count = 0;


    // read one line from CSV into buffer
    while (fgets(buffer,sizeof(buffer), spotifyFile)) {
        if (count == 0) {
            count++;
            continue;
        }
        printf("%s\n", buffer);
        musicRow row;

        char *tok = strtok(buffer, ",");

        // strcpy copies a string from source to destination
        strcpy(row.track_id, tok);
        tok = strtok(NULL, ",");

        strcpy(row.track_name, tok);
        tok = strtok(NULL, ",");

        strcpy(row.artist, tok);
        tok = strtok(NULL, ",");

        strcpy(row.album, tok);
        tok = strtok(NULL, ",");

        strcpy(row.release_date, tok);
        tok = strtok(NULL, ",");

        for (int f = 0; f < numFields; f++) {
            row.numeric[f] = atof(tok);
            tok = strtok(NULL, ",");
        }




        rowArray[count - 1] = row;
        count++;
    }


    SpotArgs a1 = {
        .rows = rowArray, .startIndex = 0, .endIndex = 2, .typesum = 0
    };

    SpotArgs a2 = {
        .rows = rowArray, .startIndex = 2, .endIndex = 4, .typesum = 0
    };

    SpotArgs a3 = {
        .rows = rowArray, .startIndex = 4, .endIndex = 6, .typesum = 0
    };

    SpotArgs a4 = {
        .rows = rowArray, .startIndex = 6, .endIndex = 8, .typesum = 0
    };

    SpotArgs a5 = {
        .rows = rowArray, .startIndex = 8, .endIndex = 10, .typesum = 0
    };

    SpotArgs a6 = {
        .rows = rowArray, .startIndex = 10, .endIndex = 11, .typesum = 0
    };

    SpotArgs a7 = {
        .rows = rowArray, .startIndex = 12, .endIndex = 14, .typesum = 0
    };
    SpotArgs a8 = {
        .rows = rowArray, .startIndex = 14, .endIndex = 15, .typesum = 0
    };
    pthread_t t1, t2, t3, t4, t5, t6, t7, t8; // Creating eight threads to handle the processes quickly
    pthread_mutex_init(&lock, NULL); // gives ability to use lock
    pthread_create(&t1, NULL, Chunk_Thread, &a1);
    pthread_create(&t2, NULL, Chunk_Thread, &a2);
    pthread_create(&t3, NULL, Chunk_Thread, &a3);
    pthread_create(&t4, NULL, Chunk_Thread, &a4);
    pthread_create(&t5, NULL, Chunk_Thread, &a5);
    pthread_create(&t6, NULL, Chunk_Thread, &a6);
    pthread_create(&t7, NULL, Chunk_Thread, &a7);
    pthread_create(&t8, NULL, Chunk_Thread, &a8);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);
    pthread_join(t6, NULL);
    pthread_join(t7, NULL);
    pthread_join(t8, NULL);

    float Sum[numFields] = {0};
    float rowNumber;
    for (int f = 0; f < numFields; f++) {
        Sum[f] = a1.sum[f] + a2.sum[f] + a3.sum[f] + a4.sum[f] + a5.sum[f] + a6.sum[f] + a7.sum[f] + a8.sum[f];

        printf("a1.sum[%d] = %f\n", f, Sum[f]);
        printf("Field %d total sum: %f\n", f, Sum[f]);


    }


     char* fields[numFields] = {"Popularity", "Dancability ", "Energy", "Loudness", "Speechiness", "Accousticness", "Instramentalness", "Liveness", "Valence", "Tempo",  };



    int minIndex = 0;
    int maxIndex = numFields - 1;

    for (int f = 0; f < numFields; f++) {
        float mini = rowArray[0].numeric[f];
        float maxi = rowArray[0].numeric[f];

        for (int s = 1; s < totalRows; s++) {
            if (rowArray[s].numeric[f] < mini) mini = rowArray[s].numeric[f];
            if (rowArray[s].numeric[f] > maxi) maxi = rowArray[s].numeric[f]; {

            }
        }
        printf("Field: %s, MIN of Field: %f, MAX of Field: %f\n", fields[f], mini, maxi);
        }








    fclose(spotifyFile);
    pthread_mutex_destroy(&lock); // destroys the lock


    return 0;
}