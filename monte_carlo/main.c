#include <stdio.h>
#include <math.h>
#include "Quaternion.h"

int main()
{
    Quaternion q = {0,0,1,0};
    Quaternion v = {0,1,0,0};
    Quaternion q2;
    rotate(q,v,&q2);
    qprint(q2);

    return 0;

}
