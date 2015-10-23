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

using namespace std;
using namespace cv;


int main() {
    string path = "img1/";
    string img = path+"src.png";

    hist(img,path,"Hist.png");
    cout << "Hist done: " << path+img << endl;
    namedWindow("final",WINDOW_NORMAL);
    Mat dst;
    Mat src = imread(img,CV_LOAD_IMAGE_GRAYSCALE);
    medianBlur(src, dst, 1);
//    imshow("dst",dst);
    imshow("hist",calcHistogram(dst));
    waitKey(0);
    return 0;
}
