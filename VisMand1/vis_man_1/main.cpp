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
#include "fourier.h"
#include "notch.h"

#define RECT_POS_X 1075
#define RECT_POS_Y 1400
#define RECT_SIZE  200

using namespace std;
using namespace cv;


Mat crop_rect(Mat original)
{
	Rect ROI = Rect(RECT_POS_X,RECT_POS_Y,RECT_SIZE,RECT_SIZE);
	cout << "csdc" << endl;
	Mat crop  = original(ROI);
	return crop;
}

cv::Mat intensityIncrease(const cv::Mat &img, int amount, bool saturateCast=false){
    cv::Mat imgCopy = img.clone();
	int r = imgCopy.rows;
	int c = imgCopy.cols;

    // for all pixels
    for (int i=0; i<r; i++)
	{
        uchar* data= imgCopy.ptr<uchar>(i); // pointer to first column of row i
        for (int j=0; j<c; j++){
            if(saturateCast) {
                data[j] = cv::saturate_cast<uchar>(data[j] + amount);
            }else {
                data[j] = data[j] + amount;
            }
        }
	}
	return imgCopy;
}

int main()
{
    string lena = "/home/student/Desktop/lena_face.bmp";
    string original = "/home/student/ROVI/VisMand1/build-vis_man_1-Desktop-Debug/img/ImageOrig.png";
    string img1 = "/home/student/ROVI/VisMand1/build-vis_man_1-Desktop-Debug/img/Image1.png";
    string img2 = "/home/student/ROVI/VisMand1/build-vis_man_1-Desktop-Debug/img/Image4_1.png";

    //namedWindow("final",WINDOW_NORMAL);
		namedWindow("das",WINDOW_NORMAL);
    //namedWindow("init",WINDOW_NORMAL);
    //namedWindow("Original", WINDOW_NORMAL);

    Mat orig = imread(original,CV_LOAD_IMAGE_GRAYSCALE);
    Mat src = imread(lena,CV_LOAD_IMAGE_GRAYSCALE);
		Mat src_crop;
		Mat orig_crop;
    Mat dst = src.clone();
    Mat_<float> src4_2 = imread(img2, CV_LOAD_IMAGE_GRAYSCALE);
		Mat_<float> output;
    //---------------------------------------------------------------//
		cout << src.type() << endl;
		if (src.type() == CV_8U)
		{
			std::cout << "YEAH" << std::endl;
		}
		//imshow("crop",	crop_rect(orig));
		//SNR(crop_rect(orig),crop_rect(src));
    //GaussianBlur( dst, dst, Size( 3, 3 ), 0, 0 );
    //eql(dst,dst);
    //blur(dst,dst,Size(5,5));
   	//equalizeHist( dst, dst );
		//intensityIncrease(dst,);
		//imshow("das", dst);
  	//medianBlur(dst,dst,-111);

    //bilateralFilter ( dst, dst, 15, 80, 80 );
    //blur(dst,dst,Size(11,11));
    //mean(dst,dst);
    //ContraHarmonic(src,dst,3,2);
    //cout << "converted" << endl;
    //imshow("init", src);
    //imshow("final", src_crop);
    //imshow("Original",orig_crop);
    // calcHistogram(dst);

    //-------------------------------------------------------------//

    //fft2(src4_2);
		//applyFilter(src4_2, output);
		run(img2,true);
		//imshow("das", output);
		//imshow("src", src);
		//imshow("Original",orig);
    //run(img2,0);
    //waitKey(0);
    return 0;
}
