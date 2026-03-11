typedef struct
{
    double a;
    double b;
    double c;
    double d;
}Quaternion;

void qadd(Quaternion q1,Quaternion q2,Quaternion *result);

void qmultiply(Quaternion q1,Quaternion q2,Quaternion *result);

void qconjugate(Quaternion q, Quaternion* result);

void qprint(Quaternion q);