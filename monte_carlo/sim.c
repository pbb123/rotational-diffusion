#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "Quaternion.h"
#include "Particle.h"

double random_double();

double dtheta = 0.001;

Quaternion E = {0,0,0,1};
Quaternion m0 = {0,0,1,0};

void init(double kT, double D[3],int Tmax, Particle* particle)
{
    srand(time(NULL));

    Quaternion rotx = {cos(dtheta/2),sin(dtheta/2),0,0};
    Quaternion roty = {cos(dtheta/2),0,sin(dtheta/2),0};
    Quaternion rotz = {cos(dtheta/2),0,0,sin(dtheta/2)};

    qnormalize(&m0);
    Quaternion m = m0;
    Quaternion new_m = {0,0,0,0};
    Quaternion position = {1,0,0,0}; //Initial position
    Quaternion current_rotation={1,0,0,0};

    Particle p = {D[0],D[1],D[2],position,m,new_m,rotx,roty,rotz,current_rotation};
    *particle =p;
}

void step(Particle* particle, double kT)
{
    random_rotation(particle); //Choose a random rotation direction
    
    calculate_new_m(particle);
    double delta_U = calculate_energy_difference(particle,E); //Calculate energy difference

    double r = random_double();
    if (delta_U<0 || ((delta_U>=0) && r<exp(-delta_U/kT)))
    { 
        rotate_particle(particle);
    }
}

void sim(double kT, double D[3],int Tmax)
{
    Particle particle;
    double dt = dtheta/pow(10,-9);

    init(kT,D,Tmax,&particle);

    printf("%f\n",kT); //Parameters output
    printf("%f\n",dt);

    for (int t=0; t<=Tmax; t++)
    {
        step(&particle,kT);
        printf("%LF\n",-qdot(particle.m,E));
        printf("%Lf\n",qdot(particle.m,m0)); //Generate output
    }
}