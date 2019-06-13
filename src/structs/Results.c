#include "./Results.h"

void initResults(Results *results, int i) {
    results = (Results*)malloc(sizeof(Results));
    results->i = i;
}

void destroyResults(Results *results) {
    destroyMonitor(results->monitor);
    free(results);
}

