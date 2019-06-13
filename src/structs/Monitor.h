#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "./../../constants.h"

typedef struct Monitor {
    int n;
    int current;
    int reading;
    float **buffer;
    pthread_mutex_t mutex;
    pthread_mutex_t empty;
    pthread_mutex_t full;
    pthread_mutex_t reading_mutex;
    pthread_cond_t empty_cond;
    pthread_cond_t full_cond;
    pthread_cond_t reading_cond;
} Monitor;

Monitor *initMonitor(int bufferLen);

float* readBuffer(Monitor *monitor);

void writeBuffer(Monitor *monitor, float *visibilities);

void destroyMonitor(Monitor *monitor);

