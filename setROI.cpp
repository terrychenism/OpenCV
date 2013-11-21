#include "highgui.h"
#include "cv.h"
#include <iostream>
using namespace std;
void main()
{
    IplImage *src=cvLoadImage("lena.jpg",-1);//����ͼ��
    IplImage *dst;
    CvRect ROI_rect_src;
    CvRect ROI_rect_dst;
    cvNamedWindow("src",CV_WINDOW_AUTOSIZE);
    cvMoveWindow("src",200,200);
    cvShowImage("src",src);//���δ��λROI��ͼ��
    cvWaitKey(0);
    
    ROI_rect_src.x=src->width/2;
    ROI_rect_src.y=src->height/2;
    ROI_rect_src.width=200;
    ROI_rect_src.height=200;
    cvSetImageROI(src,ROI_rect_src);
    cout<<"���ͼ������"<<endl;
    cout<<(src->roi->xOffset)<<""<<(src->roi->yOffset)<<endl;
    cout<<(src->roi->width)<<""<<(src->roi->height)<<endl;
    cvShowImage("src",src);//����趨ROI�Ժ��ͼ��

    dst=cvCloneImage(src);//���Ƴ�ROI�����ͼ��
    ROI_rect_dst=cvGetImageROI(dst);//�õ�ͼ���ROI����
    cout<<"���Ŀ��ͼ���ROI"<<endl;
    cout<<ROI_rect_dst.x<<" "<<ROI_rect_dst.y<<endl;
    cout<<ROI_rect_dst.width<<" "<<ROI_rect_dst.height<<endl;
    cvNamedWindow("dst",CV_WINDOW_AUTOSIZE);
    cvMoveWindow("dst",400,200);
    cvShowImage("dst",dst);
    cvWaitKey(0);

    cvResetImageROI(dst);//�ͷ�Ŀ��ͼ���ROI
    cvShowImage("dst",dst);
    cvWaitKey(0);
    cvReleaseImage(&src);
    cvReleaseImage(&dst);
}