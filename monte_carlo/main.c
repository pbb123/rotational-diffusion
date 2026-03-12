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
    Quaternion m0 = {0,random_double(),random_double(),random_double()};
    Quaternion m =m0;

    double Dx=1;
    double Dy=1;
    double Dz=1;

    double kT = 1;

    int Tmax = 50000;

    Quaternion possition = {1,0,0,0};
    for (int t=0; t<=Tmax; t++)
    {
        Quaternion* current_rotation = rot[rand()%3]; //Choose a random rotation direction

        Quaternion new_m; //Calculate new dipole moment
        rotate(*current_rotation,m,&new_m);
        Quaternion delta_m;
        qsub(new_m,m,&delta_m);

        double delta_U = -qdot(delta_m,E); //Calculate energy difference
        double r = random_double();
        if (delta_U<0 || ((delta_U>=0) && r<exp(-delta_U/kT))){ 
        qmultiply(*current_rotation,possition,&possition); // Update possition by choosen rotation

        rotate(*current_rotation,rotx,&rotx); // Update axes of rotatation
        rotate(*current_rotation,roty,&roty);
        rotate(*current_rotation,rotz,&rotz);

        normalize(&rotx); // Normalize for numerical stability
        normalize(&roty);   
        normalize(&rotz);

        m=new_m; //Update dipole moment
        }
        printf("%LF\n",qdot(m,m0)); //Generate output
    }
    
    return 0;

}
