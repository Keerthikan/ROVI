#ifndef CONTRAHARMONIC_H
#define CONTRAHARMONIC_H
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;

void ContraHarmonic(Mat src,Mat dst,  int kernel, double P);



#endif // CONTRAHARMONIC_H
