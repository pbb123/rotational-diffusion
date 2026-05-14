#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "Quaternion.h"
#include "Molecule.h"
#include "main.h"

void sim(double kT, double D[3], double electric_field[3], double dipole_moment[3], long int Tmax, output_mode out_mode);

double random_double()
{
    return (double) rand()/RAND_MAX;
}

output_mode parse_input(int argc, char* argv[], double* T, long int* Tmax, double (*D)[], double (*E)[], double (*m)[])
{
    int args_left = argc-1;
    output_mode mode = None;
    while (args_left>0)
    {
        char* argument = argv[argc-args_left];
        if (!strcmp(argument,"T"))
        {
            if (args_left>=1)
            {
                args_left--;
                *T = atof(argv[argc-args_left]);
            }
        }
        else if (!strcmp(argument,"Tmax"))
        {
            if (args_left>=1)
            {
                args_left--;
                *Tmax = atoll(argv[argc-args_left]);
            }
        }
        else if (!strcmp(argument,"D"))
        {
            if (args_left>=3)
            {
                args_left--;
                (*D)[0] = atof(argv[argc-args_left]);
                args_left--;
                (*D)[1] = atof(argv[argc-args_left]);
                args_left--;
                (*D)[2] = atof(argv[argc-args_left]);
            }            
        }
        else if (!strcmp(argument,"E"))
        {
            if (args_left>=3)
            {
                args_left--;
                (*E)[0] = atof(argv[argc-args_left]);
                args_left--;
                (*E)[1] = atof(argv[argc-args_left]);
                args_left--;
                (*E)[2] = atof(argv[argc-args_left]);
            }  
        }
        else if (!strcmp(argument,"m"))
        {
            if (args_left>=3)
            {
                args_left--;
                (*m)[0] = atof(argv[argc-args_left]);
                args_left--;
                (*m)[1] = atof(argv[argc-args_left]);
                args_left--;
                (*m)[2] = atof(argv[argc-args_left]);
            }             
        }
        else if (!strcmp(argument,"-o"))
        {
            if (args_left>=1)
            {
                args_left--;
                if(!strcmp(argv[argc-args_left],"pos"))
                {
                    mode = Position;
                }
                if(!strcmp(argv[argc-args_left],"angle"))
                {
                    mode = Angle;
                }
                if(!strcmp(argv[argc-args_left],"m"))
                {
                    mode = M;
                }
            }           
        }
        args_left--;
    }
    return mode;
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

    int Nsim = 1; //number of simulations


    output_mode out_mode = parse_input(argc,argv,&T,&Tmax,&D,&E,&m);

    printf("T=%lfK\n",T);
    printf("Tmax=%ld\n",Tmax);
    printf("D=[%lf,%lf,%lf] ns^-1\n",D[0],D[1],D[2]);
    printf("E=[%lf,%lf,%lf] GV/m\n",E[0],E[1],E[2]);
    printf("m=[%lf,%lf,%lf] 10^-30 m*C\n",m[0],m[1],m[2]);

    for (int n=0; n<Nsim; n++)
    {
        sim(kT,D,E,m,Tmax,out_mode);
    } 
    return 0; 
}


/*TODO:tau
Obsługa programu:
-opcje wywołania V
-rozkład kąta między m, a E -- czy nie zależy od kroku czasowego dt
-funkcja korelacji:
    C(\tau) = <m \cdot m(t-\tau)> -- średnia po t -- niezależne od kroku czasowego?
*/
