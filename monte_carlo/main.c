#include <stdio.h>
#include <math.h>
#include "Quaternion.h"

int main()
{
    Quaternion q1 = {0,0,1,0};
    Quaternion q2 = {0,1,0,0};
    Quaternion q3;
    qmultiply(q1,q2,&q3);
    qprint(q3);

}
