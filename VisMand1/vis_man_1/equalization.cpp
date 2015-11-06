#include "equalization.h"



Mat  eql(Mat img, Mat dst) {
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
    //double total;
    //total = image.rows * image.cols;

    equalizeHist(image,dst);


}
