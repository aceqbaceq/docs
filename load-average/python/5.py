#!/usr/bin/env python3

import numpy as np
from matplotlib import pyplot as plt




SAMPLE_RATE = 12/60  # Hertz
DURATION = 1000  # Seconds
print("SAMPLE RATE =", SAMPLE_RATE)




def generate_sine_wave(freq, sample_rate, duration):
    x = np.linspace(0, duration, sample_rate * duration, endpoint=False)
    frequencies = x * freq
    # 2pi because np.sin takes radians
    y = 10*np.sin((2 * np.pi) * frequencies)
    return x, y



# Generate a 2 hertz sine wave that lasts for 5 seconds
x, y = generate_sine_wave(1, SAMPLE_RATE, DURATION)
plt.plot(x, y)
plt.show()
plt.grid()


