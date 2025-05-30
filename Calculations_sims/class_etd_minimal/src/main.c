#include <stdio.h>
#include "background.h"

int main() {
    for (double t = 0.5; t <= 10.0; t += 0.5) {
        double S = S_of_t(t);
        double dtau = 1.0 / (1.0 + 0.09 * S);
        printf("t = %.2f Gyr:   S(t) = %.3e,   dτ/dt = %.4f\n", t, S, dtau);
    }

    for (double z = 0.0; z <= 3.0; z += 0.5) {
        double a = 1.0 / (1.0 + z);
        double t = a; // crude proxy
        double H = H_ETD(a, t);
        printf("z = %.2f:   H_ETD(z) = %.3f km/s/Mpc\n", z, H);
    }

    return 0;
}
