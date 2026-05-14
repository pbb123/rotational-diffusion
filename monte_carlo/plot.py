import numpy as np
from matplotlib import pyplot as plt

data = np.loadtxt("out.txt",skiprows=100000)

plt.hist(data,bins=20)
plt.show()