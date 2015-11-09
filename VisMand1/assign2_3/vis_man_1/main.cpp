#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <math.h>
#include "opencv2/nonfree/nonfree.hpp"

#define RECT_POS_X 1075 // 500
#define RECT_POS_Y 1400 // 900
#define RECT_SIZE  200  // 500

using namespace std;
using namespace cv;

void save_hist(Mat &img, const std::string& saveas)
{
    if(img.data < 0){
        cout << "Not loaded" << endl;
    }

    vector<Mat> bgr_planes;
    split( img, bgr_planes );

    int histSize = 256;

    float range[] = { 0, 256 } ;
    const float* histRange = { range };

    bool uniform = true; bool accumulate = false;

    Mat b_hist, g_hist, r_hist;

    calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
    calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
    calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );

    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );

    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

    for( int i = 1; i < histSize; i++ )
    {
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
              Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
              Scalar( 255, 0, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
              Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
              Scalar( 0, 255, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
              Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
              Scalar( 0, 0, 255), 2, 8, 0  );
    }

    namedWindow("Show Window",cv::WINDOW_NORMAL);
    imshow("Show Window", histImage);

    imwrite(saveas,histImage);

    //waitKey(0);
}

cv::Mat_<float> eql(const std::string& filename, const std::string& saveas) {
    cv::Mat src = imread(filename,CV_LOAD_IMAGE_GRAYSCALE);

    if(src.data < 0){
        cout << "Not loaded" << endl;
    }


    cv::Mat image = src.clone();
    int histSize = 256;

    float range[] = { 0, 256 } ;
    const float* ranges[] = { range };
    MatND hist;

    calcHist( &image, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false );

    double total;
    total = image.rows * image.cols;

    cv::Mat equalize_image;
    equalizeHist(image,equalize_image);

    imwrite(saveas,equalize_image);
    cv::Mat_<float> tmp = equalize_image;
    return tmp;
}

cv::MatND getHistogram(const cv::Mat &image)
{
    int numOfIm = 1;
    int channels[] = {0};
    cv::Mat mask;
    cv::MatND hist;
    int dimensions = 1;
    int numOfBins[] = {256};
    float minMaxValue[] = {0.0, 255.0};
    const float* ranges[] = {minMaxValue};
    cv::calcHist(&image, numOfIm, channels, mask, hist, dimensions, numOfBins, ranges);
    return hist;
}

cv::Mat_<float> getHistogramImage(const cv::Mat &image)
{
    int numOfBins = 256;
    cv::MatND hist= getHistogram(image);

    double maxVal=0, minVal=0;
    cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);
    cv::Mat histImg = cv::Mat::zeros(numOfBins,numOfBins, CV_8UC1);

    int hpt = static_cast<int>(0.9*numOfBins);

    for( int h = 0; h < numOfBins; h++ ){
        float binVal = hist.at<float>(h);
        int intensity;
        if (binVal != 0){
            intensity = static_cast<int>(hpt* binVal/maxVal) ;
            cv::line(histImg,cv::Point(h,numOfBins), cv::Point(h,numOfBins-intensity), cv::Scalar::all(255));
        }
    }

    return histImg.clone();
}

cv::Mat_<float> midpoint(cv::Mat_<float> &img, unsigned int filter_size)
{
    cv::Mat_<float> img_filter = img.clone();
    std::vector<float> filter_list(filter_size*filter_size, 0.0);
    unsigned int temp_x, temp_y, i = 0, percentile_i;

    for(size_t y = 0; y < img.cols; y++)
    {
        for(size_t x = 0; x < img.rows; x++)
        {
            for(size_t filter_y = 0; filter_y < filter_size; ++filter_y)
            {
                for(size_t filter_x = 0; filter_x < filter_size; ++filter_x)
                {
                    temp_x = (x - filter_size / 2 + filter_x + img.rows) % img.rows;
                    temp_y = (y - filter_size / 2 + filter_y + img.cols) % img.cols;

                    filter_list[i] = img(temp_x, temp_y);
                    i++;
                }
            }
            i = 0;

            std::sort(filter_list.begin(), filter_list.end());

            img_filter(x, y) = (filter_list.front() + filter_list.back())/2;
        }
    }

    return img_filter;
}

