#include "cv.h"
#include "highgui.h"

int main() {


CvRect rect;
IplImage* frame=cvLoadImage("lena.jpg",1);


//rect.x = 100;
//rect.y = 100;
//rect.width = 300;
//rect.height = 400;
rect = cvRect( 200, 200, 200, 200 );


cvSetImageROI(frame, rect );
IplImage *dst = cvCreateImage( cvGetSize( frame ), frame->depth, 1 );

cvNamedWindow("My Window");
cvNamedWindow("111");
cvCvtColor( frame, dst, CV_BGR2GRAY);

cvResetImageROI( frame );

cvShowImage("My Window",dst);
cvShowImage("111",frame);
cvMoveWindow("111",400,400);

cvSaveImage("C:/Users/Terry/Desktop/part_ROI_img.jpg",dst);

cvWaitKey();
cvReleaseImage( &frame );
cvReleaseImage( &dst );

cvDestroyWindow("My Window");
cvDestroyWindow("111");
return 0;
}