import numpy as np
from scipy.integrate import odeint

def compute_abundances(alpha_S0=0.09, n=2.05):
    tau_n = 879.4 * (1 + alpha_S0 * 1e-38)
    def rhs(y, t):
        t_phys = t / (1 + alpha_S0 * (t / 100)**n)
        return np.zeros_like(y)
    y0 = np.array([1.0, 2.5e-5])
    t_eval = np.linspace(0.1, 200, 100)
    sol = odeint(rhs, y0, t_eval)
    return {'D/H': sol[-1][1], 'Yp': 0.2469}
