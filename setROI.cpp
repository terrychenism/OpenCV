#include "highgui.h"
#include "cv.h"
#include <iostream>
using namespace std;
void main()
{
    IplImage *src=cvLoadImage("lena.jpg",-1);//读入图像
    IplImage *dst;
    CvRect ROI_rect_src;
    CvRect ROI_rect_dst;
    cvNamedWindow("src",CV_WINDOW_AUTOSIZE);
    cvMoveWindow("src",200,200);
    cvShowImage("src",src);//输出未定位ROI的图像
    cvWaitKey(0);
    
    ROI_rect_src.x=src->width/2;
    ROI_rect_src.y=src->height/2;
    ROI_rect_src.width=200;
    ROI_rect_src.height=200;
    cvSetImageROI(src,ROI_rect_src);
    cout<<"输出图像区域"<<endl;
    cout<<(src->roi->xOffset)<<""<<(src->roi->yOffset)<<endl;
    cout<<(src->roi->width)<<""<<(src->roi->height)<<endl;
    cvShowImage("src",src);//输出设定ROI以后的图像

    dst=cvCloneImage(src);//复制出ROI区域的图像
    ROI_rect_dst=cvGetImageROI(dst);//得到图像的ROI区域
    cout<<"输出目标图像的ROI"<<endl;
    cout<<ROI_rect_dst.x<<" "<<ROI_rect_dst.y<<endl;
    cout<<ROI_rect_dst.width<<" "<<ROI_rect_dst.height<<endl;
    cvNamedWindow("dst",CV_WINDOW_AUTOSIZE);
    cvMoveWindow("dst",400,200);
    cvShowImage("dst",dst);
    cvWaitKey(0);

    cvResetImageROI(dst);//释放目标图像的ROI
    cvShowImage("dst",dst);
    cvWaitKey(0);
    cvReleaseImage(&src);
    cvReleaseImage(&dst);
}