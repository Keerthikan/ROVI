#include <iostream>
#include <math.h>       /* sin & cos*/
#include <vector>

using namespace std; // Sorry Jes.. I had to..

double ** rotation(double z,double y,double x)
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

void conv_rotation2rpy(double R[3][3]){
    double pitch = 0, roll = 0, yaw = 0;
    if(R[2][0]==1){
        cout << "R[2][0]: " << R[2][0] << " Special sequence!!" << endl;
        pitch = asin(-R[2][0]);
        yaw = atan2(R[0][1],R[0][2]) + roll;
        roll = atan2(R[1][1],R[1][2]) + yaw;

        std::cout << roll << " " << pitch << " " << yaw << std::endl;
        std::cout << std::endl;

        double ** tmp = rotation(roll,pitch,yaw);


        for(int i = 0 ; i < 3 ;  i++){
            for(int j = 0 ; j < 3 ; j++){
                std::cout << tmp[i][j] << "  ";
            }
            std::cout << std::endl;
        }
    }else if(R[2][0] > 1){
        std::cout << "This value is out of bounce, baby!  " << R[2][0] << std::endl;
        return;
    }else{
        pitch = asin(-R[2][0]);
        yaw = atan2(R[2][1],R[2][2]);
        roll = atan2(R[1][0],R[0][0]);

        std::cout << roll << " " << pitch << " " << yaw << std::endl;
        std::cout << std::endl;

        double ** tmp = rotation(roll,pitch,yaw);


        for(int i = 0 ; i < 3 ;  i++){
            for(int j = 0 ; j < 3 ; j++){
                std::cout << tmp[i][j] << "  ";
            }
            std::cout << std::endl;
        }
    }
}

int main()
{
    double pi = 3.14;

    double test[3][3];
    std::cout << std::endl;

    for(int i = 0 ; i < 3 ; i++){
        for(int j = 0 ; j < 3 ; j++){
            test[i][j] = -1;
        }
    }

    conv_rotation2rpy(test);

    return 0;
}

