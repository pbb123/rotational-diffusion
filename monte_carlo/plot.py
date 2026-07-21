import numpy as np
from matplotlib import pyplot as plt

angle = np.loadtxt("angle.txt",skiprows=5)
m = np.loadtxt("m.txt",delimiter=" ",skiprows=5)

#plt.plot(np.arange(len(angle)),angle)

plt.hist(angle[200000:],bins=20)
plt.show()
# C(\tau) = <m \cdot m(t-\tau)>

