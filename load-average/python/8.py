#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt
import scipy.fftpack





# 1. Linspace
N = 600
# Sample spacing
tmax = 3/4
T = tmax / N # =1.0 / 800.0
x1 = np.linspace(0.0, N*T, N)
y1 = np.sin(50.0 * 2.0*np.pi*x1) + 0.5*np.sin(80.0 * 2.0*np.pi*x1)
yf1 = scipy.fftpack.fft(y1)
xf1 = np.linspace(0.0, 1.0/(2.0*T), N//2)




# 2. Integer number of periods
tmax = 1
T = tmax / N # Sample spacing
x2 = np.linspace(0.0, N*T, N)
y2 = np.sin(50.0 * 2.0*np.pi*x2) + 0.5*np.sin(80.0 * 2.0*np.pi*x2)
yf2 = scipy.fftpack.fft(y2)
xf2 = np.linspace(0.0, 1.0/(2.0*T), N//2)




# 3. Correct positioning of dates relatively to FFT theory ('arange' instead of 'linspace')
tmax = 1
T = tmax / N # Sample spacing
x3 = T * np.arange(N)
y3 = np.sin(50.0 * 2.0*np.pi*x3) + 0.5*np.sin(80.0 * 2.0*np.pi*x3)
yf3 = scipy.fftpack.fft(y3)
xf3 = 1/(N*T) * np.arange(N)[:N//2]




fig, ax = plt.subplots()
# Plotting only the left part of the spectrum to not show aliasing
ax.plot(xf1, 2.0/N * np.abs(yf1[:N//2]), label='fftpack tutorial')
ax.plot(xf2, 2.0/N * np.abs(yf2[:N//2]), label='Integer number of periods')
ax.plot(xf3, 2.0/N * np.abs(yf3[:N//2]), label='Correct positioning of dates')
plt.legend()
plt.grid()
plt.show()


