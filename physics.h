#ifndef PHYSICS_H
#define PHYSICS_H

double R1(double T);
double R2(double T);

double F_magnetic(double I);
int relay_closed(double x);

double I2(double T2, double I1, double x);

double dI1_dt(double I1, double T1);
double dT1_dt(double I1, double T1);
double dT2_dt(double T2, double I1, double x);
double dv_dt(double x, double v, double I1);

void rk4_step(double* I1, double* T1, double* T2, double* x, double* v, double dt);

#endif
