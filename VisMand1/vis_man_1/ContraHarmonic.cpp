#include "ContraHarmonic.h"

Mat ContraHarmonic(Mat src, int kernel, double P)
{
    Mat Num = Mat(src.rows,src.cols,CV_8U,Scalar(1,1,1));
    Mat Den = Mat(src.rows,src.cols,CV_8U,Scalar(1,1,1));
    for(int i = 0; i < src.rows; i++)
    {
        for(int j = 0; j < src.cols; j++)
        {
            Num.at<uchar>(i,j) = pow(src.at<uchar>(i,j),P+1);
            Den.at<uchar> (i,j) = pow(src.at<uchar>(i,j),P);
        }
    }

    Mat Appliedkernel = Mat(kernel,kernel,CV_8U,Scalar(1,1,1));
    filter2D(Num,Num, src.depth(), Appliedkernel);
    filter2D(Den,Den, src.depth(), Appliedkernel);

    Mat output = Num/Den;


    return output;
}

