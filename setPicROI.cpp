#include "cv.h"
#include "highgui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>
using namespace std;
int setROI(CvPoint p1,CvPoint p2);
static CvMemStorage* storage = 0;
static CvHaarClassifierCascade* cascade = 0;
CvRect *r;
void detect_and_draw( IplImage* image );

const char* cascade_name ="haarcascade_frontalface_alt2.xml";
/* "haarcascade_profileface.xml";*/

int main()
{
	CvCapture* capture = 0;
	
	cascade = (CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0 );

	if( !cascade )
	{
		fprintf( stderr, "ERROR: Could not load classifier cascade/n" );
		//fprintf( stderr,
			//"Usage: facedetect --cascade=/"<cascade_path>"/[filename|camera_index]/n" );
		return -1;
	}
	storage = cvCreateMemStorage(0);


	cvNamedWindow( "result", 1 );

	
	//const char* filename = "C:/Users/Terry/Desktop/messi.jpg";
	const char* filename = "lena.jpg";
	IplImage* image = cvLoadImage(filename);

	if( image )
	{
		detect_and_draw( image );
		cvWaitKey(0);
		cvReleaseImage( &image );
	}

	cvDestroyWindow("result");
	cvWaitKey(0);
	return 0;
}

void detect_and_draw( IplImage* img )
{


	static CvScalar colors[] = 
	{
		{{0,0,255}},
		{{0,128,255}},
		{{0,255,255}},
		{{0,255,0}},
		{{255,128,0}},
		{{255,255,0}},
		{{255,0,0}},
		{{255,0,255}}
	};

	double scale = 2.0;
	IplImage* gray = cvCreateImage( cvSize(img->width,img->height), 8, 1 );
	IplImage* small_img = cvCreateImage( cvSize( cvRound (img->width/scale),
		cvRound (img->height/scale)),
		8, 1 );
	int i;

	cvCvtColor( img, gray, CV_BGR2GRAY );
	cvResize( gray, small_img, CV_INTER_LINEAR );
	cvEqualizeHist( small_img, small_img );
	cvClearMemStorage( storage );

	if( cascade )
	{
		double t = (double)cvGetTickCount();
		CvSeq* faces = cvHaarDetectObjects( small_img, cascade, storage,
			1.1, 2, 0/*CV_HAAR_DO_CANNY_PRUNING*/,
			cvSize(30, 30) );
		t = (double)cvGetTickCount() - t;
		printf( "detection time = %gms/n", t/((double)cvGetTickFrequency()*1000.) );
		/*for( i = 0; i < (faces ? faces->total : 0); i++ )
		{
			CvRect* r = (CvRect*)cvGetSeqElem( faces, i );
			CvPoint center;
			int radius;
			center.x = cvRound((r->x + r->width*0.5)*scale);
			center.y = cvRound((r->y + r->height*0.5)*scale);
			radius = cvRound((r->width + r->height)*0.25*scale);
			cvCircle( img, center, radius, colors[i%8], 3, 8, 0 );
		}*/
	
		for (i = 0; i < (faces ? faces->total : 0); i++)
   {
     //返回索引所指定的元素指针
	 r = (CvRect*)cvGetSeqElem(faces, i); 
     //用矩形
     //确定两个点来确定人脸位置因为用cvRetangle
     CvPoint pt1, pt2;
     //找到画矩形的两个点
     pt1.x = r->x*scale;
     pt2.x = (r->x+r->width)*int(scale);
     pt1.y = r->y*scale;
     pt2.y = (r->y+r->height)*int(scale);
	 setROI(pt1,pt2);
     //画出矩形
     cvRectangle( img, pt1, pt2, colors[i%8], 3, 8, 0 );

   }
	}
	const char* filename2 = "C:/Users/Terry/Desktop/test3.jpg";
	cvShowImage( "result", img );
	cvSaveImage( filename2, img);   //保存图片
	cvReleaseImage( &gray );
	cvReleaseImage( &small_img );
} 

int setROI(CvPoint p1,CvPoint p2) {


	CvRect rect;
	IplImage* frame=cvLoadImage("lena.jpg",1);



	//rect = cvRect( p1.x, p1.y, p2.x, p2.y);

	rect = cvRect(p1.x,p1.y,r->width*2,r->height*2);

	cvSetImageROI(frame, rect );
	//IplImage *dst = cvCreateImage( cvGetSize( frame ), frame->depth, 0 );
	IplImage *dst=cvCloneImage(frame);

	cvNamedWindow("My Window",CV_WINDOW_AUTOSIZE);


	cvShowImage("My Window",dst);
	//cvShowImage("111",frame);
	//cvMoveWindow("111",400,400);

	cvSaveImage("C:/Users/hzhou/Desktop/part_ROI_img.jpg",dst);

	cvWaitKey();
	//cvReleaseImage( &frame );
	cvReleaseImage( &dst );

	cvDestroyWindow("My Window");
	//cvDestroyWindow("111");
	return 0;
}
