#include "background.h"
#include <math.h>

double alpha = 0.09;
double S_0 = 1.2;
double n = 2.5;
double t_c = 2.0;
double delta_t = 0.4;
double S_early = 1e-4;

double S_of_t(double t) {
    double tanh_trans = tanh((t - t_c)/delta_t);
    return S_early * pow(t, 1.5) * (1 - tanh_trans) + S_0 * pow(t, n) * (1 + tanh_trans);
}

double H_LCDM(double a) {
    double H0 = 67.3;
    double omega_m = 0.3;
    double omega_lambda = 0.7;
    return H0 * sqrt(omega_m * pow(a, -3) + omega_lambda);
}

double H_ETD(double a, double t) {
    return H_LCDM(a) * sqrt(1 + alpha * S_of_t(t));
}
