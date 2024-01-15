#!/usr/bin/env python3

# метод наименьших квадратов

import numpy as np
import matplotlib.pyplot as plt
import scipy.fftpack

import pandas as pd
plt.rcParams['figure.figsize'] = (20.0, 10.0)
 
# Reading Data
data = pd.read_csv('ema2.csv')
print(data.shape)
data.head()
 
 
# Collecting X and Y
X = data['r'].values
Y = data['la'].values

print(X)
print(Y)

mean_x = np.mean(X)
mean_y = np.mean(Y)
 
# Total number of values
n = len(X)
 
# Using the formula to calculate m and c
numer = 0
denom = 0
for i in range(n):
  numer += (X[i] - mean_x) * (Y[i] - mean_y)
  denom += (X[i] - mean_x) ** 2
m = numer / denom
c = mean_y - (m * mean_x)
 
# Print coefficients
print(m, c)


# Plotting Values and Regression Line
max_x = np.max(X) + 100
min_x = np.min(X) - 100
# Calculating line values x and y
x = np.linspace(min_x, max_x, 1000)
y = c + m * x 
 
# Ploting Line
plt.plot(x, y, color='#52b920', label='Regression Line')
# Ploting Scatter Points
plt.plot(X, Y, c='#ef4423', label='Scatter Plot')

plt.xlabel('r')
plt.ylabel('la')
plt.xlim(0, 60)
plt.ylim(10,11)
plt.legend()
plt.grid()
plt.show()



