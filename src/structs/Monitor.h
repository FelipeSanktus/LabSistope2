#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct Monitor {
    int n;
    int current;
    int *buffer;
    pthread_mutex_t mutex;
    pthread_mutex_t empty;
    pthread_mutex_t full;
} Monitor;

void initMonitor(Monitor *monitor, int bufferLen);

void *readBuffer(void *monitor);

void *writeBuffer(void *monitor);

void destroyMonitor(Monitor *monitor);

