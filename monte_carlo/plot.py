import numpy as np
from matplotlib import pyplot as plt

y = np.loadtxt("out.txt")

y1=y[::2]
y2=y[1::2]


x1=np.arange(np.size(y1))
x2=np.arange(np.size(y2))

plt.plot(x1,y1,label="-<m,E>")
plt.plot(x2,y2,label="<m,m0>")
plt.legend()
plt.savefig("./fig.png")

