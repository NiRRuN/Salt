#include "physics.h"
#include "config.h"

double R1(double T) { return R10 * (1 + BETA1 * (T - T0)); }
double R2(double T) { return R20 * (1 + BETA2 * (T - T0)); }

double F_magnetic(double I) { return K_MAGNET * I * I; }
int relay_closed(double x) { return x >= X_CLOSED; }

double I2(double T2, double I1, double x) {
    if (!relay_closed(x)) return 0.0;
    return E2 / (R2(T2) + R_YAKOR);
}
double dI1_dt(double I1, double T1) { return (E1 - R1(T1) * I1) / L1; }
double dT1_dt(double I1, double T1) { return (I1 * I1 * R1(T1) - ALPHA1 * (T1 - T_ENV)) / C1; }
double dT2_dt(double T2, double I1, double x) {
    double i2 = I2(T2, I1, x);
    return (i2 * i2 * R2(T2) - ALPHA2 * (T2 - T_ENV)) / C2;
}
double dv_dt(double x, double v, double I1) {
    double Fmag = F_magnetic(I1);
    return (Fmag - K_SPRING * x - DAMPING * v) / MASS;
}
void rk4_step(double* I1, double* T1, double* T2, double* x, double* v, double dt) {
    double k1_I = dI1_dt(*I1, *T1);
    double k1_T1 = dT1_dt(*I1, *T1);
    double k1_T2 = dT2_dt(*T2, *I1, *x);
    double k1_x = *v;
    double k1_v = dv_dt(*x, *v, *I1);

    double I1_2 = *I1 + 0.5 * dt * k1_I;
    double T1_2 = *T1 + 0.5 * dt * k1_T1;
    double T2_2 = *T2 + 0.5 * dt * k1_T2;
    double x2 = *x + 0.5 * dt * k1_x;
    double v2 = *v + 0.5 * dt * k1_v;

    double k2_I = dI1_dt(I1_2, T1_2);
    double k2_T1 = dT1_dt(I1_2, T1_2);
    double k2_T2 = dT2_dt(T2_2, I1_2, x2);
    double k2_x = v2;
    double k2_v = dv_dt(x2, v2, I1_2);

    *I1 += dt * k2_I;
    *T1 += dt * k2_T1;
    *T2 += dt * k2_T2;
    *x += dt * k2_x;
    *v += dt * k2_v;
}

