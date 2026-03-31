#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "Quaternion.h"
#include "Molecule.h"

double random_double();

double dtheta = 0.001;

Quaternion E = {0,0,0,0}; /* V/nm =  GV/m */
Quaternion m0 = {0,-8.4783536*0.108425,8.4783536*0.160436,8.4783536*0.803881}; // 10**-30 C*m

void init(double kT, double D[3],long int Tmax, double m0_norm, Molecule* molecule)
{
    srand(time(NULL));

    m0.c = m0_norm;

    Quaternion rotx = {cos(dtheta/2),sin(dtheta/2),0,0};
    Quaternion roty = {cos(dtheta/2),0,sin(dtheta/2),0};
    Quaternion rotz = {cos(dtheta/2),0,0,sin(dtheta/2)};

    qnormalize(&m0);
    Quaternion m = m0;
    Quaternion new_m = {0,0,0,0};
    Quaternion position = {1,0,0,0}; //Initial position
    Quaternion current_rotation={1,0,0,0};

    Quaternion ex={0,1,0,0};
    Quaternion ey={0,0,1,0};
    Quaternion ez={0,0,0,1};

    Molecule p = {D[0],D[1],D[2],position,m,new_m,rotx,roty,rotz,current_rotation,ex,ey,ez};
    *molecule =p;
}

void step(Molecule* molecule, double kT)
{
    random_rotation(molecule); //Choose a random rotation direction
    
    calculate_new_m(molecule);
    double delta_U = calculate_energy_difference(molecule,E); //Calculate energy difference

    double r = random_double();

    if (delta_U<=0 || ((delta_U>=0) && r<exp(-delta_U/kT)))
    { 
        rotate_molecule(molecule);
    }
}

void sim(double kT /*10**-23 J*/, double D[3] /*ns^-1*/, long int Tmax /*ps*/, double m0_norm /*C*m*10^-30*/)
{
    Molecule molecule;
    double dt = dtheta; // ns

    init(kT,D,Tmax,m0_norm,&molecule);

    //printf("%f\n",kT); //Parameters output
    //printf("%f\n",dt);

    int N = (int) (molecule.D[0] + molecule.D[1] + molecule.D[2]); // Number of rotations per time step

    for (int t=0; t<=Tmax; t++)
    {
        for(int i=0; i<N; i++)
        {
            step(&molecule,kT);
        }
        //printf("%LF\n",-qdot(molecule.m,E)); //Generate output
        //qprint(molecule.ez);
        //printf("%Lf\n",molecule.ex.d);
        //printf("%Lf\n",molecule.ey.d);
        //printf("%Lf\n",molecule.ey.d);
        //printf("%Lf\n",qdot(molecule.m,m0)); 
        //qprint(molecule.position);
        //printf("%Lf\n",molecule.position.d);
        //printf("%d\n",t);
    }

    printf("%Lf\n",molecule.ex.d);
}

