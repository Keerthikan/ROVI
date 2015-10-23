#ifndef HISTOGRAM_H
#define HISTOGRAM_H
#include <string>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace std;
using namespace cv;


void hist(const std::string& filename, const std::string& path, const std::string& saveas);

#endif // HISTOGRAM_H
