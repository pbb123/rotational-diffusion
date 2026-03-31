typedef struct
{
    long double a;
    long double b;
    long double c;
    long double d;
}Quaternion;

void qadd(Quaternion q1,Quaternion q2,Quaternion *result);

void qsub(Quaternion q1,Quaternion q2,Quaternion *result);

void qmultiply(Quaternion q1,Quaternion q2,Quaternion *result);

void qconjugate(Quaternion q, Quaternion* result);

void qprint(Quaternion q);

long double qdot(Quaternion q1,Quaternion q2);

void rotate(Quaternion rotation, Quaternion vector, Quaternion* result);

void qnormalize(Quaternion* q);

void minusq(Quaternion q, Quaternion* result);