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
#include "constras_stretching.h"
#include <string>

#define RECT_POS_X 1075
#define RECT_POS_Y 1400
#define RECT_SIZE  200

using namespace std;
using namespace cv;


Mat crop_rect(Mat original)
{
	Rect ROI = Rect(RECT_POS_X,RECT_POS_Y,RECT_SIZE,RECT_SIZE);
	Mat crop  = original(ROI);
	return crop;
}


int main()
{
    string lena = "/home/student/Desktop/lena_face.bmp";
    string original = "/home/student/ROVI/VisMand1/build-vis_man_1-Desktop-Debug/img/ImageOrig.png";
    string img1 = "/home/student/ROVI/VisMand1/build-vis_man_1-Desktop-Debug/img/Image1.png";
    string img2 = "/home/student/ROVI/VisMand1/build-vis_man_1-Desktop-Debug/img/Image4_2.png";
		string img3 = "/home/student/ROVI/VisMand1/report_vis_pro1/img1/img_1_contraharmonic5_1_medianBlur_3.png";
		string outoutS = "/home/student/ROVI/VisMand1/build-vis_man_1-Desktop-Debug/output/outm.yml";

		namedWindow("das",WINDOW_NORMAL);
    //namedWindow("init",WINDOW_NORMAL);
    //namedWindow("Original", WINDOW_NORMAL);

    Mat orig = imread(original,CV_LOAD_IMAGE_GRAYSCALE);
    Mat src = imread(img1,CV_LOAD_IMAGE_GRAYSCALE);
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
		// for(int kernel = 3; kernel <= 11; kernel += 2)
		// {
		// 	for(int p = 1;  p < 10 ; p++)
		// 	{
		  	ContraHarmonic(src,dst,5,1);
		// 	cvtColor(dst,dst,CV_GRAY2BGR);
		// 	dst = increase_value(dst,30);
		// 	dst = increase_saturation(dst, 100);
		// 	cvtColor(dst,dst,CV_BGR2GRAY);
			  constrast_stretching(dst,dst);
		//		constrast_stretching(dst,dst);

		//		equalizeHist(dst,dst);
		// 	calcHistogram(crop_rect(dst));
		// 	waitKey(0);
		// 	calcHistogram(crop_rect(orig));
		// 	waitKey(0);

		// 	cout << " kernel: " << kernel << " Q: " << p << endl;
		// 	imwrite("/home/student/ROVI/VisMand1/report_vis_pro1/img1/img_1_gaus_"+to_string(5)+"_"+to_string(1)+"_constrast_strech.png",dst);

 	  //	//waitKey(0);
		// 	//destroyWindow("final");
		// 	}
		// }
		//for(int i = 3; i < 10 ; i=2+i)
		//{
		//	medianBlur(dst,dst,i);
			//imshow("final", dst);
		namedWindow("final",0);
			resizeWindow("final",450,700);
			imshow("final", dst);
		waitKey(0);
  		//medianBlur(dst,dst,-1);
			//imwrite("/home/student/ROVI/VisMand1/report_vis_pro1/img1/img_1_contraharmonic5_1_eqh.png",dst);
		//}
    //bilateralFilter ( dst, dst, 15, 80, 80 );
    //blur(dst,dst,Size(11,11));
    //mean(dst,dst);
    //cout << "converted" << endl;
    //imshow("Original",orig_crop);
    // calcHistogram(dst);
 return 0;
}
