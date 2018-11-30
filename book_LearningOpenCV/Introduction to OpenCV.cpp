/*
1: First Program—Display a Picture  16
2: Second Program—AVI Video  18
3: Moving Around滚动条  19
4: 在图片上画矩形
5:
6:
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

// 4在图片上画矩形----------------------------------------------------------------------------------------
#include "stdafx.h"
#include<iostream>
#include<highgui.h>
#include<cv.h>

int g_slider_position = 0;
CvCapture* g_capture = NULL;

void onTrackbarSlide(int pos) {
	cvSetCaptureProperty(g_capture, CV_CAP_PROP_POS_FRAMES, pos);
}

void my_mouse_callback(int event,int x,int y,int flags,void* param);

CvRect box;
bool drawing_box = false;

void draw_box(IplImage* img, CvRect rect) {
	cvRectangle(img, cvPoint(box.x, box.y), cvPoint(box.x + box.width, box.y + box.height), cvScalar(0xff, 0x00, 0x00));
}


int main()
{
	IplImage* image = cvLoadImage("em.jpg");
	IplImage* temp = cvCloneImage(image);
	cvNamedWindow("Box example");

	cvSetMouseCallback("Box example", my_mouse_callback, (void*)image);
	while (1) {
		cvCopy(image, temp);
		//cvCopyImage(image, temp);
		if (drawing_box)draw_box(temp, box);
		cvShowImage("Box example", temp);

		if (cvWaitKey(15) == 27)break;
	}
	cvReleaseImage(&image);
	cvReleaseImage(&temp);
	cvDestroyWindow("Box example");

	return 0;
}
void my_mouse_callback(int event, int x, int y, int flags, void* param) {
	IplImage* image = (IplImage*)param;
	switch (event)
	{
		case CV_EVENT_MOUSEMOVE: {
			if (drawing_box) {
				box.width = x - box.x;
				box.height = y - box.y;
			}
		}
		break;
		case CV_EVENT_LBUTTONDOWN: {
			drawing_box = true;
			box = CvRect(x, y, 0, 0);
		}
		break;
		case CV_EVENT_LBUTTONUP: {
			drawing_box = false;
			if (box.width < 0) {
				box.x += box.height;
				box.x *= -1;
			}
			if (box.height < 0) {
				box.y += box.height;
				box.height *= -1;
			}
			draw_box(image, box);
		}
		break;
	}
}

// 5----------------------------------------------------------------------------------------

// 6----------------------------------------------------------------------------------------

// 7----------------------------------------------------------------------------------------
