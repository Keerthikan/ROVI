#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <math.h>
#include "opencv2/nonfree/nonfree.hpp"
#include "histogram.h"
#include "equalization.h"
#include "calchistogram.h"
#include "ContraHarmonic.h"

using namespace std;
using namespace cv;

int main() {
    string path = "img1/";
    string img = path+"src.png";
    namedWindow("final",WINDOW_NORMAL);
    //namedWindow("init",WINDOW_NORMAL);
    Mat dst;
    Mat src = imread(img,CV_LOAD_IMAGE_GRAYSCALE);

    dst = ContraHarmonic(src,10,0.000000000000000001);
    imshow("final", dst);
    waitKey(0);
    return 0;
}
