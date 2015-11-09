#include <iostream>
#include <math.h>       /* sin & cos*/
#include <vector>
#include <ctime>
#include <cstdlib>

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

double ** rotationT(double q[3])
{
    double** euler = 0;
    euler = new double*[4];
    
    for (int i = 0; i < 4; ++i)
    {
        euler[i] = new double[4];
    }
    
    euler[0][0] = cos(q[1])*cos(q[1]);
    euler[0][1] = sin(q[0])*sin(q[2])*cos(q[2])-cos(q[0])*sin(q[2]);
    euler[0][2] = cos(q[0])*sin(q[1])*cos(q[2])-sin(q[0])*sin(q[2]);
    
    euler[1][0] = cos(q[1])*sin(q[2]);
    euler[1][1] = sin(q[0])*sin(q[1])*sin(q[2])+cos(q[0])*cos(q[2]);
    euler[1][2] = cos(q[0])*sin(q[1])*sin(q[2])-sin(q[0])*cos(q[2]);
    
    euler[2][0] = -sin(q[1]);
    euler[2][1] = sin(q[0])*cos(q[1]);
    euler[2][2] = cos(q[0])*cos(q[1]);
    
    euler[3][0] = 0;
    euler[3][1] = 0;
    euler[3][2] = 0;
    euler[3][3] = 1;
    
    
    for(int j = 0 ; j<4 ; j++ ){
        for(int k = 0 ; k<4 ; k++ ){
            cout << euler[j][k] << "\t";
        }
        cout << endl;
    }
    return euler;
}

void rotation2rpy(double R[3][3]){
    double pitch = 0, roll = 0, yaw = 0;
    if(R[2][0]==1){
        cout << "R[2][0]: " << R[2][0] << " Special sequence!!" << endl;
        
        yaw = acos(R[0][0]);
        roll = acos(R[2][2]);
        
        std::cout << yaw << "   " << roll << std::endl;
        
        double tmp[3][3] = {0};
        
        tmp[0][0] = cos(roll);
        tmp[1][1] = cos(roll)*cos(yaw);
        tmp[2][2] = cos(yaw);
        
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

double ** rotationTr(double z,double y,double x)
{
    double** euler = 0;
    euler = new double*[4];
    
    for (int i = 0; i < 4; ++i)
    {
        euler[i] = new double[4];
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
    
    euler[3][0] = 0;
    euler[3][1] = 0;
    euler[3][2] = 0;
    euler[3][3] = 1;
    
    return euler;
}


double **  transformation(double q[3], vector<double>& RPY)
{
    double** result = 0;
    result = new double*[4];
    
    for (int i = 0; i < 4; ++i)
    {
        result[i] = new double[4];
    }
    
    for(int amount = 0; amount < RPY.size(); amount = amount +3){
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                // Multiply the row of A by the column of B to get the row, column of product.
                for (int inner = 0; inner < 2; inner++) {
                    result[row][col] += rotationTr(RPY.at(amount), RPY.at(amount+1), RPY.at(amount)+2)[row][inner] * rotationT(q)[inner][col];
                }
                std::cout << result[row][col] << "  ";
            }
            std::cout << "\n";
        }
    }
    return result;
}
int main()
{
    double pi = 3.14;
    /*
     double test[3][3];
     std::cout << std::endl;
     
     float random_number = 0;
     
     for(int i = 0 ; i < 3 ; i++){
     for(int j = 0 ; j < 3 ; j++){
     srand((unsigned)time(0));
     random_number = rand()%10000+1;
     
     for(int l = 0 ; l < 1000000000/2 ; l++ ){
     
     }
     
     test[i][j] = random_number/10000;
     cout << random_number << "  ";
     }
     }
     std::cout << std::endl;
     
     //test[2][0] = 1;
     
     rotation2rpy(test);
     */
    
    double testQ[3] = {1,2,3};
    
    rotationT(testQ);
    
    cout << "done" << endl;
    vector<double> RPY;
    float random_number = 0;
    
    for(int j = 0 ; j < 9 ; j++){
        srand((unsigned)time(0));
        random_number = rand()%10000+1;
        
        for(int l = 0 ; l < 1000000000/2 ; l++ ){
            
        }
        
        RPY.push_back(random_number/10000);
    }
    cout << "done" << endl;
    cout <<  RPY.size() << endl;
    
    
    return 0;
}
