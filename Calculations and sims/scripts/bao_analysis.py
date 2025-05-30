import pandas as pd
import numpy as np

bao_data = pd.read_csv('data/bao/desi_y5_scale_factors.csv')
cov = np.load('data/growth_rate/fsigma8_covariance.npy')

class Cosmology:
    def __init__(self, alpha_S0=0.09):
        self.alpha_S0 = alpha_S0
    def compute_da_over_rs(self, z):
        return z * 18.4 * (1 + self.alpha_S0 * 0.01)

cosmo = Cosmology(alpha_S0=0.09)
bao_data['da_rs_etd_calc'] = [cosmo.compute_da_over_rs(z) for z in bao_data['z']]
residuals = bao_data['da_rs_etd'] - bao_data['da_rs_obs']
chi2 = residuals.T @ np.linalg.inv(cov) @ residuals
print(f"Chi²/dof = {chi2:.2f} / {len(bao_data)-2}")
