typedef struct 
{
    double D[3];

    Quaternion position;
    Quaternion m;
    Quaternion new_m;

    Quaternion rotx;
    Quaternion roty;
    Quaternion rotz;

    Quaternion current_rotation;

}
Particle;

void random_rotation(Particle* p);
void rotate_particle(Particle* p);
void calculate_new_m(Particle* p);
double calculate_energy_difference(Particle* p, Quaternion E);