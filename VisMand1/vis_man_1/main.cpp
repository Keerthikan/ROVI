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

void hist(const std::string& filename, const std::string& path, const std::string& saveas)
{
    Mat gray = imread(filename,CV_LOAD_IMAGE_GRAYSCALE);

    if(gray.data < 0){
        cout << "Not loaded" << endl;
    }

    // Initialize parameters
    int histSize = 256;    // bin size
    float range[] = { 0, 255 };
    const float *ranges[] = { range };

    // Calculate histogram
    MatND hist;
    calcHist( &gray, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false );

    // Show the calculated histogram in command window
    double total;
    total = gray.rows * gray.cols;
    for( int h = 0; h < histSize; h++ )
    {
        float binVal = hist.at<float>(h);
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
              Scalar( 0, 0, 0), 2, 8, 0  );
    }

    imwrite( path+saveas, histImage);
}

void eql(const std::string& filename, const std::string& path, const std::string& saveas) {
    Mat img = cv::imread(filename,CV_LOAD_IMAGE_GRAYSCALE);

    if(img.data < 0){
        cout << "Not loaded" << endl;
    }

    Mat image = img.clone();
    int histSize = 256;

    float range[] = { 0, 256 } ;
    const float* ranges[] = { range };
    MatND hist;

    calcHist( &image, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false );

    // Show the calculated histogram in command window
    double total;
    total = image.rows * image.cols;

    Mat equalize_image;
    equalizeHist(image,equalize_image);

    imwrite( path+saveas, equalize_image);
}

int main() {
    string path = "img3/";
    string img = path+"src.png";

    hist(img,path,"Hist.png");
    cout << "Hist done: " << path+img << endl;

    eql(img,path,"Eql.png");
    cout << "Eql done: " << path+img << endl;

    return 0;
}
