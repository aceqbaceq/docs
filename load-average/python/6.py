#!/usr/bin/env python3

import numpy as np
from matplotlib import pyplot as plt
from scipy.fftpack import rfft, rfftfreq


START=0
END=10   # duration in seconds
STEP=1  # sampling frequency
T=1  # period in seconds


x=np.linspace(START, END, STEP*END)   # start, stop, numer of steps
#y=np.sin((2*np.pi/1)*x) + 2*np.sin((2*np.pi/3)*x) + 0.5*np.sin((2*np.pi/0.5)*x)       # radians, signal
#y=np.sin((2*np.pi/T)*x)       # radians, signal

y=x-x+1       # radians, signal


n = y.size
yf = rfft(y)  # fourier
xf = rfftfreq(STEP*END, 1/STEP)






plt.subplot(2, 1, 1)                   # Plot the amplitude response
plt.suptitle('Bode Plot')            
plt.plot(x, y, linestyle='solid',linewidth=2.0)     # Convert to dB
plt.ylabel('Amplitude')
plt.xlim(-0.2, END)
plt.ylim(-4, 4)
plt.grid()



plt.subplot(2, 1, 2)                   # Plot the phase response
#plt.plot(xf, np.abs(yf))    # Convert argument to degrees
plt.plot(xf[:(STEP*END)//2], 2.0/(STEP*END) * np.abs(yf[:(STEP*END)//2]), label='fftpack tutorial',linewidth=2.0)
plt.xlabel('Frequency [Hz]')
plt.ylabel('Amplitude ')
plt.xlim(-0.2, 3)
plt.ylim(0,3)
plt.xticks([0, 0.5, 1, 2, 3 ])

plt.grid()
plt.show()

