#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct Monitor {
    int n;
    int current;
    float **buffer;
    pthread_mutex_t mutex;
    pthread_mutex_t empty;
    pthread_mutex_t full;
    pthread_cond_t empty_cond;
    pthread_cond_t full_cond;
} Monitor;

void initMonitor(Monitor *monitor, int bufferLen);

float* readBuffer(Monitor *monitor);

void writeBuffer(Monitor *monitor, float *visibilities);

void destroyMonitor(Monitor *monitor);

