#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "./../constants.h"


void procesLine(char *line,char *param1,char *param2,char *param3){
    char *token;
    token = strtok(line,",");
    token = strtok(NULL,",");
    token = strtok(NULL,",");
    strcpy(param1,token);
    token = strtok(NULL,",");
    strcpy(param2,token);
    token = strtok(NULL,",");
    strcpy(param3,token);
}


void createMsg(float realMedia,float imagineMedia,float power,float sumNoise,int pid,int n,char *msg) {
    sprintf(msg,"%i;%i;%f;%f;%f;%f", pid, n, realMedia, imagineMedia, power, sumNoise);
}


int main(int argc, char *argv[]) {
    int n = 0;
    char **data;
    float sumImagine = 0;
    float sumReal = 0;
    float sumNoise = 0;
    float potencia = 0;
    char *m = malloc(sizeof(char)*100);

    while(read(atoi(argv[1]),m,100) != 3){
        printf("n:%i\n",n);
        n++;
        char *rdata = malloc(sizeof(char)*30);
        char *idata = malloc(sizeof(char)*30);
        char *ndata = malloc(sizeof(char)*30);
        procesLine(m,rdata,idata,ndata);
        sumReal = sumReal + atof(rdata);
        sumImagine = sumImagine + atof(idata);
        sumNoise = sumNoise + atof(ndata);
        potencia = potencia+sqrt(atof(rdata)*atof(rdata)+atof(idata)*atof(idata));
        strcpy(m,"");
        free(rdata);
        free(idata);
        free(ndata);
        rdata = NULL;
        idata = NULL;
        ndata = NULL;
    }

    char *msg = malloc(sizeof(char)*100);
    if (n != 0) {
        float realMedia = sumReal/n;
        float imagineMedia = sumImagine/n;
        float power = sqrt((sumReal*sumReal+sumImagine*sumImagine));

        int mypid = getpid();
        createMsg(realMedia,imagineMedia,potencia,sumNoise,mypid,n,msg);

        if (write(atoi(argv[2]),msg,100) != 100) {
            exit(ERROR);
        }
        exit(OK);
    }

    sprintf(msg, "%d;0", getpid());
    if (write(atoi(argv[2]), msg, 100) != 100) {
        printf("Error en escribir en el pipe");
        exit(ERROR);
    }
    exit(OK);

}
