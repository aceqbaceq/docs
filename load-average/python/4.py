#!/usr/bin/env python3

from scipy import signal
import numpy as np
b = signal.firwin(80, 0.5, window=('kaiser', 8))
w, h = signal.freqz(b)



