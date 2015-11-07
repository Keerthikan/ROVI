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

        double den=0,num=0;
          for(int i = -(kernel/2); i <= (kernel/2) ; i++)
          {
            for(int j = -(kernel/2) ; j <= (kernel/2); j++)
            {
                den += pow(temp.at<double>(row+i,col+j),P);
                num += pow(temp.at<double>(row+i,col+j),P+1);
                //cout <<"Row: "<<row+i << " " << "col: "<< col + j << endl;
            }
          }

        //cout << num/den << endl;
        double value = num/den;
        if (isnan(value))
        {
          cout << num << " " << den << endl;

          if(isinf(num) && isinf(den))
          {
            dst.at<double>(row,col) = 1;
          }

          else if (isinf(num))
          {
            dst.at<double>(row,col) = den;
          }
          else if (isinf(den))
          {
            dst.at<double>(row,col) = num;
          }

        }
        else
        {
          //cout << "was not nan" << endl;
          dst.at<double>(row,col) = value;
        }
      //  namedWindow("ad",WINDOW_NORMAL);
      //  imshow("ad",dst);
      }
    }
    cout << "ada" << endl;
    dst.convertTo(dst111,CV_8U);
    namedWindow("hey",WINDOW_NORMAL);
    imshow("hey",dst111);
    cout << "done " << endl;
    waitKey();
}
