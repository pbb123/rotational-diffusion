#include <stdio.h>
#include <math.h>

#include "Quaternion.h"
#include "Particle.h"

extern double random_double();

void random_rotation(Particle* p)
{    
    double s = random_double();
    
    if (s<p->D[0]/(p->D[0]+p->D[1]+p->D[2]))
    {
        p->current_rotation=p->rotx;
    }
    else if (s<(p->D[0]+p->D[1])/(p->D[0]+p->D[1]+p->D[2]))
    {
        p->current_rotation=p->roty;
    }
    else 
    {
        p->current_rotation=p->rotz;
    }
}

void rotate_particle(Particle* p)
{
    qmultiply(p->current_rotation,p->position,&(p->position)); // Update position by choosen rotation

    rotate(p->current_rotation,p->rotx,&(p->rotx)); // Update axis of rotation
    rotate(p->current_rotation,p->roty,&(p->roty));
    rotate(p->current_rotation,p->rotz,&(p->rotz));

    qnormalize(&(p->rotx)); // Normalize for numerical stability
    qnormalize(&(p->roty));   
    qnormalize(&(p->rotz));

    p->m=p->new_m; //Update dipole moment
}

void calculate_new_m(Particle* p)
{
    Quaternion new_m; //Calculate new dipole moment
    rotate(p->current_rotation,p->m,&(p->new_m));
}

double calculate_energy_difference(Particle* p, Quaternion E)
{
    Quaternion delta_m;
    qsub(p->new_m,p->m,&delta_m);
    return -qdot(delta_m,E);
}