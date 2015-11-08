#include "constras_stretching.h"

void constrast_stretching(Mat src, Mat dst)
{
  double q = 0;
  if (src.depth() == 0)
  {
    cout << "8 bit - unsigned" << endl;
    q = 8;
  }
  double mp = pow(2,q)-1;
  double min = 0;
  double max = 0;
  minMaxLoc(src,&min,&max);
  double r = max-min;
  for (int row = 0; row < src.rows; row++) {
    for (int col = 0; col < src.cols; col++) {
      dst.at<uchar>(row,col) = round(((src.at<uchar>(row,col)-min)/r)*mp);
    }
  }

}
