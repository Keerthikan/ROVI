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

  //-------------------------------------------------------------//

			/* code */
				/* code */
		// for (int cut = 100; cut < 900; cut= cut+50) {
		// 	/* code */
		// 	for (int order= 1; order < 15; order++) {
		// 		/* code */
		// 		cout << "cut: " << cut << " order: " << order << endl;
		 		applyFilter(src4_2, output, 500, 14);
				Mat test_output = imread("/home/student/ROVI/VisMand1/report_vis_pro1/img4/filteredOutput_"+to_string(500)+to_string(14)+".png",CV_LOAD_IMAGE_GRAYSCALE);
				constrast_stretching(test_output,test_output);
				imwrite("/home/student/ROVI/VisMand1/report_vis_pro1/img4/filteredOutput_"+to_string(500)+to_string(14)+"_contrast_strech.png",test_output);
		// 		Mat_<float> newC = imread("/home/student/ROVI/VisMand1/report_vis_pro1/img4/filteredOutput_"+to_string(cut)+to_string(order)+".png",CV_LOAD_IMAGE_GRAYSCALE);
		// 		fft2(newC,cut,order);
		// 	}
		// }


		//imshow("init", src4_2);
		//Mat_<float> Test;
		//cv::FileStorage fs(outoutS,cv::FileStorage::READ);
		//fs["ImageId"]>>Test;
		//fft2(Test);
		imshow("das", test_output);
		//imshow("src", src);
		//imshow("Original",orig);
    //run(img2,0);
    waitKey(0);
    return 0;
}

