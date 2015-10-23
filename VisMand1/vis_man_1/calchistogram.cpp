#include "calchistogram.h"

Mat calcHistogram(Mat dst){

    /// Set the ranges ( for B,G,R) )
      int histSize = 256;
      float range[] = { 0, 256 } ;
      const float* histRange = { range };

      bool uniform = true;
      bool accumulate = false;

      Mat hist, hist1;

      /// Compute the histograms:
      calcHist( &dst, 1, 0, Mat(), hist, 1, &histSize, &histRange, uniform, accumulate );

      // Draw the histograms for B, G and R
      int hist_w = 512; int hist_h = 400;
      int bin_w = cvRound( (double) hist_w/histSize );

      Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

      /// Normalize the result to [ 0, histImage.rows ]
      normalize(hist, hist1, 0, histImage.rows, NORM_MINMAX, -1, Mat() );


      /// Draw for each channel
      for( int i = 1; i < histSize; i++ )
      {
          line( histImage, Point( bin_w*(i-1), hist_h - cvRound(hist1.at<float>(i-1)) ) ,
                           Point( bin_w*(i), hist_h - cvRound(hist1.at<float>(i)) ),
                           Scalar( 255, 0, 0), 2, 8, 0  );
      }

      /// Display
      namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE );
      imshow("calcHist Demo", histImage );
      return(hist);
}
