#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Физика (Условия)
double T0 = 293.0;
double E1 = 20.0;
double E2 = 10.0;
double R10 = 5.0;
double R20 = 5.0;
double BETA1 = 0.004;
double BETA2 = 0.005;
double C1 = 397.0;
double C2 = 397.0;
double ALPHA1 = 0.5;
double ALPHA2 = 0.5;
double T_ENV = 293.0;
double R_YAKOR = 5.0;
double L1 = 1.0;
double K_MAGNET = 0.1;
double X_CLOSED = 0.01;
double MASS = 0.05;
double K_SPRING = 10.0;
double DAMPING = 0.1;
double MAX_TEMPERATURE = 50.0;

//Физика (Параметры)
double I1 = 0;
double T1 = 293.0;
double T2 = 293.0;
double x = 0.0;
double v = 0.0;

void load_config(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return;

    char line[128], key[64], value[64];
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%63[^=]=%63[^\n]", key, value) == 2) {
            double val = atof(value);

            #define SET(k) if (strcmp(key, #k) == 0) k = val;

            SET(T0) SET(E1) SET(E2) SET(R10) SET(R20)
            SET(BETA1) SET(BETA2)
            SET(C1) SET(C2)
            SET(ALPHA1) SET(ALPHA2)
            SET(T_ENV) SET(R_YAKOR) SET(L1)
            SET(K_MAGNET) SET(X_CLOSED)
            SET(MASS) SET(K_SPRING) SET(DAMPING)
            SET(MAX_TEMPERATURE)
            SET(I1) SET(T1) SET(T2) SET(x) SET(v)
            #undef SET
        }
    }

    fclose(file);
}

