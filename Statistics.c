//
// Created by elija on 12/3/2025.
//

#include "Statistics.h"

#include <stdio.h>

#include "Worker.h"


void* total_Stats(void* args) {
    SpotArgs* data = (SpotArgs*) args;
    for (int i = data->startIndex; i < data->endIndex; i++) {
        float rowNumber;
        for (int f = 0; f < numFields; f++) {
            float row_number = data->rows[i].numeric[f];


            // SUM
            data->sum[f] += row_number;

            // MIN
            if (row_number < data->min[f]) {
                data->min[f] = row_number;
            }
            // MAX
            if (row_number > data->max[f]) {
                data->max[f] = row_number;
            }
            pthread_mutex_unlock(&lock);

        }
    }
    return NULL;
}






