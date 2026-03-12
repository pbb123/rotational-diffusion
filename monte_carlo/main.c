#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "Quaternion.h"
double random_double()
{
    return (double) rand()/RAND_MAX;
}
int main()
{
    srand(time(NULL));
    float dtheta = 0.001;

    Quaternion rotx = {cos(dtheta/2),sin(dtheta/2),0,0};
    Quaternion roty = {cos(dtheta/2),0,sin(dtheta/2),0};
    Quaternion rotz = {cos(dtheta/2),0,0,sin(dtheta/2)};

    Quaternion* rot[3] = {&rotx,&roty,&rotz};

    Quaternion E = {0,0,0,1};
    Quaternion m0 = {0,0,1,0};
    qnormalize(&m0);
    Quaternion m = m0;

    double D[3] = {100,1,1}; //Diffusion tensor (in diagonal form)
    double Dtrace = D[0]+D[1]+D[2];

    double kT = 0.001;

    int Tmax = 50000;

    Quaternion position = {1,0,0,0}; //Initial position 
    for (int t=0; t<=Tmax; t++)
    {
        double s = random_double();
        int n;
        if (s<D[0]/(D[0]+D[1]+D[2])) {n=0;}
        else if (s<(D[0]+D[1])/(D[0]+D[1]+D[2])) {n=1;}
        else {n=2;}
        Quaternion* current_rotation = rot[n]; //Choose a random rotation direction

        Quaternion new_m; //Calculate new dipole moment
        rotate(*current_rotation,m,&new_m);
        Quaternion delta_m;
        qsub(new_m,m,&delta_m);

        double delta_U = -qdot(delta_m,E); //Calculate energy difference
        double r = random_double();
        if (delta_U<0 || ((delta_U>=0) && r<exp(-delta_U/kT))){ 
        qmultiply(*current_rotation,position,&position); // Update position by choosen rotation

        rotate(*current_rotation,rotx,&rotx); // Update axis of rotation
        rotate(*current_rotation,roty,&roty);
        rotate(*current_rotation,rotz,&rotz);

        qnormalize(&rotx); // Normalize for numerical stability
        qnormalize(&roty);   
        qnormalize(&rotz);

        m=new_m; //Update dipole moment
        }
        //printf("%LF\n",-qdot(m,E));
        printf("%Lf\n",qdot(m,m0)); //Generate output
    }
    return 0;
    
}
