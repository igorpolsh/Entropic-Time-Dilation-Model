
#include <stdio.h>
#include <math.h>

// Entropic parameters
double alpha = 0.09;
double S_0 = 1.2;
double n = 2.5;
double t_c = 2.0;
double delta_t = 0.4;
double S_early = 1e-4;

// Entropy function S(t)
double S_of_t(double t) {
    double tanh_trans = tanh((t - t_c)/delta_t);
    return S_early*pow(t, 1.5)*(1 - tanh_trans) + S_0*pow(t, n)*(1 + tanh_trans);
}

// Modified Hubble parameter H_ETD(a)
double H_LCDM(double a) {
    double H0 = 67.3;
    double omega_m = 0.3;
    double omega_lambda = 0.7;
    return H0 * sqrt(omega_m * pow(a, -3) + omega_lambda);
}

double H_ETD(double a, double S_t) {
    return H_LCDM(a) * sqrt(1 + alpha * S_t);
}

// Time dilation factor dτ/dt
double dtau_dt(double t) {
    return 1.0 / (1.0 + alpha * S_of_t(t));
}

// Angular diameter distance integral term
double integrand(double z, double dz) {
    double t = 1.0 / (1.0 + z); // proxy mapping z ↔ t in Gyr
    double a = 1.0 / (1.0 + z);
    double H = H_ETD(a, S_of_t(t));
    double numerator = sqrt(1 + alpha * S_0);
    double denominator = sqrt(1 + alpha * S_of_t(t));
    return (1.0 / H) * (numerator / denominator);
}

int main() {
    printf("Testing ETD entropy and expansion functions:\n\n");

    for (double t = 0.5; t <= 10.0; t += 0.5) {
        double S = S_of_t(t);
        double dtau = dtau_dt(t);
        printf("t = %.2f Gyr:\tS(t) = %.3e,\tdτ/dt = %.4f\n", t, S, dtau);
    }

    for (double z = 0.0; z <= 3.0; z += 0.5) {
        double t = 1.0 / (1.0 + z);
        double a = 1.0 / (1.0 + z);
        double S = S_of_t(t);
        double H = H_ETD(a, S);
        printf("z = %.2f:\tH_ETD(z) = %.3f km/s/Mpc\n", z, H);
    }

    return 0;
}
