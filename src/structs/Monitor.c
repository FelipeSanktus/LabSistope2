#include "./Monitor.h"

Monitor *initMonitor(int bufferLen) {
    Monitor *monitor = (Monitor*)malloc(sizeof(Monitor));
    monitor->n = bufferLen;
    monitor->current = 0;
    monitor->reading = FALSE;
    monitor->buffer = (float**)malloc(sizeof(float*) * bufferLen);

    for (int i=0; i < bufferLen; i++) {
        monitor->buffer[i] = (float*)malloc(sizeof(float) * 3);
        monitor->buffer[i][0] = 9;
        monitor->buffer[i][1] = 9;
        monitor->buffer[i][2] = 9;
    }

    pthread_cond_init(&monitor->full_cond, NULL);
    pthread_cond_init(&monitor->empty_cond, NULL);
    pthread_cond_init(&monitor->reading_cond, NULL);
    pthread_cond_init(&monitor->empty_cond, NULL);
    pthread_mutex_init(&monitor->mutex, NULL);
    pthread_mutex_init(&monitor->full, NULL);
    pthread_mutex_init(&monitor->empty, NULL);
    pthread_mutex_init(&monitor->reading_mutex, NULL);
    pthread_mutex_init(&monitor->mutex, NULL);

    return monitor;
}

float *readBuffer(Monitor *monitor) {
    if (!monitor->reading) {
        pthread_cond_wait(&monitor->reading_cond, &monitor->reading_mutex);
    }

    if (monitor->current == 0) {
        monitor->reading = FALSE;
        pthread_cond_signal(&monitor->empty_cond);
        pthread_cond_wait(&monitor->full_cond, &monitor->full);
    }

    float *visibilities = (float*)malloc(sizeof(float) * 3);

    pthread_mutex_lock(&monitor->mutex);
    visibilities[0] = monitor->buffer[monitor->current][0];
    visibilities[1] = monitor->buffer[monitor->current][1];
    visibilities[2] = monitor->buffer[monitor->current][2];
    monitor->current--;
    pthread_mutex_unlock(&monitor->mutex);

    return visibilities;
}

void writeBuffer(Monitor *monitor, float *visibilities) {
    if (monitor->reading) {
        pthread_cond_wait(&monitor->reading_cond, &monitor->reading_mutex);
    }

    if (monitor->current == monitor->n) {
        monitor->reading = TRUE;
        pthread_cond_signal(&monitor->full_cond);
        pthread_cond_wait(&monitor->empty_cond, &monitor->empty);
    }

    pthread_mutex_lock(&monitor->mutex);
    monitor->buffer[monitor->current][0] = visibilities[0];
    monitor->buffer[monitor->current][1] = visibilities[1];
    monitor->buffer[monitor->current][2] = visibilities[2];
    printf("%d =>  %f, %f, %f\n", monitor->current, monitor->buffer[monitor->current][0], monitor->buffer[monitor->current][1], monitor->buffer[monitor->current][2]);
    monitor->current++;
    pthread_mutex_unlock(&monitor->mutex);
}

void destroyMonitor(Monitor *monitor) {
    pthread_mutex_destroy(&monitor->mutex);
    pthread_mutex_destroy(&monitor->full);
    pthread_mutex_destroy(&monitor->empty);

    for (int i; i < monitor->n; i++) {
        free(monitor->buffer[i]);
    }
    free(monitor->buffer);
}

