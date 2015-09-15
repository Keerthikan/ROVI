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
#include "opencv2/nonfree/nonfree.hpp"
using namespace std;
using namespace cv;

string getImgType(int imgTypeInt)
{
    int numImgTypes = 35; // 7 base types, with five channel options each (none or C1, ..., C4)

    int enum_ints[] =       {CV_8U,  CV_8UC1,  CV_8UC2,  CV_8UC3,  CV_8UC4,
                             CV_8S,  CV_8SC1,  CV_8SC2,  CV_8SC3,  CV_8SC4,
                             CV_16U, CV_16UC1, CV_16UC2, CV_16UC3, CV_16UC4,
                             CV_16S, CV_16SC1, CV_16SC2, CV_16SC3, CV_16SC4,
                             CV_32S, CV_32SC1, CV_32SC2, CV_32SC3, CV_32SC4,
                             CV_32F, CV_32FC1, CV_32FC2, CV_32FC3, CV_32FC4,
                             CV_64F, CV_64FC1, CV_64FC2, CV_64FC3, CV_64FC4};

    string enum_strings[] = {"CV_8U",  "CV_8UC1",  "CV_8UC2",  "CV_8UC3",  "CV_8UC4",
                             "CV_8S",  "CV_8SC1",  "CV_8SC2",  "CV_8SC3",  "CV_8SC4",
                             "CV_16U", "CV_16UC1", "CV_16UC2", "CV_16UC3", "CV_16UC4",
                             "CV_16S", "CV_16SC1", "CV_16SC2", "CV_16SC3", "CV_16SC4",
                             "CV_32S", "CV_32SC1", "CV_32SC2", "CV_32SC3", "CV_32SC4",
                             "CV_32F", "CV_32FC1", "CV_32FC2", "CV_32FC3", "CV_32FC4",
                             "CV_64F", "CV_64FC1", "CV_64FC2", "CV_64FC3", "CV_64FC4"};

    for(int i=0; i<numImgTypes; i++)
    {
        if(imgTypeInt == enum_ints[i]) return enum_strings[i];
    }
    return "unknown image type";
}

int main() {
	Mat image; 
	image = imread("image.png",CV_LOAD_IMAGE_COLOR);
	if (! image.data)
	{
		cout << " not loaded" << endl; 
	}
	imshow("windowname",image);
	waitKey(0);


	// Load image in greyscale 
	Mat grey;
	cvtColor(image,grey, CV_BGR2GRAY);
	imshow("windowname", grey);
	waitKey(0);

	// Image depth 
    cout << "Grey depth " << getImgType(grey.type()) << " Image depth " <<getImgType(image.type()) << endl;
	cout << "Grey channel " << grey.channels() << " Image channel " <<image.channels() << endl;

	//Draw rectangle - example1
	cout << "First example" << endl;
	Mat Square_1 = image.clone();
	rectangle(Square_1,Point(350,100),Point(440,220),Scalar(0,0,0),-1);
	imshow("windowname",Square_1);
	waitKey(0);
	
	//Draw rectangle - example2
	cout << "Second example" << endl;
	Mat Square_2 = image.clone();
	for (size_t x = 350; x < 440; x++)
	{
   	  for (size_t y = 100; y < 220; y++)
	  {
              Square_2.at<cv::Vec3b>(y, x)[0] = 0;
              Square_2.at<cv::Vec3b>(y, x)[1] = 0;
              Square_2.at<cv::Vec3b>(y, x)[2] = 0;
    	  }
	}
	imshow("windowname",Square_1);
	waitKey(0);

	//Draw rectangle  - example3
    cout << "Third Example" << endl;
    Mat img_object(image.size(),CV_8UC1, Scalar::all(255));
    Rect Roi(350,100,100,150);
    img_object(Roi).setTo(Scalar::all(0));
    Mat image3 = image.clone();
    image3(Roi).setTo(Scalar::all(0));
    imshow("windowname",image3);
    imshow("test", img_object);
    waitKey(0);

    // Draw lines   - example4
    cout << "Fourth example" << endl;
    Mat image4 = image.clone();
    for(int x=350 ; x<=440 ; x++){
        line( image4, Point(x, 100), Point(x,220), Scalar(0,0,0), 1, 8 );
    }

    imshow("windowname",image4);
    waitKey(0);

	return 0;
}
