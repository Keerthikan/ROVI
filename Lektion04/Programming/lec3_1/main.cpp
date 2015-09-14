#include <iostream>
#include <math.h>       /* sin & cos*/
#include <vector>

double ** rotation(double x,double y,double z)
{
    double** euler = 0;
    euler = new double*[3];

    for (int i = 0; i < 3; ++i)
    {
        euler[i] = new double[3];
    }

    euler[0][0] = cos(y)*cos(z);
    euler[0][1] = sin(x)*sin(y)*cos(z)-cos(x)*sin(z);
    euler[0][2] = cos(x)*sin(y)*cos(z)-sin(x)*sin(z);

    euler[1][0] = cos(y)*sin(z);
    euler[1][1] = sin(x)*sin(y)*sin(z)+cos(x)*cos(z);
    euler[1][2] = cos(x)*sin(y)*sin(z)-sin(x)*cos(z);

    euler[2][0] = -sin(y);
    euler[2][1] = sin(x)*cos(y);
    euler[2][2] = cos(x)*cos(y);

    return euler;
}


int main()
{
    std::cout << "Hello Kiddi !\n\n";

    double pi = 3.14;

    double **tmp = rotation(pi,pi,pi);

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            std::cout << tmp[i][j] << "\t";
        }
        std::cout << std::endl;
    }

    return 0;
}

