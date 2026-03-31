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

    Quaternion ex;
    Quaternion ey;
    Quaternion ez;

}
Molecule;

void random_rotation(Molecule* p);
void rotate_molecule(Molecule* p);
void calculate_new_m(Molecule* p);
double calculate_energy_difference(Molecule* p, Quaternion E);