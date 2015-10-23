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
using namespace std;
using namespace cv;



int main() {
    string path = "img3/";
    string img = path+"src.png";

    hist(img,path,"Hist.png");
    cout << "Hist done: " << path+img << endl;

    //eql(img,path);
    //cout << "Eql done: " << path+img << endl;


    eql(img,path,"Eql.png");
    cout << "Eql done: " << path+img << endl;

    return 0;
}
