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
    image = imread("lena.bmp",CV_LOAD_IMAGE_GRAYSCALE);
    if(image.data < 0)
    {
        cout << "Not loaded" << endl;
    }
    imshow("image",image);
    waitKey(0);

    //---------------------------------------------------//

    //Exercise 1 -  Intensity transformation
    Mat image1 = image.clone();
    for(int x = 0; x<image1.rows;x++ )
    {
        for(int y = 0; y<image1.cols; y++ )
        {
                image1.at<cv::Vec3b>(y, x)[0] += 50;

        }
    }
    imshow("image",image1);
    //Saturate_cast API is available at openCV
    waitKey(0);
    destroyWindow("image");

    // ---------------------------------------------------- //
    //Exercise 2a -  Histogram calculation and plotting
    Mat image2 = image.clone();
    Mat image3 = image.clone();
    // Establish the number of bins
    int histSize = 256;

    // Set the ranges ( graytone)
    float range[] = { 0, 256 } ;
    const float* ranges[] = { range };
    MatND hist;
    int channels[] = {0};
    calcHist( &image2, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false );

    // Show the calculated histogram in command window
    double total;
    total = image2.rows * image2.cols;
    double pdf[256]; //Using for own histogram function
    for( int h = 0; h < histSize; h++ )
    {
        float binVal = hist.at<float>(h);
        pdf[h] = binVal;
       // cout<<" "<<binVal;
    }
    // Plot the histogram
    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );

   Mat histImage( hist_h, hist_w, CV_8UC1, Scalar( 255,0,0) );
   normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

    for( int i = 1; i < histSize; i++ )
    {
       line( histImage, Point( bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1)) ) ,
                           Point( bin_w*(i), hist_h - cvRound(hist.at<float>(i)) ),
                           Scalar( 0, 0, 0), 1, CV_AA, 0  );
    }

    imshow( "Histogram", histImage );
    waitKey(0);
    destroyWindow("Histogram");

    // -------------------------------------------------//
    // Example 2b - Create your Own equalizeHist
    for(int i = 0; i < 256 ; i++) // calculate the PDF, number of pixels/total amount of pixels
    {
       pdf[i] =  pdf[i]/total;
       cout << pdf[i] << endl;
    }
    //calculate CDF
    double cdf[256];
    double sum = 0;
    for(int i = 0; i < 256 ; i++) // calculate the CDF, sum of all PDF = 1
    {
           sum  = sum + pdf[i];
           cdf[i] = sum;
           cout << " " <<cdf[i];
    }
    //split it into 256 -1  bins
    for(int i = 0; i < 256 ; i++) // calculate the CDF, sum of all PDF = 1
    {

           cdf[i] = floor(cdf[i]*255);
           cout << " " <<cdf[i] << endl;
    }
    //Apply it
    for(int x  = 0; x < image3.rows ; x++)
    {
       for(int y = 0; y < image3.cols; y++)
       {

             image3.at<cv::Vec3b>(y, x)[0] = cdf[image3.at<cv::Vec3b>(y, x)[0]];

       }
    }
    imshow("OwnEQhist", image3);
    imshow("Original", image);
    waitKey(0);
    //------------------------------------------------------------//
    //Example 2c Apply equalizeHist from openCV
    Mat equalize_image2;
    equalizeHist(image2,equalize_image2);
    imshow("equalized", equalize_image2);
    waitKey(0);
    destroyWindow("equalized");
    destroyWindow("OwnEQhist");
    destroyWindow("Original");

    // ----------------------------------------------------------//
    //Example 3a  - Linear filtering using filter2D
    Mat image4 = image.clone();
    Mat transformed;
    Mat edge_kernel = (Mat_<float>(3,3) <<
    (-1), -1,  -1,
    (-1), 8,  -1,
    (-1), -1,  -1);

    filter2D(image4, transformed,-1,edge_kernel);
    imshow("transformed", transformed);
    waitKey(0);
    //Example 3b - Linear filtering using own method
    Mat image5 = image.clone();
    

    return 0;
}
