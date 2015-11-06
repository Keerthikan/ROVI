#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <math.h>
#include "opencv2/nonfree/nonfree.hpp"

void run(const std::string& filename, bool highpass, bool print) {
    cv::Mat img = cv::imread(filename,CV_LOAD_IMAGE_GRAYSCALE);

    cv::Mat padded;

    int m = cv::getOptimalDFTSize(2*img.rows);
    int n = cv::getOptimalDFTSize(2*img.cols);


    cv::copyMakeBorder(img,padded,0,m-img.rows,0,n-img.cols,cv::BORDER_CONSTANT,cv::Scalar::all(0));

    cv::Mat planes[] = {cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F)};
    cv::Mat complexI;

    merge(planes, 2, complexI);

    cv::Mat_<float> imgs[] = {img.clone(), cv::Mat_<float>(img.rows, img.cols, 0.0f)};
    cv::Mat_<cv::Vec2f> img_dft;

    cv::dft(complexI,complexI);

    cv::split(complexI,planes);
    cv::magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
    cv::Mat magI = planes[0];

    magI += cv::Scalar::all(1);                    // switch to logarithmic scale
    log(magI, magI);

    // crop the spectrum, if it has an odd number of rows or columns
    magI = magI(cv::Rect(0, 0, magI.cols & -2, magI.rows & -2));

    // rearrange the quadrants of Fourier image  so that the origin is at the image center
    int cx = magI.cols/2;
    int cy = magI.rows/2;

    cv::Mat q0(magI, cv::Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    cv::Mat q1(magI, cv::Rect(cx, 0, cx, cy));  // Top-Right
    cv::Mat q2(magI, cv::Rect(0, cy, cx, cy));  // Bottom-Left
    cv::Mat q3(magI, cv::Rect(cx, cy, cx, cy)); // Bottom-Right

    cv::Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);

    normalize(magI, magI, 0, 1, CV_MINMAX); // Transform the matrix with float values into a

    if(print==true)
        cv::imwrite("Mag.png",magI);

    cv::imshow(filename, img);
    cv::imshow("Mag",magI);
    cv::waitKey();
    cv::destroyWindow(filename);
    cv::destroyWindow("Mag");

}

int main()
{
    run("lena.bmp", false, false);
    run("lena_face.bmp", false, false);
    run("lena_hair.bmp", false, false);
    run("lena_hat.bmp", false, true);
    run("src.png", false, true);

    cv::waitKey();

    return 0;
}
















