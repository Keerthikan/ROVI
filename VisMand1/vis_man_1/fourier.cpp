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
	magnitude.convertTo(mgnitude,CV_8UC3,255.0);
	cout << "converted" << endl;
	imwrite("/home/student/ROVI/VisMand1/build-vis_man_1-Desktop-Debug/output/imgssuft.png",magnitude);
	waitKey(0);
	cout << "out" << endl;
}


void applyFilter(const Mat_<float> src, Mat_<float> output,int kernel , int order)
{
		Mat_<float> temp = src;
		int wxOrig = src.cols;
	  int wyOrig = src.rows;

		int m = cv::getOptimalDFTSize(2*wyOrig);
		int n = cv::getOptimalDFTSize(2*wxOrig);

	  copyMakeBorder(temp, temp, 0, m - wyOrig, 0, n - wxOrig, cv::BORDER_CONSTANT, cv::Scalar::all(0));

		const int wx = temp.cols, wy = temp.rows;
	  const int cx = wx/2, cy = wy/2;

		std::cout << wxOrig << " " << wyOrig << std::endl;
		std::cout << wx << " " << wy << std::endl;
		std::cout << cx << " " << cy << std::endl;

		cv::Mat_<float> imgs[] = {temp.clone(), cv::Mat_<float>::zeros(wy, wx)};
	  cv::Mat_<cv::Vec2f> img_dft;
	  cv::merge(imgs, 2, img_dft);
	  cv::dft(img_dft, img_dft);

		dftshift(img_dft);
		cout << "helo " << endl;

	  //cv::Mat hpf = BHPF(3000, 4, wy, wx, cx, cy);
		Mat filter = temp.clone();
		create_butterworth_lowpass_filter(filter,kernel,order);
		//cv::mulSpectrums(hpf, img_dft, img_dft, cv::DFT_ROWS);
		cv::mulSpectrums(img_dft, filter, img_dft, cv::DFT_ROWS);

		dftshift(img_dft);
		cout << "helo" << endl;
		Mat mag = create_spectrum_magnitude_display(img_dft, true);

	  cv::idft(img_dft, img_dft); //the result is a 2 channel image
		split(img_dft, imgs);
		normalize(imgs[0], output, 0, 1, CV_MINMAX);

		cv::Mat_<float> croppedOutput(output,cv::Rect(0,0,wxOrig,wyOrig));
		cout << "helo" << endl;
		split(filter, imgs);
		Mat filterOutput;
		normalize(imgs[0],filterOutput,0,1,CV_MINMAX);
		Mat  input = src.clone();

		normalize(input,input, 0,1,CV_MINMAX);
		namedWindow("Low-pass filtered input",0);
		resizeWindow("Low-pass filtered input",450,700);
		moveWindow("Low-pass filtered input", 100,100);

		namedWindow("Input",WINDOW_NORMAL);

		namedWindow("filter",0);
		resizeWindow("filter",450,700);
		moveWindow("filter", 550,100);

		namedWindow("output", WINDOW_NORMAL);

		cv::imshow("Input", input);

		cv::imshow("Low-pass filtered input", croppedOutput);

		cv::imshow("filter", filterOutput);

		cv::imshow("output", output);
		cout << "fft of output" << endl;
		//fft2(output);
		//cout << "order: " << order << " cutFrequency: " << cut << endl;
		imwrite("/home/student/ROVI/VisMand1/build-vis_man_1-Desktop-Debug/output/imgssut.png", input);
		//imwrite("/home/student/ROVI/VisMand1/build-vis_man_1-Desktop-Debug/output/outm.png",output);
		cv::FileStorage fs("/home/student/ROVI/VisMand1/build-vis_man_1-Desktop-Debug/output/outm.yml",cv::FileStorage::WRITE);
		//imwrite("/home/student/ROVI/VisMand1/build-vis_man_1-Desktop-Debug/output/outm.png",croppedOutput);
		fs <<"ImageId"<< input;
		//cout << "lol" << endl;
		cv::waitKey(0);
		cout << "Destroy" << endl;
		destroyAllWindows();

}
