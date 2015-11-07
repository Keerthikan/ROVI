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

Mat create_spectrum_magnitude_display(Mat& complexImg, bool rearrange)
{
    Mat planes[2];

    // compute magnitude spectrum (N.B. for display)
    // compute log(1 + sqrt(Re(DFT(img))**2 + Im(DFT(img))**2))

    split(complexImg, planes);
    magnitude(planes[0], planes[1], planes[0]);

    Mat mag = (planes[0]).clone();
    mag += Scalar::all(1);
    log(mag, mag);

    if (rearrange)
    {
        // re-arrange the quaderants
        dftshift(mag);
    }

    normalize(mag, mag, 0, 1, CV_MINMAX);

    return mag;

}

void run(const std::string& filename, bool highpass) {
    // A gray image
    cv::Mat_<float> img = cv::imread(filename, CV_LOAD_IMAGE_GRAYSCALE);

    //Pad the image with borders using copyMakeBorders. Use getOptimalDFTSize(A+B-1). See G&W page 251,252 and 263 and dft tutorial. (Typicly A+B-1 ~ 2A is used)
    int rows = cv::getOptimalDFTSize(2*img.rows);
    int cols = cv::getOptimalDFTSize(2*img.cols);
    int imgRows = img.rows;
    int imgCols = img.cols;
    cv::copyMakeBorder(img,img,0,rows-img.rows,0,cols-img.cols,cv::BORDER_CONSTANT,cv::Scalar(0));

    //Copy the gray image into the first channel of a new 2-channel image of type Mat_<Vec2f>, e.g. using merge(), save it in img_dft
    //The second channel should be all zeros.
   cv::Mat_<float> imgs[] = {img.clone(), cv::Mat_<float>(img.rows, img.cols, 0.0f)};
   cv::Mat_<cv::Vec2f> img_dft;
   cv::merge(imgs, 2, img_dft);

   // Compute DFT
   cv::dft(img_dft, img_dft);

   // Split
   cv::split(img_dft, imgs);

   // Compute magnitude/phase
   cv::Mat_<float> magnitude, phase;
   cv::cartToPolar(imgs[0], imgs[1], magnitude, phase);

   // Shift quadrants for viewability
   dftshift(magnitude);

   // Logarithm of magnitude
   cv::Mat_<float> magnitudel;

   // Output image for HPF
   cv::Mat_<float> imgout;

   if(highpass) {
      // High-pass filter: remove the low frequency parts in the middle of the spectrum
      const int sizef = 500;
      magnitude(cv::Rect(magnitude.cols/2-sizef/2, magnitude.rows/2-sizef/2, sizef, sizef)) = 0.0f;
			magnitude(cv::Rect(magnitude.cols/2 -50, magnitude.rows/2 - 50, 50, 50)) = 400.0f;
      // Take logarithm of modified magnitude
      magnitudel = magnitude + 1.0f;
      cv::log(magnitudel, magnitudel);

      // Shift back quadrants of the spectrum
      dftshift(magnitude);

      // Compute complex DFT output from magnitude/phase
      cv::polarToCart(magnitude, phase, imgs[0], imgs[1]);

      // Merge DFT into one image and restore
      cv::merge(imgs, 2, img_dft);
      cv::dft(img_dft, imgout, cv::DFT_INVERSE + cv::DFT_SCALE + cv::DFT_REAL_OUTPUT);

      //Cut away the borders
      imgout = imgout(cv::Rect(0,0,imgCols,imgRows));
   } else {
      // Take logarithm of magnitude
      magnitudel = magnitude + 1.0f;
      cv::log(magnitudel, magnitudel);
   }


   // Show
   cv::normalize(img, img, 0.0, 1.0, CV_MINMAX);
   cv::normalize(magnitudel, magnitudel, 0.0, 1.0, CV_MINMAX);
   cv::normalize(phase, phase, 0.0, 1.0, CV_MINMAX);
	 namedWindow("Input",WINDOW_NORMAL);
	 namedWindow("Magnitude",WINDOW_NORMAL);
	 namedWindow("Output",WINDOW_NORMAL);
   cv::imshow("Input", img);
   cv::imshow("Magnitude", magnitudel);
   if(highpass) {
      cv::normalize(imgout, imgout, 0.0, 1.0, CV_MINMAX);
      cv::imshow("Output", imgout);
   }
   cv::waitKey();
}

