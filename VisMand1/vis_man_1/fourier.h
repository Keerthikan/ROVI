#ifndef FOURIER_H
#define FOURIER_H
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

//void fft(Mat_<float> src);
void fft2(Mat_<float> src);
void applyFilter(Mat_<float> src, Mat_<float> output);
void run(const std::string& filename, bool highpass);


#endif // FOURIER_H
