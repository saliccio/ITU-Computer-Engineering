import numpy as np
import matplotlib.pyplot as plt

def signal_1(n):
    return 5* np.exp(1j * (7*np.pi*n/8 + np.pi/3))

def signal_2(n):
    result = 1 # u[5]

    if n >= -2:
        result += 0.2*n

    if n <= 2:
        result += -0.2*n

    return result

def signal_3(n):
    return 1* (n >= 0)

def signal_4(t):

    if t >= -1 and t <= 0:
        return t +1
    elif t >= 0 and t <= 2:
        return 1
    elif t >= 2 and t <= 3:
        return -t +3
    return 0

def signal_5(t):
    return 5*np.sin(2*np.pi*t)*np.cos(np.pi*t-8)


n_values = np.arange(-100,101)
t_values = np.arange(-100,100,0.1)

signal_1_samples = np.zeros(n_values.shape, dtype=np.complex_)
signal_2_samples = np.zeros(n_values.shape)
signal_3_samples = np.zeros(n_values.shape)
signal_4_samples = np.zeros(t_values.shape)
signal_5_samples = np.zeros(t_values.shape)

for i in range(n_values.shape[0]):
    signal_1_samples[i] = signal_1(n_values[i])

for i in range(n_values.shape[0]):
    signal_2_samples[i] = signal_2(n_values[i])

for i in range(n_values.shape[0]):
    signal_3_samples[i] = signal_3(n_values[i])

for i in range(t_values.shape[0]):
    signal_4_samples[i] = signal_4(t_values[i])

for i in range(t_values.shape[0]):
    signal_5_samples[i] = signal_5(t_values[i])


### PART A

fig, ax = plt.subplots(2, 1, figsize=(15, 8))
ax[0].stem(n_values,np.real(signal_1_samples))
ax[0].set_title("x1 Real")
ax[1].stem(n_values,np.imag(signal_1_samples))
ax[1].set_title("x1 Imaginary")

fig.savefig('q1_a_1.png')
plt.close(fig)


plt.stem(n_values, signal_2_samples)
plt.savefig('q1_a_2.png')
plt.close()

plt.stem(n_values, signal_3_samples)
plt.savefig('q1_a_3.png')
plt.close()

plt.plot(t_values, signal_4_samples)
plt.savefig('q1_a_4.png')
plt.close()

plt.plot(t_values, signal_5_samples)
plt.savefig('q1_a_5.png')
plt.close()

### PART B

def y_continuous(t, x):
    return t*x(t/2)


signal_4_y = np.zeros(t_values.shape)
signal_5_y = np.zeros(t_values.shape)

for i in range(n_values.shape[0]):
    signal_4_y[i] = y_continuous(n_values[i], signal_4)

for i in range(n_values.shape[0]):
    signal_5_y[i] = y_continuous(n_values[i], signal_5)

plt.plot(t_values, signal_4_y)
plt.savefig('q1_b_4.png')
plt.close()

plt.plot(t_values, signal_5_y)
plt.savefig('q1_b_5.png')
plt.close()

### PART C

signal_1_y = np.cumsum(signal_1_samples)
signal_2_y = np.cumsum(signal_2_samples)
signal_3_y = np.cumsum(signal_3_samples)

fig, ax = plt.subplots(2, 1, figsize=(15, 8))
ax[0].stem(n_values,np.real(signal_1_y))
ax[0].set_title("x1 Real")
ax[1].stem(n_values,np.imag(signal_1_y))
ax[1].set_title("x1 Imaginary")
plt.savefig('q1_c_1.png')
plt.close()

plt.stem(n_values, signal_2_y)
plt.savefig('q1_c_2.png')
plt.close()

plt.stem(n_values, signal_3_y)
plt.savefig('q1_c_3.png')
plt.close()
