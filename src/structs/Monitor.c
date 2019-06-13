#include "./Monitor.h"

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
    pthread_mutex_destroy(&monitor->mutex);
    pthread_mutex_destroy(&monitor->full);
    pthread_mutex_destroy(&monitor->empty);
    free(monitor->buffer);
}

