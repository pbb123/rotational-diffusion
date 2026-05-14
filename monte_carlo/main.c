#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "Quaternion.h"
#include "Molecule.h"

void sim(double kT, double D[3], double electric_field[3], double dipole_moment[3], long int Tmax);

double random_double()
{
    return (double) rand()/RAND_MAX;
}


int main(int argc, char* argv[])
{
    srand(time(NULL));

    double T = 293.15; // K = 20 oC
    double k = 1.380649; // 10**-23 J/K
    double kT = k*T; // [kT] = 10**-23 J

    long int Tmax = 50000; // number of time steps -- each 0.001 ns long

    double D[3] = {1,1,1}; //Diffusion tensor (in diagonal form) [D] = ns^-1

    double E[3] = {0,0,10}; // electric field [E] = V/nm = GV/m

    double m[3] = {15,15,15}; // electric dipole moment [m] = 10^-30 m*C

    int K = 1; //number of simulations

    //parse(argc,argv);

    for (int n=0; n<K; n++)
    {
        sim(kT,D,E,m,Tmax);
    } 
    return 0; 
}


/*TODO:
Obsługa programu:
-opcje wywołania 
-rozkład kąta między m, a E -- czy nie zależy od kroku czasowego dt
-funkcja korelacji:
    C(\tau) = <m \cdot m(t-\tau)> -- średnia po t -- niezależne od kroku czasowego?
*/
