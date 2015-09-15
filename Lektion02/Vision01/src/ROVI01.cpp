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
	cout << "Grey depth " << grey.depth() << " Image depth " <<image.depth() << endl;
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
	
    Mat img_object(image.size(),CV_8UC1, Scalar::all(255));
    Rect Roi(350,100,100,150);
    img_object(Roi).setTo(Scalar::all(0));
    Mat image3 = image.clone();
    image3(Roi).setTo(Scalar::all(0));
    imshow("windowname",image3);
    imshow("test", img_object);
    waitKey(0);

    // Draw lines   - example4

    Mat image4 = image.clone();
    for(int x=350 ; x<=440 ; x++){
        line( image4, Point(x, 100), Point(x,220), Scalar(0,0,0), 1, 8 );
    }

    imshow("windowname",image4);
    waitKey(0);

	return 0;
}
