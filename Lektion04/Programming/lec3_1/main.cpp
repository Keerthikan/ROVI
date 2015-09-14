#include <iostream>
#include <math.h>       /* sin & cos*/

double ** rotation(double x,double y,double z,bool fixed)
{
    double** euler = new double*[3];

    for (int i = 0; i < 3; ++i)
    {
       euler[i] = new double[3];
    }

    if(!fixed){
        euler[1][1] = cos(y)*cos(z);
        euler[1][2] = sin(x)*sin(y)*cos(z)-cos(x)*sin(z);
        euler[1][3] = cos(x)*sin(y)*cos(z)-sin(x)*sin(z);

        euler[2][1] = cos(y)*sin(z);
        euler[2][2] = sin(x)*sin(y)*sin(z)+cos(x)*cos(z);
        euler[2][3] = cos(x)*sin(y)*sin(z)-sin(x)*cos(z);

        euler[3][1] = -sin(y);
        euler[3][2] = sin(x)*cos(y);
        euler[3][3] = cos(x)*cos(y);
    }else{
        std::cout << "Lars will come back with nizzel shiiit\n";
    }

    return euler;
}

int main()
{
    std::cout << "Hello Kiddi !" << std::endl;
    double pi = 3.14;

    double **tmp = rotation(pi,pi,pi,0);

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            std::cout << tmp[i][j] << "\t";
            std::cout << "Mogens\n";
        }
        std::cout << std::endl;
    }

    return 0;
}

