#include "Quaternion.h"
#include <stdio.h>
void qadd(Quaternion q1,Quaternion q2,Quaternion *result)
{
    Quaternion ret = 
    {
        q1.a + q2.a,
        q1.b + q2.b,
        q1.c + q2.c,
        q1.d + q2.d
    };

    *result = ret;
}

void qmultiply(Quaternion q1,Quaternion q2,Quaternion *result)
{
    Quaternion ret = 
    {
        q1.a * q2.a - q1.b * q2.b - q1.c * q2.c - q1.d * q2.d,
        q1.a * q2.b + q1.b * q2.a + q1.c * q2.d - q1.d * q2.c,
        q1.a * q2.c - q1.b * q2.d + q1.c * q2.a + q1.d * q2.b,
        q1.a * q2.d + q1.b * q2.c - q1.c * q2.b + q1.d * q2.a
    };
    *result =ret;
}

void qconjugate(Quaternion q, Quaternion* result)
{
    Quaternion ret = 
    {
        q.a
        -q.b,
        -q.c,
        -q.d
    };
    *result = ret;
}

void qprint(Quaternion q)
{
    printf("{%f,%f,%f,%f}\n",q.a,q.b,q.c,q.d);
}