import subprocess
from itertools import product

import numpy as np
import scipy as scp
import matplotlib.pyplot as plt

def wigner_d_from_quaternion(l, m, n, q):
    """
    Computes a specific Wigner D-matrix element for given l, m, n from a quaternion.
    q: numpy array of shape (N,4) representing [[q0(t_0), q1(t_0), q2(t_0), q3(t_0)],...]
    """
    s2 = 1.4142135623730951 # sqrt(2)
    s6 = 2.449489742783178  # sqrt(6)
    
    # Map Mathematica's 1-indexed array access to 0-indexed Python arrays
    a = q[:,0] + 1j * q[:,3]
    b = q[:,2] + 1j * q[:,1]
    
    ap = np.conj(a)
    bp = np.conj(b)
    
    res = np.repeat(0.0 + 0.0j,q.shape[0])
    
    # l = 0
    if l == 0 and m == 0 and n == 0:
        res = np.repeat(0.0 + 0.0j,q.shape[0])
        
    # l = 1
    elif l == 1:
        if m == -1:
            if n == -1: res = ap * ap
            elif n == 0: res = s2 * ap * b
            elif n == 1: res = b * b
        elif m == 0:
            if n == -1: res = -s2 * ap * bp
            elif n == 0: res = a * ap - b * bp
            elif n == 1: res = s2 * a * b
        elif m == 1:
            if n == -1: res = bp * bp
            elif n == 0: res = -s2 * a * bp
            elif n == 1: res = a * a
            
    # l = 2
    elif l == 2:
        if m == -2:
            if n == -2: res = ap**4
            elif n == -1: res = 2.0 * b * ap**3
            elif n == 0: res = s6 * ap**2 * b**2
            elif n == 1: res = 2.0 * ap * b**3
            elif n == 2: res = b**4
        elif m == -1:
            if n == -2: res = -2.0 * ap**3 * bp
            elif n == -1: res = ap**3 * a - 3.0 * ap**2 * b * bp
            elif n == 0: res = s6 * ap**2 * a * b - s6 * ap * b**2 * bp
            elif n == 1: res = 3.0 * a * ap * b**2 - b**3 * bp
            elif n == 2: res = 2.0 * a * b**3
        elif m == 0:
            if n == -2: res = s6 * ap**2 * bp**2
            elif n == -1: res = -s6 * ap**2 * a * bp + s6 * ap * b * bp**2
            elif n == 0: res = a**2 * ap**2 - 4.0 * a * ap * b * bp + b**2 * bp**2
            elif n == 1: res = s6 * ap * a**2 * b - s6 * a * b**2 * bp
            elif n == 2: res = s6 * a**2 * b**2
        elif m == 1:
            if n == -2: res = -2.0 * ap * bp**3
            elif n == -1: res = 3.0 * a * ap * bp**2 - b * bp**3
            elif n == 0: res = -s6 * ap * a**2 * bp + s6 * a * b * bp**2
            elif n == 1: res = ap * a**3 - 3.0 * a**2 * b * bp
            elif n == 2: res = 2.0 * a**3 * b
        elif m == 2:
            if n == -2: res = bp**4
            elif n == -1: res = -2.0 * a * bp**3
            elif n == 0: res = s6 * a**2 * bp**2
            elif n == 1: res = -2.0 * a**3 * bp
            elif n == 2: res = a**4

    return res


def run_sim(T,m,E,D):
    subprocess.run(["./main.out","T",str(T),"m",*map(str,m),"E",*map(str,E),"D",*map(str,D),"-o","pos"],
                   stdout=open(f"out/quat_T={T}_m={m}_E={E}_D={D}.dat"
                               ,'w+'))
def calculate_wigner_cor(quat,D):
    for (l,m,n) in ((l,m,n) for l in range(2) for m in range(-l,l+1) for n in range(-l,l+1)):
        wigner = wigner_d_from_quaternion(l,m,n,quat)
        cor = scp.signal.correlate(wigner,wigner,mode="full")
        cor /= np.max(cor)
        np.savetxt(open(
            f"out/cor_{D}_({l}_{m}_{n}).dat",'w+')
            ,cor,delimiter=" ")
        make_plot(D,l,m,n)
def run_sims(T,m,E,D):
    for i in np.arange(np.size(T)):
        run_sim(T[i],m[i],E[i],D[i])
        quat = np.loadtxt(f"out/quat_T={T[i]}_m={m[i]}_E={E[i]}_D={D[i]}.dat",delimiter=" ")
        calculate_wigner_cor(quat,D[i])

def make_plot(D,l,m,n):
    cor =np.loadtxt(f"out/cor_{D}_({l}_{m}_{n}).dat",dtype=np.complex128)
    plt.clf()
    plt.plot(cor)
    plt.plot(np.imag(cor))
    plt.title(f"D={D} l={l} m={m} n={n}")
    plt.savefig(f"plots/cor_{D}_({l}_{m}_{n}).png")

N = 10
T = np.repeat(300,N)
m = np.repeat([[0,0,0.1]],N,0)
E = np.repeat([[0,0,0]],N,0)
D = np.arange(1,N+1)[:,None]*np.repeat([[1,1,1]],N,0)
run_sims(T,m,E,D)