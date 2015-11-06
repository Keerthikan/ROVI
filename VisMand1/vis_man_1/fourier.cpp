#include "fourier.h"
//#include "notch.h"

template<class ImgT>
void dftshift(ImgT& img) {
	const int cx = img.cols/2;
	const int cy = img.rows/2;

	ImgT tmp;
	ImgT topLeft(img, cv::Rect(0, 0, cx, cy));
	ImgT topRight(img, cv::Rect(cx, 0, cx, cy));
	ImgT bottomLeft(img, cv::Rect(0, cy, cx, cy));
	ImgT bottomRight(img, cv::Rect(cx, cy, cx, cy));

	topLeft.copyTo(tmp);
	bottomRight.copyTo(topLeft);
	tmp.copyTo(bottomRight);

	topRight.copyTo(tmp);
	bottomLeft.copyTo(topRight);
	tmp.copyTo(bottomLeft);
}


cv::Mat BHPF(double d0, double n, int wy, int wx, int cx, int cy)
{
	cv::Mat_<cv::Vec2f> hpf(wy, wx);
	for(int y = 0; y < wy; ++y) {
		for(int x = 0; x < wx; ++x) {
			// Real part
			const double d = std::sqrt( double((x-cx)*(x-cx)) + double((y-cy)*(y-cy)) );

			if(d==0) // Avoid division by zero
				hpf(y,x)[0] = 0;
			else
				hpf(y,x)[0] = 1.0 / (1.0 + std::pow(d0/d, 2.0*n));

			// Imaginary part
			hpf(y,x)[1] = 0;
		}
	}
    return hpf;
}



void fft2(Mat_<float> src)
{
	int x = getOptimalDFTSize(2* src.rows );
	int y = getOptimalDFTSize(2* src.cols );
	copyMakeBorder(src, src, 0, (x - src.rows), 0, (y - src.cols), BORDER_CONSTANT, Scalar::all(0));
	     // Get padded image size
	     const int wx = src.cols, wy = src.rows;
	     const int cx = wx/2, cy = wy/2;


	//--------------------------------//
	// DFT - performing		     //
	cv::Mat_<float> imgs[] = {src.clone(), Mat::zeros(src.size(), CV_32F)};
	cv::Mat_<cv::Vec2f> img_dft;
	merge(imgs,2,img_dft);
	dft(img_dft, img_dft);
	split(img_dft,imgs);
	cv::Mat_<float> magnitude, phase;
	cartToPolar(imgs[0],imgs[1],magnitude,phase);
	dftshift(magnitude);
	magnitude = magnitude + 1.0f;
	log(magnitude,magnitude);
	normalize(magnitude,magnitude,0,1,CV_MINMAX);
	namedWindow("img_dft",WINDOW_NORMAL);
	imshow("img_dft",magnitude);
	waitKey(0);

}

// void fft(Mat_<float> img)
// {
//
// 	// Get original size
//     int wxOrig = img.cols;
//     int wyOrig = img.rows;
//
//
//     int m = cv::getOptimalDFTSize( 2*wyOrig );
//     int n = cv::getOptimalDFTSize( 2*wxOrig );
//
//     copyMakeBorder(img, img, 0, m - wyOrig, 0, n - wxOrig, cv::BORDER_CONSTANT, cv::Scalar::all(0));
//
//     // Get padded image size
//     const int wx = img.cols, wy = img.rows;
//     const int cx = wx/2, cy = wy/2;
//
//     //std::cout << wxOrig << " " << wyOrig << std::endl;
//     //std::cout << wx << " " << wy << std::endl;
//     std::cout << "Center of frequency rectangle: " <<cx << " " << cy << std::endl;
//
// 	// Compute DFT of image
// 	cv::Mat_<float> imgs[] = {img.clone(), cv::Mat_<float>::zeros(wy, wx)};
//     cv::Mat_<cv::Vec2f> img_dft;
// 	cv::merge(imgs, 2, img_dft);
// 	cv::dft(img_dft, img_dft);
//
// 	// Shift to center
// 		dftshift(img_dft);
//
// 		// Used for visualization only
// 		cv::Mat_<float> magnitude, phase;
// 		cv::split(img_dft, imgs);
// 		cv::cartToPolar(imgs[0], imgs[1], magnitude, phase);
// 		magnitude = magnitude + 1.0f;
// 		cv::log(magnitude, magnitude);
// 		cv::normalize(magnitude, magnitude, 0, 1, CV_MINMAX);
// 		namedWindow("img_dft",WINDOW_NORMAL);
// 		cv::imshow("img_dft", magnitude);
// 		waitKey(0);
//
//
// 		//cv::Mat hpf = notch(250,2,wy,wx,cx,cy);
// 		///cv::mulSpectrums(hpf, img_dft,img_dft,cv::DFT_ROWS);
// 		//dftshift(img_dft);
//
// 		//Display high pass filter
// 	 //cv::Mat realImg[2];
// 	 //cv::split(hpf,realImg);
// 	// cv::Mat realHPF = realImg[0];
// 	 //cv::normalize(realHPF, realHPF, 0.0, 1.0, CV_MINMAX);
// 	 //cv::imshow("HPF", realHPF);
//
// 	 //----- Compute IDFT of HPF filtered image
//
// 			 //you can do this
// 			 //cv::idft(img_dft, img_dft); //the result is a 2 channel image
// 			 //Mat output;
// 			 // therefore you split it and get the real one
// 			 //split(img_dft, imgs);
// 			 //normalize(imgs[0], output, 0, 1, CV_MINMAX);
//
// 			 //or you can do like this, then you dont need to split
// 			 //cv::Mat_<float> output;
// 	 //cv::dft(img_dft, output, cv::DFT_INVERSE| cv::DFT_REAL_OUTPUT);
// 	 //cv::Mat_<float> croppedOutput(output,cv::Rect(0,0,wxOrig,wyOrig));
//
// 	// 		 cv::normalize(output, output, 0, 1, CV_MINMAX);
// 	// 		 cv::normalize(img, img, 0.0, 1.0, CV_MINMAX);
// 	 //
// 	 //
// 	//  cv::imshow("Input", img);
// 	//  cv::imshow("High-pass filtered input", croppedOutput);
// 	//  cv::imwrite("out.png", croppedOutput * 255);
// 	// 		 cv::waitKey(0);
//
// }
