#ifndef EQUALIZATION_H
#define EQUALIZATION_H
#include <string>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace std;
using namespace cv;

void eql(const std::string& filename, const std::string& path, const std::string& saveas);

#endif // EQUALIZATION_H
