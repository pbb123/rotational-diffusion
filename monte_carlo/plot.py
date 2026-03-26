import numpy as np
from matplotlib import pyplot as plt

y = np.loadtxt("out.txt")

T = y[0]
y1=y[1::2]
y2=y[2::2]


x1=np.arange(np.size(y1))
x2=np.arange(np.size(y2))

plt.plot(x1,y1,label="$-\\left<m,E \\right>$")
plt.plot(x2,y2,label="$\\left<m,m_0 \\right>$")
plt.title(f"T={T}")

plt.ylim(-1.1,1.1)
plt.xlabel("Time step")

plt.legend()
plt.savefig(f"./figT={T}.png")

