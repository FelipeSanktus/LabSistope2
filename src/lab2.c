#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "./../constants.h"

void parseLine(char *line, char *param1, char *param2) {
    char *token = strtok(line,",");
    strcpy(param1, token);
    token = strtok(NULL,",");
    strcpy(param2, token);
    return;
}

int main(int argc, char * argv[]) {
    int c, i;
    int n = 0;
    int ppid = 0;
    int radius = 0;
    int show = FALSE;
    int *childs = NULL;
    char *input = NULL;
    char *output = NULL;
    int **descriptors = NULL;

    while ((c = getopt(argc, argv, "i:o:d:n:b")) != -1) {
        switch (c) {
            case 'i':
                input = (char*) malloc(30 * sizeof(char));
                strcpy(input, optarg);
                break;
            case 'o':
                output = (char*) malloc(30 * sizeof(char));
                strcpy(output, optarg);
                break;
            case 'd':
                radius = atoi(optarg);
                break;
            case 'n':
                n = atoi(optarg);
                break;
            case 'b':
                show = TRUE;
                break;
        }
    }

    descriptors = (int**)malloc((2*n)*sizeof(int*));
    childs = (int*)malloc(n*sizeof(int));

    for (i=0; i<2*n; i++) {
        int *fd= (int*)malloc(2*sizeof(int));
        if (pipe(fd) == -1) {
            perror("No se pudo crear el pipe\n");
            exit(ERROR);
        }
        descriptors[i] = fd;
    }

    ppid = getpid();
    for (i=0; i<n; i++) {
        if (ppid == getpid()) {
            if (fork() == 0) {
                int pidhijo = getpid();
                childs[i] = pidhijo;
                int forRead = descriptors[2*i][0];
                int forWrite = descriptors[2*i+1][1];
                char *bufferRead = (char*)malloc(50*sizeof(char));
                char *bufferWrite = (char*)malloc(50*sizeof(char));
                sprintf(bufferRead,"%i",forRead);
                sprintf(bufferWrite,"%i",forWrite);
                char *newargv[] = {"./functions.out",bufferRead,bufferWrite,NULL};

                execvp(newargv[0],newargv);
            }
        }
    }

    if (ppid == getpid()) {
        char *reader = (char*)malloc(sizeof(char));
        char* linereader = (char*)malloc(sizeof(char)*100);
        FILE *file = fopen(input, "r");
        strcpy(linereader, "");

        if (file != NULL) {
            while (!feof(file)) {

                if (fread(reader, 1, 1, file) < 0) {
                    printf("Error al leer archivo\n");
                    exit(ERROR);
                }

                if ((*reader == '\n' || *reader == EOF) && (int)strlen(linereader) > 1) {
                    char *aux = (char*)malloc(sizeof(char)*100);
                    strcpy(aux,linereader);
                    char *procesLine[2];
                    procesLine[0] = (char*)malloc(50 * sizeof(char));
                    procesLine[1] = (char*)malloc(50 * sizeof(char));
                    parseLine(linereader, procesLine[0], procesLine[1]);

                    float pointU = atof(procesLine[0]);
                    float pointV = atof(procesLine[1]);
                    float radio = sqrtf((pointU*pointU+pointV*pointV));

                    for (int i=0; i<n; i++) {
                        float min = i*radius;
                        float max = (i+1)*radius;

                        if (radio >= min && radio < max) {
                            if(write(descriptors[2*i][1], aux, 100) != 100){
                                printf("Error en escribir en el pipe\n");
                                exit(ERROR);
                            }
                        } else if (radio >= n * radius && i == n-1) {
                            if (write(descriptors[2*(n-1)][1], aux, 100) != 100){
                                printf("Error en escribir en el pipe\n");
                                exit(ERROR);
                            }
                        }
                    }

                    free(linereader);
                    linereader = NULL;
                    linereader = (char*)malloc(100*sizeof(char));
                    strcpy(linereader, "");
                } else {
                    strcat(linereader, reader);
                }
            }

            for (int i=0;i<n;i++) {
                if (write(descriptors[2*i][1],"FIN",3) != 3) {
                    printf("Error en escribir en el pipe\n");
                    exit(ERROR);
                }
            }

            fclose(file);
        } else {
            perror(input);
            exit(ERROR);
        }

        char* buffer = (char*)malloc(50 * sizeof(char));
        char* token = (char*)malloc(12 * sizeof(char));
        file = fopen(output, "wb");
        char *buff = malloc(sizeof(char)*100);
        char *childpid= malloc(sizeof(char)*100);

        for (i=0; i<n; i++) {
            if (read(descriptors[2*i+1][0],buff,100) != 100) {
                exit(ERROR);
            }

            token = strtok(buff, ";");
            strcpy(childpid, token);
            token = strtok(NULL,";");

            if (show) {
                printf("Soy el hijo de pid: %s, ", childpid);
                printf("procesé: %s visibilidades\n", token);
            }

            if (atoi(token) == 0) {
                strcpy(buff, "0;0;0;0;0");
                token = strtok(buff, ";");
            }
            token = strtok(NULL,";");

            sprintf(buffer, "Disco %d:\n", i+1);
            fwrite(buffer, 1, strlen(buffer), file);
            strcpy(buffer, "");
            sprintf(buffer, "Media real: %s\n", token);
            fwrite(buffer, 1, strlen(buffer), file);
            strcpy(buffer, "");
            token = strtok(NULL,";");
            sprintf(buffer, "Media imaginaria: %s\n", token);
            fwrite(buffer, 1, strlen(buffer), file);
            strcpy(buffer, "");
            token = strtok(NULL,";");
            sprintf(buffer, "Potencia: %s\n", token);
            fwrite(buffer, 1, strlen(buffer), file);
            strcpy(buffer, "");
            token = strtok(NULL,";");
            sprintf(buffer, "Ruido total: %s\n", token);
            fwrite(buffer, 1, strlen(buffer), file);
            strcpy(buffer, "");
        }
        fclose(file);

        return OK;
    }
}