cv::Mat_<float> adaptive_median_filter(cv::Mat_<float> &img, unsigned int max_filter_size)
{
    cv::Mat_<float> img_filter = img.clone();
    std::vector<float> filter_list;
    unsigned int temp_x,
            temp_y,
            i = 0,
            filter_size,
            z_min,
            z_max,
            z_med;

    for(size_t y = 0; y < img.cols; y++)
    {
        for(size_t x = 0; x < img.rows; x++)
        {
            filter_size = 3;
            while(true)
            {
                filter_list.resize(filter_size*filter_size);

                for(size_t filter_y = 0; filter_y < filter_size; ++filter_y)
                {
                    for(size_t filter_x = 0; filter_x < filter_size; ++filter_x)
                    {
                        temp_x = (x - filter_size / 2 + filter_x + img.rows) % img.rows;
                        temp_y = (y - filter_size / 2 + filter_y + img.cols) % img.cols;

                        filter_list[i] = img(temp_x, temp_y);
                        i++;
                    }
                }
                i = 0;

                std::sort(filter_list.begin(), filter_list.end());

                z_min = filter_list[0];
                z_max = filter_list[filter_size*filter_size - 1];
                z_med = filter_list[filter_size*filter_size/2];

                if(z_min == z_med || z_med == z_max)
                {
                    filter_size += 2;
                }
                else
                {
                    if(img(x, y) == z_min || img(x, y) == z_max)
                    {
                        img_filter(x, y) = z_med;
                    }
                    else
                    {
                        img_filter(x, y) = img(x, y);
                    }
                    break;
                }

                if(max_filter_size == filter_size)
                {
                    img_filter(x, y) = img(x, y);
                    break;
                }
            }
        }
    }

    return img_filter;
}

