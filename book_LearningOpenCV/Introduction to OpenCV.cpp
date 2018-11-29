/*
1: First Program—Display a Picture  16
2: Second Program—AVI Video  18
3: Moving Around  19
A Simple Transformation  22
A Not-So-Simple Transformation  24
Input from a Camera  26
Writing to an AVI File  27
Onward  29
Exercises  29
*/
// 1读取图片----------------------------------------------------------------------------------------
#include<iostream>

#include<highgui.h>

using namespace cv;

int main()
{
	IplImage* img = cvLoadImage("em.jpg");
	cvNamedWindow("example1", CV_WINDOW_AUTOSIZE);
	cvShowImage("example1", img);
	cvWaitKey(0);
	cvReleaseImage(&img);
	cvDestroyWindow("example1");
	return 0;
}

// 2读取视频----------------------------------------------------------------------------------------


// 3----------------------------------------------------------------------------------------
