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
	
  	//Mat img_object(image.size(),CV_8UC1, Scalar::all(0));
	//Rect Roi(350,100,100,150);
	//img_object(Roi).setTo(Scalar::all(255));
	//imshow("ss",img_object);
	//waitKey(0);
	Mat test = image.clone();
	Mat img_scene;
	cvtColor(test,img_scene,CV_BGR2GRAY);
	Mat img_object = img_scene(cv::Range(100,220), cv::Range(350,440));
	
	//-- Step 1: Detect the keypoints using SURF Detector
  int minHessian = 600;

  SurfFeatureDetector detector( minHessian );

  std::vector<KeyPoint> keypoints_object, keypoints_scene;

  detector.detect( img_object, keypoints_object );
  detector.detect( img_scene, keypoints_scene );

  //-- Step 2: Calculate descriptors (feature vectors)
  SurfDescriptorExtractor extractor;

  Mat descriptors_object, descriptors_scene;

  extractor.compute( img_object, keypoints_object, descriptors_object );
  extractor.compute( img_scene, keypoints_scene, descriptors_scene );

  //-- Step 3: Matching descriptor vectors using FLANN matcher
  FlannBasedMatcher matcher;
  std::vector< DMatch > matches;
  matcher.match( descriptors_object, descriptors_scene, matches );

  double max_dist = 0; double min_dist = 100;

  //-- Quick calculation of max and min distances between keypoints
  for( int i = 0; i < descriptors_object.rows; i++ )
  { double dist = matches[i].distance;
    if( dist < min_dist ) min_dist = dist;
    if( dist > max_dist ) max_dist = dist;
  }

  cout << "-- Max dist :" << max_dist;
  cout << "-- Min dist :" << min_dist;

  //-- Draw only "good" matches (i.e. whose distance is less than 3*min_dist )
  std::vector< DMatch > good_matches;

  for( int i = 0; i < descriptors_object.rows; i++ )
  { if( matches[i].distance < 3*min_dist )
     { good_matches.push_back( matches[i]); }
  }

  Mat img_matches;
  drawMatches( img_object, keypoints_object, img_scene, keypoints_scene,
               good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
               vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

  //-- Localize the object
  std::vector<Point2f> obj;
  std::vector<Point2f> scene;

  for( int i = 0; i < good_matches.size(); i++ )
  {
    //-- Get the keypoints from the good matches
    obj.push_back( keypoints_object[ good_matches[i].queryIdx ].pt );
    scene.push_back( keypoints_scene[ good_matches[i].trainIdx ].pt );
  }

  Mat H = findHomography( obj, scene, CV_RANSAC );

  //-- Get the corners from the image_1 ( the object to be "detected" )
  std::vector<Point2f> obj_corners(4);
  obj_corners[0] = cvPoint(0,0); obj_corners[1] = cvPoint( img_object.cols, 0 );
  obj_corners[2] = cvPoint( img_object.cols, img_object.rows ); obj_corners[3] = cvPoint( 0, img_object.rows );
  std::vector<Point2f> scene_corners(4);

  perspectiveTransform( obj_corners, scene_corners, H);

  //-- Draw lines between the corners (the mapped object in the scene - image_2 )
  line( img_matches, scene_corners[0] + Point2f( img_object.cols, 0), scene_corners[1] + Point2f( img_object.cols, 0), Scalar(0, 255, 0), 4 );
  line( img_matches, scene_corners[1] + Point2f( img_object.cols, 0), scene_corners[2] + Point2f( img_object.cols, 0), Scalar( 0, 255, 0), 4 );
  line( img_matches, scene_corners[2] + Point2f( img_object.cols, 0), scene_corners[3] + Point2f( img_object.cols, 0), Scalar( 0, 255, 0), 4 );
  line( img_matches, scene_corners[3] + Point2f( img_object.cols, 0), scene_corners[0] + Point2f( img_object.cols, 0), Scalar( 0, 255, 0), 4 );

  //-- Show detected matches
  imshow( "Good Matches & Object detection", img_matches );


	return 0;
}
