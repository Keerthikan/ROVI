#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <string>     // std::string, std::to_string
#include <iostream>
#include <math.h>
#include<fstream>
#include <stdio.h>
using namespace std;
using namespace cv;

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
     Point *p   = (Point*) userdata;
     	    
     if  ( event == EVENT_LBUTTONDOWN )
     {
          cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	p->x = x;
        p->y = y;
	destroyWindow("My Window");
     }
     
}



int main( int argc, char** argv )
{
     fstream myReadFile;
     myReadFile.open("/home/student/Arbejde/crop/data2/file.txt");
     
     if(!myReadFile.is_open())
     {
	cout << "list of files not open!" << endl;
	return -1;
     }

     if(myReadFile.eof())
     {
	cout << "end of file reached" << endl;
	return -1;
     }

     
     for(string file_name; std::getline(myReadFile,file_name);)
     {
	cout << "Openening: " << file_name << endl;
     	Point p;
   	//namedWindow("My Window", WINDOW_NORMAL);
     	Mat img = imread("/home/student/Arbejde/crop/data2/"+file_name);
    	Mat rotated;

     	if ( img.empty() ) 
     	{ 
     	     cout << "Error loading the image" << endl;
    	      return -1; 
     	}

    	//imshow("My Window", img);
     	//setMouseCallback("My Window", CallBackFunc, &p);
     	//waitKey(0);
     	//int width = 500;
     	//int height = 500;
     	//Rect ROI (p.x-width/2,p.y-height/2,width,height);
     	//cropped = img(ROI);
	transpose(img,rotated);
	flip(img,rotated,1);
     	imwrite("/home/student/Arbejde/crop/CW_"+file_name,rotated);
	transpose(img,rotated);
	flip(img,rotated,1);
     	imwrite("/home/student/Arbejde/crop/CCW_"+file_name,rotated);
	flip(img,rotated,-1);
     	imwrite("/home/student/Arbejde/crop/flip_"+file_name,rotated);
    	//waitKey(0);
    }	
	cout << "done" << endl; 
}
