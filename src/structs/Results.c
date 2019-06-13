#include "./Results.h"

void initResults(Results *results, int i, int n) {
    results = (Results*)malloc(sizeof(Results));
    initMonitor(results->monitor, n)
    results->i = i;
}

void destroyResults(Results *results) {
    destroyMonitor(results->monitor);
    free(results);
}

