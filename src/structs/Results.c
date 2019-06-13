#include "./Results.h"

Results *initResults(int i, int n) {
    Results *results = (Results*)malloc(sizeof(Results));
    results->i = i;
    results->monitor = initMonitor(n);

    return results;
}

void destroyResults(Results *results) {
    destroyMonitor(results->monitor);
    free(results);
}

