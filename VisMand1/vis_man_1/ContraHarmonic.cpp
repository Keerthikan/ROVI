#include "ContraHarmonic.h"

void ContraHarmonic(Mat src, Mat dst, int kernel, double P)
{
  cout << "got it" << endl;
    Mat temp = src.clone();
    Mat dst111 = src.clone();
    copyMakeBorder(temp,temp,kernel-1,kernel-1,kernel-1,kernel-1,BORDER_CONSTANT,Scalar(0,0,0));

    for(int row = kernel/2; row < temp.rows - kernel/2-1; row++)
    {
        for(int col = kernel/2; col < temp.cols - kernel/2-1; col++)
        {

        double den=0,num=0,value=0;
          for(int i = -(kernel/2); i <= (kernel/2) ; i++)
          {
            for(int j = -(kernel/2) ; j <= (kernel/2); j++)
            {
                den += pow(temp.at<uchar>(row+i,col+j),P);
                num += pow(temp.at<uchar>(row+i,col+j),P+1);
            }
          }

        value = num/den;
        dst.at<uchar>(row,col) = value;
      }
    }
    cout << "ada" << endl;
    dst.convertTo(dst,CV_8U);
    cout << "done " << endl;
}