void dftshift(cv::Mat_<float> &magnitude) {
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

cv::Mat_<float> get_DFT_image(cv::Mat_<float> &img, bool log)
{
    int rows = cv::getOptimalDFTSize(2 * img.rows);
    int cols = cv::getOptimalDFTSize(2 * img.cols);
    int imgRows = img.rows;
    int imgCols = img.cols;
    cv::copyMakeBorder(img, img, 0, rows - img.rows, 0, cols - img.cols, cv::BORDER_CONSTANT, cv::Scalar(0));

    cv::Mat_<float> imgs[] = {img.clone(), cv::Mat_<float>(img.rows, img.cols, 0.0f)};
    cv::Mat_<cv::Vec2f> img_dft;
    cv::merge(imgs, 2, img_dft);

    cv::dft(img_dft, img_dft);
    cv::split(img_dft, imgs);

    cv::Mat_<float> magnitude, phase;
    cv::cartToPolar(imgs[0], imgs[1], magnitude, phase);

    dftshift(magnitude);

    if(log)
    {
        magnitude += 1.0f;
        cv::log(magnitude, magnitude);
    }

    img = img(cv::Rect(0,0,imgCols,imgRows));

    return magnitude;
}

void rect_hist(cv::Mat_<float> img, const std::string& filename, const std::string& path, const std::string& saveas){
    imwrite(path+filename, img);
    cv::Mat_<float> hist_img3 = getHistogramImage(img);
    imwrite(path+"hist_"+saveas+"_"+filename, hist_img3);

    cv::Mat hist_img3_tmp = cv::imread(path+filename);
    save_hist(hist_img3_tmp,path+"hist_"+saveas+"_"+filename);

    cv::Mat_<float> img3_rect = img(cv::Rect(RECT_POS_X, RECT_POS_Y, RECT_SIZE, RECT_SIZE));
    imwrite(path+"rect_"+saveas+"_"+filename, img3_rect);

    cv::Mat_<float> hist_img3_rect = getHistogramImage(img3_rect);
    imwrite(path+"hist_rect_"+saveas+"_"+filename, hist_img3_rect);

    cv::Mat img3_rect_tmp = cv::imread(path+"rect_"+saveas+"_"+filename);
    save_hist(img3_rect_tmp,path+"hist_rect_"+saveas+"_"+filename);

    cv::Mat_<float> DFT_img3_rect = get_DFT_image(img3_rect, true);
    cv::normalize(DFT_img3_rect, DFT_img3_rect, 0, 255, CV_MINMAX);
    imwrite(path+"DFT_rect_"+saveas+"_"+filename, DFT_img3_rect);
}

void adaptiveMedian(Mat src, Mat dst)
{
    double z_min, z_max,z_med;
    int kernel = 3;
    for(int row = kernel/2; row < src.rows - kernel/2-1; row++)
    {
        for(int col = kernel/2; col < src.cols - kernel/2-1; col++)
        {
            double den=0,num=0,value=0;
            for(int i = -(kernel/2); i <= (kernel/2) ; i++)
            {
                for(int j = -(kernel/2) ; j <= (kernel/2); j++)
                {
                    if (z_min > src.at<uchar>(row+i,col+j))
                    {
                        z_min = src.at<uchar>(row+i,col+j);
                    }
                    if (z_max < src.at<uchar>(row+i,col+j))
                    {
                        z_max = src.at<uchar>(row+i,col+j);
                    }
                    if(i == j)
                    {
                        if (src.at<uchar>(row+i,col+j) == z_min ||  src.at<uchar>(row+i,col+j) == z_min)
                        {
                            kernel = 2 + kernel;
                        }
                        else
                        {
                            z_med = src.at<uchar>(row+i,col+j);
                        }
                    }
                    if(kernel == src.rows*src.cols)
                    {
                        cout << "too big" << endl;
                        exit -1;
                    }
                }
                if(src.at<uchar>(row,col) == z_max || src.at<uchar>(row,col) == z_min )
                {
                    dst.at<uchar>(row,col) = z_med;
                }
                else
                {
                    dst.at<uchar>(row,col) = src.at<uchar>(row,col);
                }
            }
        }
    }

    rect_hist(dst,"adaptive_2_2_tmp.png","img2/","1");
}

void assign2(const std::string& filename, const std::string& path, const std::string& saveas) {

    cv::Mat img2 = cv::imread(filename,CV_LOAD_IMAGE_GRAYSCALE);

    if(img2.data < 0){
        cout << "Not loaded" << endl;
    }

    rect_hist(img2,"img2.png","img2/","org");

    std::stringstream ss;

    cv::Mat img_test;
    for (size_t i = 3; i <= 15; i+=2)
    {
        ss.str("");
        ss << i;

        std::string a = ss.str();
        medianBlur(img2,img_test,i);
        imwrite(path+"median_"+a+"_"+saveas, img_test);

        cv::Mat_<float> img2_ss = cv::imread(path+"median_"+a+"_"+saveas,CV_LOAD_IMAGE_GRAYSCALE);
        rect_hist(img2_ss,"median_"+a+"_"+saveas,"img2/",a);

        cout << i << endl;
    };

    cv::Mat_<float> img2_f = cv::imread(filename,CV_LOAD_IMAGE_GRAYSCALE);
    cv::Mat_<float> img_test_adaptive;
    img_test_adaptive = adaptive_median_filter(img2_f, 51);
    imwrite(path+"adaptive_test_"+saveas, img_test_adaptive);

    cv::Mat img2_s = cv::imread(path+"adaptive_test_"+saveas,CV_LOAD_IMAGE_GRAYSCALE);
    rect_hist(img2_s,"adaptive_test_"+saveas,"img2/","1");


    for (size_t i = 3; i <= 25; i+=2)
    {
        ss.str("");
        ss << i;

        std::string a = ss.str();
        cv::Mat img_test_test;
        GaussianBlur(img2_s,img_test_test,Size(i,i),0,0);
        rect_hist(img_test_test,"adaptive_"+a+"_test_"+saveas,"img2/","2");
        eql("img2/adaptive_"+a+"_test_"+saveas,"img2/eql_"+a+"test.png");

        cout << i << endl;
    };
}

void assign3(const std::string& filename, const std::string& path, const std::string& saveas) {
    cv::Mat_<float> img3 = cv::imread(filename,CV_LOAD_IMAGE_GRAYSCALE);

    if(img3.data < 0){
        cout << "Not loaded" << endl;
    }

    rect_hist(img3,"img3.png","img3/","src");

    std::stringstream ss;

    cv::Mat_<float> img_test;
    for (size_t i = 3; i <= 11; i+=2)
    {
        ss.str("");
        ss << i;
        std::string a = ss.str();
        img_test = midpoint(img3, i);
        imwrite(path+"midpoint_"+a+"_"+saveas, img_test);

        cv::Mat_<float> img3_ss = cv::imread(path+"midpoint_"+a+"_"+saveas,CV_LOAD_IMAGE_GRAYSCALE);
        rect_hist(img3_ss,"midpoint_"+a+"_"+saveas,"img3/",a);

        cout << a << endl;
    };
    Mat imgH;

    for(double j = 0.1 ; j<=2; j+=0.1){
        ss.str("");
        ss << j;
        std::string a = ss.str();

        cv::Mat img3_ss = cv::imread(path+"midpoint_5_final_img3.png",CV_LOAD_IMAGE_GRAYSCALE);
        img3_ss.convertTo(imgH, -1, j, 0);

        cout << "imgh_" << a << endl;

        rect_hist(imgH,"contrast_5_"+a+"_"+saveas,"img3/",a);
    }

    for(double j = 0.1 ; j<=2; j+=0.05){
        ss.str("");
        ss << j;
        std::string a = ss.str();

        eql("img3/contrast_5_"+a+"_final_img3.png","img3/eql_"+a+"result.png");

        cout << "imgh_const_" << a << endl;
    }
}

int main() {
    cout << "Assignment 2..." << endl;
    assign2("img2/src.png","img2/","final_img2.png");

    eql("img2/median_11_final_img2.png","img2/eql.png");
    eql("img2/adaptive_test_final_img2.png","img2/eql_ad.png");
    eql("img2/adaptive_2_test_final_img2.png","img2/eql_ad2.png");

    //cout << "Assignment 3..." << endl;
    //assign3("img3/src.png","img3/","final_img3.png");
    //
    //cv::Mat img3_ss = cv::imread("img3/org.png",CV_LOAD_IMAGE_GRAYSCALE);
    //rect_hist(img3_ss,"org_res_total.png","img3/","eee");

    cout << "All Done!" << endl;

    return 0;
}






























