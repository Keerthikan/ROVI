//============================================================================
// Name        : ROVI01.cpp
// Author      : Keerthikan R
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <math.h>
#include "opencv2/nonfree/nonfree.hpp"
using namespace std;
using namespace cv;


int main() {

    Mat image_full = imread("lena(1).bmp",CV_LOAD_IMAGE_GRAYSCALE);
    Mat image_face = imread("lena_face.bmp",CV_LOAD_IMAGE_GRAYSCALE);
    Mat image_hair = imread("lena_hair.bmp",CV_LOAD_IMAGE_GRAYSCALE);
    Mat image_hat = imread("lena_hat.bmp",CV_LOAD_IMAGE_GRAYSCALE);

    if(image_full.data < 0 && image_face.data < 0  && image_hair.data < 0 && image_hat.data < 0)
    {
        cout << "Not loaded" << endl;
        exit(0);
    }
    imshow("image_full",image_full);
    imshow("image_face",image_face);
    imshow("image_hair",image_hair);
    imshow("image_hat",image_hat);
    waitKey(0);
    destroyAllWindows();
    //---------------------------------------------------//
    // Pad the image with borders to avoid wrap around errors using copyMakeBorders()
    int m = getOptimalDFTSize(2*image_full.rows);
    int n = getOptimalDFTSize(2*image_full.cols);
    copyMakeBorder(image_full, image_full,  0 , 0 ,0, n/2 , BORDER_CONSTANT, Scalar::all(0));
    imshow("image_full",image_full);
    waitKey(0);
    // I think it is done
    //---------------------------------------------------//
    // Copy the gray image into the first channel of a new 2-channel image of type Mat_<Vec2f>,
    // e.g. using merge(). The second channel should be all zeros.


    return 0;
}
