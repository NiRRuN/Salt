#ifndef CONFIG_H
#define CONFIG_H

//Физика (Параметры)
extern double I1;
extern double T1;
extern double T2;
extern double x;
extern double v;

//Физика (Условия)
extern double T0;
extern double E1;
extern double E2;
extern double R10;
extern double R20;
extern double BETA1;
extern double BETA2;
extern double C1;
extern double C2;
extern double ALPHA1;
extern double ALPHA2;
extern double T_ENV;
extern double R_YAKOR;
extern double L1;
extern double K_MAGNET;
extern double X_CLOSED;
extern double MASS;
extern double K_SPRING;
extern double DAMPING;
extern double MAX_TEMPERATURE;

void load_config(const char* filename); // функция загрузки

#endif
