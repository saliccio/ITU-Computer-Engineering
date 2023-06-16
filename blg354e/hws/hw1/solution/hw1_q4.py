import numpy as np
import matplotlib.pyplot as plt

def x(n):

    result = 0

    if n >= -4:
        result += 1
    if n >= 4:
        result += -1
    if n >= -3:
        result += 1
    if n >= 3:
        result += -1
    if n >= -1:
        result += 1
    if n >= 1:
        result += -1
    return result
    
t_values = np.arange(-100,100,0.1)
n_values = np.arange(-100,101)

signal_1_samples = np.zeros(t_values.shape)
signal_2_samples = np.zeros(t_values.shape)
signal_3_samples = np.zeros(n_values.shape)
signal_4_samples = np.zeros(n_values.shape)

for i in range(t_values.shape[0]):
    signal_1_samples[i] = x(t_values[i]/2)+ x(t_values[i]*2)

for i in range(t_values.shape[0]):

    for j in range(1,21):
        signal_2_samples[i] += x(t_values[i]/j)

def isinteger(x):
    return np.equal(np.mod(x, 1), 0)


for i in range(n_values.shape[0]):
    signal_3_samples[i] = isinteger(n_values[i]/2)*x(n_values[i]/2)* + x(n_values[i]*2)


for i in range(n_values.shape[0]):

    for j in range(1,21):
        signal_4_samples[i] += isinteger(n_values[i]/j)*x(n_values[i]/j)


plt.plot(t_values, signal_1_samples)
plt.savefig('q4_1.png')
plt.close()


plt.plot(t_values, signal_2_samples)
plt.savefig('q4_2.png')
plt.close()

plt.stem(n_values, signal_3_samples)
plt.savefig('q4_3.png')
plt.close()

plt.stem(n_values, signal_4_samples)
plt.savefig('q4_4.png')
plt.close()

