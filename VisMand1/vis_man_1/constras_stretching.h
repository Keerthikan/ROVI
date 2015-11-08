#ifndef CONSTRAS_STRETCHING_H
#define CONSTRAS_STRETCHING_H
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/opencv.hpp"
#include <math.h>
using namespace cv;
using namespace std;

void constrast_stretching(Mat src, Mat dst);

#endif // CONSTRAS_STRETCHING_H
