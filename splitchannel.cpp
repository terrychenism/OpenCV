#include "highgui.h"
#include "cv.h"
#include"iostream"
int main( int argc, char * grgv[] )
{
 IplImage *src = cvLoadImage( "image1.jpg", 1);
 //IplImage *repeat_img;
// std::cout<<src->depth<<std::endl;
// cvFlip(src,NULL,-1);
 IplImage *dst;
 IplImage *dst1;
 IplImage *dst2;
 IplImage *dst3;
 dst1 = cvCreateImage(cvSize(src->width, src->height), IPL_DEPTH_8U, 1);
 dst2 = cvCreateImage(cvSize(src->width, src->height), IPL_DEPTH_8U, 1);
 dst3 = cvCreateImage(cvSize(src->width, src->height), IPL_DEPTH_8U, 1);
 dst = cvCreateImage(cvSize(src->width, src->height), IPL_DEPTH_8U, 3);
 cvSplit(src, dst1, dst2, dst3, 0);//分离RGB通道，分别得到BGR的单通道图像
 cvMerge(dst1, dst2, dst3, 0, dst);//逆运算，将三通道图像融合得到彩色图像

 cvNamedWindow("dst1",1);
 cvShowImage("dst1",dst1);
 cvNamedWindow("dst2",1);
 cvShowImage("dst2",dst2);
 cvNamedWindow("dst3",1);
 cvShowImage("dst3",dst3);
 cvNamedWindow("dst",1);
 cvShowImage("dst",dst);
 cvMoveWindow("dst1",100,100);
 cvMoveWindow("dst2",200,200);
 cvMoveWindow("dst3",300,300);
 cvWaitKey(0);
 //cvReleaseImage(&src);
 cvReleaseImage(&dst1);
 cvReleaseImage(&dst2);
 cvReleaseImage(&dst3);
 cvReleaseImage(&dst);
 return 0;
}