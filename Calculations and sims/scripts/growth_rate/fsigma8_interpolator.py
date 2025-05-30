import numpy as np
from scipy.interpolate import interp1d

z_vals = np.array([0.38, 0.51, 0.61])
fsigma8_vals = np.array([0.46, 0.43, 0.41])

interp = interp1d(z_vals, fsigma8_vals, kind='linear')
print(interp(0.5))
