#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <math.h>
#include "opencv2/nonfree/nonfree.hpp"
using namespace cv;
using namespace std;
void dftshift(cv::Mat_<float>& magnitude) {
   const int cx = magnitude.cols/2;
   const int cy = magnitude.rows/2;
   
   cv::Mat_<float> tmp;
   cv::Mat_<float> topLeft(magnitude, cv::Rect(0, 0, cx, cy));
   cv::Mat_<float> topRight(magnitude, cv::Rect(cx, 0, cx, cy));
   cv::Mat_<float> bottomLeft(magnitude, cv::Rect(0, cy, cx, cy));
   cv::Mat_<float> bottomRight(magnitude, cv::Rect(cx, cy, cx, cy));
   
   topLeft.copyTo(tmp);
   bottomRight.copyTo(topLeft);
   tmp.copyTo(bottomRight);
   
   topRight.copyTo(tmp);
   bottomLeft.copyTo(topRight);
   tmp.copyTo(bottomLeft);
}

int main()
{
    //Exercise 1 

     Mat_<float> Lena_full = imread("lena(1).bmp", CV_LOAD_IMAGE_GRAYSCALE);	
     Mat_<float> Lena_face = imread("lena_face.bmp", CV_LOAD_IMAGE_GRAYSCALE);
     Mat_<float> Lena_hair = imread("lena_hair.bmp", CV_LOAD_IMAGE_GRAYSCALE);
     Mat_<float> Lena_hat  = imread("lena_hat.bmp", CV_LOAD_IMAGE_GRAYSCALE);
     if(Lena_full.data < 0 )
     {
	cout << "loading issues" << endl; 
	return -1; 
     }

     waitKey(0);
   //---------------------------------//
   // Pad Borders //
   int x = getOptimalDFTSize( Lena_full.rows );
   int y = getOptimalDFTSize( Lena_full.cols );
   copyMakeBorder(Lena_full, Lena_full, 0, (x - Lena_full.rows), 0, (y - Lena_full.cols), BORDER_CONSTANT, Scalar::all(0));
   //imshow("show",Lena_full);
   //waitKey(0);
   //--------------------------------//
   // DFT - performing		     //
   cv::Mat_<float> imgs[] = {Lena_full.clone(), Mat::zeros(Lena_full.size(), CV_32F)};
   cv::Mat_<cv::Vec2f> img_dft;
   merge(imgs,2,img_dft);
   dft(img_dft, img_dft);     
   split(img_dft,imgs);	
   cv::Mat_<float> magnitude, phase;
   cartToPolar(imgs[0],imgs[1],magnitude,phase);
   dftshift(magnitude);
   //log(magnitude,magnitude);
   //normalize(magnitude,magnitude,0,1,CV_MINMAX);
   //imshow("magnitude",magnitude);
   //waitKey(0);


//----------------------------------------------------------------//
//Exercise 2							  //

   magnitude(cv::Rect(magnitude.cols/2 - 25, magnitude.rows/2 -25, 50, 50)) = 0.0f;
   cv::Mat_<float> magnitude_del;
   log(magnitude,magnitude_del);
   dftshift(magnitude_del);

   polarToCart(magnitude_del,phase,imgs[0],imgs[1]);

   Mat image;
   Mat imgout;
   merge(imgs,2,image);

   dft(image,imgout, DFT_INVERSE+DFT_SCALE+DFT_REAL_OUTPUT);


   cv::normalize(Lena_full, Lena_full, 0.0, 1.0, CV_MINMAX);
   cv::normalize(magnitude_del, magnitude_del, 0.0, 1.0, CV_MINMAX);
   cv::normalize(phase, phase, 0.0, 1.0, CV_MINMAX);	
   cv::normalize(imgout, imgout, 0.0, 1.0, CV_MINMAX);
   cout << "done" << endl; 
   cv::imshow("Output", imgout);
   cv::imshow("Input", Lena_full);
   cv::imshow("Magnitude", magnitude_del);
   waitKey(0);
}



















