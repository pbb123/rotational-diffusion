#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "Quaternion.h"
#include "Molecule.h"

void sim(double kT, double D[3],long int Tmax, double m0_norm);

double random_double()
{
    return (double) rand()/RAND_MAX;
}

int main()
{
    double T = 293.15; // K = 20 oC
    double k = 1.380649; // 10**-23 J/K
    double kT = k*T; // [kT] = 10**-23 J

    double m0_norm = 15; // 10^-30 C*m

    long int Tmax = 50000; // number of time steps -- each 0.001 ns long

    double D[3] = {1,1,1}; //Diffusion tensor (in diagonal form) [D] = ns^-1
    for (int n=0; n<800; n++)
    {
        sim(kT,D,Tmax,m0_norm);
    } 
    return 0; 
}


/*TODO:
Jednostki:
m -Debye (~10**(-30) C * m)
E - V/m ()
T - kelwiny -- pokojowa

D - rad^2/s (10**-5 - 10**-9) (ns)
dt ~ ns -> dtheta << 1 rad

dtheta = dt * D

0.001 = 0.001 ns * 1/ns

dt = 0.001 ns

U ~ V/m * C*m * 10**-30 ~ 10**-30 J 
U/kT - bezwymiarowe

Obsługa programu:
-opcje wywołania 

Output:
-
*/
 