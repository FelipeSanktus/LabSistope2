#include "./functions.h"


void *bufferConsume(void *results) {
    float *visibilities = (float*)malloc(sizeof(float) * 3);

    for (int i=0; i < ((Results*)results)->monitor->n; i++) {
        printf("Esperando a que el buffer %d se llene...\n", ((Results *)results)->i);
        visibilities = readBuffer(((Results*)results)->monitor);
        printf("Se llenó el buffer %d!!!\n", ((Results *)results)->i);

        float sumImagine = 0;
        float sumReal = 0;
        float sumNoise = 0;
        float potencia = 0;

        ((Results*)results)->realMean = ((Results*)results)->realMean + visibilities[0] / ((Results*)results)->monitor->n;
        ((Results*)results)->imgMean = ((Results*)results)->imgMean + visibilities[1] / ((Results*)results)->monitor->n;
        ((Results*)results)->noise = ((Results*)results)->noise + visibilities[2];
        ((Results*)results)->power = ((Results*)results)-> power + sqrt(visibilities[0]*visibilities[0] + visibilities[1]*visibilities[1]);

    }
    return (void*) OK;
}
