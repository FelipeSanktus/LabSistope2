#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "./Monitor.h"

typedef struct Results {
    int i;
    float realMean;
    float imgMean;
    float power;
    float noise;
    Monitor *monitor;
} Results;

void initResults(Results *results, int i);

void destroyResults(Results *results);

