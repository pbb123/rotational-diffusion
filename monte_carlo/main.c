#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "Quaternion.h"
#include "Particle.h"

void sim(double kT, double D[3],int Tmax);

double random_double()
{
    return (double) rand()/RAND_MAX;
}

int main()
{
    double kT = pow(10,-5); // [kT] = J
    int Tmax = 50000; // []
    double D[3] = {1,1,1}; //Diffusion tensor (in diagonal form) [D] = ns^-1

    sim(kT,D,Tmax); 
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

0.001 = 1 ps * 1/ns

dt = 1 ps

U ~ V/m * C*m * 10**-30 ~ 10**-30 J 
U/kT - bezwymiarowe

Obsługa programu:
-opcje wywołania

Output:
-
*/
 