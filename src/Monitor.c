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

void initMonitor(Monitor *monitor, int bufferLen) {
    monitor->n = bufferLen;
    monitor->current = 0;
    monitor->buffer = (int*)malloc(sizeof(int) * bufferLen);
    pthread_mutex_init(&monitor->mutex, NULL);
    pthread_mutex_init(&monitor->full, NULL);
    pthread_mutex_init(&monitor->empty, NULL);
    pthread_mutex_lock(&monitor->empty);
}

void *readBuffer(void *monitor) {
    // do something
    // SC
    // do something
}

void *writeBuffer(void *monitor) {
    // do something
    // SC
    // do something
}

void destroyMonitor(Monitor *monitor) {
    free(monitor->buffer);
    pthread_mutex_init(&monitor->mutex, NULL);
    pthread_mutex_init(&monitor->full, NULL);
    pthread_mutex_init(&monitor->empty, NULL);
    pthread_mutex_lock(&monitor->empty);
}

