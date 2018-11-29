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
//#include "stdafx.h"
#include<iostream>
#include<highgui.h>
using namespace cv;
int main()
{
	//载入一张图片，返回指针
	IplImage* img = cvLoadImage("em.jpg");
	//建立一个名字为example1的窗口，窗口大小根据内容缩放
	cvNamedWindow("example1", CV_WINDOW_AUTOSIZE);
	//在已经建立的窗口里显示图片
	cvShowImage("example1", img);
	//无限等待键盘输入
	cvWaitKey(0);
	//释放图片内存
	cvReleaseImage(&img);
	//释放所有内存
	cvDestroyWindow("example1");
	return 0;
}

// 2读取视频----------------------------------------------------------------------------------------
//#include "stdafx.h"
#include<iostream>
#include<highgui.h>
using namespace cv;
int main()
{
	cvNamedWindow("example2", CV_WINDOW_AUTOSIZE);
	CvCapture* capture = cvCreateFileCapture("tree.avi");
	IplImage* frame;
	while (1) {
		frame = cvQueryFrame(capture);
		if (!frame)break;
		cvShowImage("example2", frame);
		char c = cvWaitKey(33);
		if (c == 27)break;
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("example2");
	return 0;
}

// 3添加进度条----------------------------------------------------------------------------------------
#include "stdafx.h"
#include<iostream>
#include<highgui.h>
#include<cv.h>

//进度条位置
int g_slider_position = 0;
//callback需要使用捕获到的对象，所以先建立这个全局变量g_capture
CvCapture* g_capture = NULL;
void onTrackbarSlide(int pos) {
	cvSetCaptureProperty(g_capture, CV_CAP_PROP_POS_FRAMES, pos);
}

int main()
{
	cvNamedWindow("example3", CV_WINDOW_AUTOSIZE);
	g_capture = cvCreateFileCapture("harmony.avi");
	//得到视频一共有多少帧
	int frames = (int)cvGetCaptureProperty(g_capture, CV_CAP_PROP_FRAME_COUNT);
	//有时候无法得到视频帧数，所以这时候不显示进度条
	if (frames != 0) {
		//给进度条一个标签，也就是名字position；指定进度条所在窗口为example3；绑定进度条的位置；进度条最大值；callback
		cvCreateTrackbar("position", "example3", &g_slider_position, frames, onTrackbarSlide);
	}
	IplImage* frame;
	while (1) {
		frame = cvQueryFrame(g_capture);
		if (!frame)break;
		cvShowImage("example3", frame);
		char c = cvWaitKey(33);
		if (c == 27)break;
	}
	cvReleaseCapture(&g_capture);
	cvDestroyWindow("example3");

	return 0;
}

// 4----------------------------------------------------------------------------------------

// 5----------------------------------------------------------------------------------------

// 6----------------------------------------------------------------------------------------

// 7----------------------------------------------------------------------------------------
