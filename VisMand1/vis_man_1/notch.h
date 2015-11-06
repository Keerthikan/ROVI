#ifndef NOTCH_H
#define NOTCH_H
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;
cv::Mat notch(double d0, double n, int wy, int wx, int cx, int cy);

#endif // NOTCH_H
