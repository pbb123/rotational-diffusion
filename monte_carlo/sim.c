#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "Quaternion.h"
#include "Molecule.h"
#include "main.h"

double random_double();

double dtheta = 0.001;

Quaternion E;
Quaternion m0; 


void init(double kT, double D[3], double electric_field[3] /*GV/m*/,  double dipole_moment[3] /*10^-30 C*m */, Molecule* molecule)
{
    m0.a = 0;
    m0.b = dipole_moment[0];
    m0.c = dipole_moment[1];
    m0.d = dipole_moment[2];

    E.a = 0;
    E.b = electric_field[0]; 
    E.c = electric_field[1];
    E.d = electric_field[2];

    Quaternion rotx = {cos(dtheta/2),sin(dtheta/2),0,0};
    Quaternion roty = {cos(dtheta/2),0,sin(dtheta/2),0};
    Quaternion rotz = {cos(dtheta/2),0,0,sin(dtheta/2)};

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

void generate_output(output_mode mode, Molecule* molecule)
{
    switch (mode)
    {
    case Position:
        qprint(molecule->position);
        break;
    case Angle:
        printf("%lf",acos(qdot(E,molecule->m)/qnorm(E)/qnorm(molecule->m)));    
        break;
    case Corelation:
        printf("TODO: corelation calculation");
    default:
        break;
    }
}

void step(Molecule* molecule, double kT, output_mode out_mode)
{
    random_rotation(molecule); //Choose a random rotation direction
    
    calculate_new_m(molecule);
    long double delta_U = calculate_energy_difference(molecule,E); //Calculate energy difference

    double r = random_double();

    double p = fmin(1, exp(-delta_U/kT));
    if (r < p)
    { 
        rotate_molecule(molecule);
    }
    generate_output(out_mode,molecule);
    qprint(molecule->position);

}

void sim(double kT /*10**-23 J*/, double D[3] /*ns^-1*/, double electric_field[3] /*GV/m*/,  double dipole_moment[3] /*10^-30 C*m */, long int Tmax /*ps*/, output_mode out_mode)
{
    Molecule molecule;
    double dt = dtheta; // ns

    init(kT,D,electric_field,dipole_moment,&molecule);

    int N = (int) (molecule.D[0] + molecule.D[1] + molecule.D[2]); // Number of rotations per time step

    for (int t=0; t<=Tmax; t++)
    {
        for(int i=0; i<N; i++)
        {
            step(&molecule,kT,out_mode);
        }
    }
}

