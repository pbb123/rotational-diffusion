#include <stdio.h>
#include <math.h>

#include "Quaternion.h"
#include "Molecule.h"

extern double random_double();

void random_rotation(Molecule* p)
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
    s = random_double();
    
    if (s<0.5)
    {
        qconjugate(p->current_rotation,&(p->current_rotation));
    }
}

void rotate_molecule(Molecule* p)
{
    qmultiply(p->current_rotation,p->position,&(p->position)); // Update position by choosen rotation

    rotate(p->current_rotation,p->rotx,&(p->rotx)); // Update axis of rotation
    rotate(p->current_rotation,p->roty,&(p->roty));
    rotate(p->current_rotation,p->rotz,&(p->rotz));

    rotate(p->current_rotation,p->ex,&(p->ex)); // Update inner coordinates
    rotate(p->current_rotation,p->ey,&(p->ey));
    rotate(p->current_rotation,p->ez,&(p->ez));

    qnormalize(&(p->rotx)); // Normalize for numerical stability
    qnormalize(&(p->roty));   
    qnormalize(&(p->rotz));

    qnormalize(&(p->ex));
    qnormalize(&(p->ey));
    qnormalize(&(p->ez));

    p->m=p->new_m; //Update dipole moment
}

void calculate_new_m(Molecule* p)
{
    Quaternion new_m; //Calculate new dipole moment
    rotate(p->current_rotation,p->m,&(p->new_m));
}

long double calculate_energy_difference(Molecule* p, Quaternion E)
{
    Quaternion delta_m;
    qsub(p->new_m,p->m,&delta_m);
    return -qdot(delta_m,E)/100; // J * 10^-30 * 10^9 *10^-2 = 10^-23 J -- it divides nicely with kT
}


/*
*/