cv::Mat BHPF(double d0, double n, int wy, int wx, int cx, int cy)
{
	cv::Mat_<cv::Vec2f> hpf(wy, wx);
	for(int y = 0; y < wy; ++y) {
		for(int x = 0; x < wx; ++x) {
			// Real part
			for(int i = 0; i < 3 ; i++)
			{
				const double d = std::sqrt( double((x-cx)*(x-cx)) + double((y-cy)*(y-cy)) );
				const double d_k = std::sqrt(pow(x-cx-(cx+100),2.0) + pow(y-cy-(cy+100),2.0));
				const double d_mk = std::sqrt(pow(x-cx+(cx+0),2.0) + pow(y-cy+(cy+0),2.0));
				if(d==0) // Avoid division by zero
					hpf(y,x)[0] = 0;
				else
					//	hpf(y,x)[0] = 1.0 / (1.0 + std::pow(d0/d, 2.0*n));
					hpf(y,x)[0] *= (1.0/(1+pow((d0/d_k),2.0*n)))*(1.0/(1+pow((d0/d_mk),2.0*n)));
					// Imaginary part
					hpf(y,x)[1] = 0;
			}
		}
	}
    return hpf;
}

void create_butterworth_lowpass_filter(Mat &dft_Filter, int D, int n)
{
	Mat tmp = Mat(dft_Filter.rows, dft_Filter.cols, CV_32F);

	Point centre = Point(dft_Filter.rows / 2, dft_Filter.cols / 2);
	double radius;

	// based on the forumla in the IP notes (p. 130 of 2009/10 version)
	// see also HIPR2 on-line

	for(int i = 0; i < dft_Filter.rows; i++)
	{
		for(int j = 0; j < dft_Filter.cols; j++)
		{
			radius = (double) sqrt(pow((i - centre.x), 2.0) + pow((double) (j - centre.y), 2.0));
			tmp.at<float>(i,j) = (float)
						( 1 / (1 + pow((double) (radius /  D), (double) (2 * n))));
		}
	}

    Mat toMerge[] = {tmp, tmp};
	merge(toMerge, 2, dft_Filter);
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
	cout << "out" << endl;
}

void applyFilter(Mat_<float> src, Mat_<float> output)
{
	int wxOrig = src.cols;
  int wyOrig = src.rows;

	int m = cv::getOptimalDFTSize(2*wyOrig);
	int n = cv::getOptimalDFTSize(2*wxOrig);

  copyMakeBorder(src, src, 0, m - wyOrig, 0, n - wxOrig, cv::BORDER_CONSTANT, cv::Scalar::all(0));

	const int wx = src.cols, wy = src.rows;
  const int cx = wx/2, cy = wy/2;

	std::cout << wxOrig << " " << wyOrig << std::endl;
	std::cout << wx << " " << wy << std::endl;
	std::cout << cx << " " << cy << std::endl;

	cv::Mat_<float> imgs[] = {src.clone(), cv::Mat_<float>::zeros(wy, wx)};
  cv::Mat_<cv::Vec2f> img_dft;
  cv::merge(imgs, 2, img_dft);
  cv::dft(img_dft, img_dft);

	dftshift(img_dft);
	cout << "helo " << endl;

  //cv::Mat hpf = BHPF(3000, 4, wy, wx, cx, cy);
	Mat filter = src.clone();
	create_butterworth_lowpass_filter(filter,300,7);
	//cv::mulSpectrums(hpf, img_dft, img_dft, cv::DFT_ROWS);
	cv::mulSpectrums(img_dft, filter, img_dft, cv::DFT_ROWS);

	dftshift(img_dft);

	Mat mag = create_spectrum_magnitude_display(img_dft, true);

  cv::idft(img_dft, img_dft); //the result is a 2 channel image
	split(img_dft, imgs);
	normalize(imgs[0], output, 0, 1, CV_MINMAX);

	cv::Mat_<float> croppedOutput(output,cv::Rect(0,0,wxOrig,wyOrig));

	split(filter, imgs);
	Mat filterOutput;
	normalize(imgs[0],filterOutput,0,1,CV_MINMAX);
	namedWindow("Low-pass filtered input",WINDOW_NORMAL);
	namedWindow("Input",WINDOW_NORMAL);
	namedWindow("filter",WINDOW_NORMAL);
	namedWindow("output", WINDOW_NORMAL);
	cv::imshow("Input", src);
	cv::imshow("Low-pass filtered input", croppedOutput);
	cv::imshow("filter", filterOutput);
	cv::imshow("output", output);
	imwrite("/home/student/ROVI/VisMand1/build-vis_man_1-Desktop-Debug/output/outm.jpg",croppedOutput);
	cout << "lol" << endl;
	cv::waitKey(0);

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
