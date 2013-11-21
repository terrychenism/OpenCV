#include "cv.h"
#include "highgui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h> //���ڷ���ʽ���
#include <math.h>
#include <float.h>//<float.h>��<limits.h>һ���Ƕ���߽�ֵ��,<float.h>������Ǹ������ı߽�ֵ
#include <limits.h>
#include <time.h>
#include <ctype.h>//�ڵ����ַ�����ʱ����Դ�ļ��а�����ͷ�ļ�

#ifdef _EiC
#define WIN32
#endif


static CvMemStorage *storage = 0;
static CvHaarClassifierCascade *cascade = 0;//harr �������������ڲ���ʶ��ʽ

void detect_and_draw( IplImage *image);

const char *cascade_name = "haarcascade_frontalface_alt2.xml";

int main()
{
 CvCapture *capture = 0;
 IplImage *frame, *frame_copy = 0;
 const char *input_name;
 cascade = (CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0);
 if ( !cascade )
 {
  fprintf( stderr, "ERROR:û���ļ�\n");
  return -1;
 }
 storage = cvCreateMemStorage(0);//�����ڴ��
 capture = cvCaptureFromCAM(0);//��ȡ����ͷ
 cvNamedWindow( "����ʶ��", 1);//������ʽ������

 if (capture)
 {
  //ѭ��������ͷ����ͼƬ���м��
  while(1)
  {
      //������ͷ������Ƶ�ļ���ץȡ֡ 
      //����cvQueryFrame������ͷ�����ļ���ץȡһ֡��Ȼ���ѹ��������һ֡��
      //������������Ǻ���cvGrabFrame�ͺ���cvRetrieveFrame��һ����õ���ϡ����ص�ͼ�񲻿��Ա��û��ͷŻ����޸ġ�
   if (!cvGrabFrame( capture )){
         break;
   }
      frame = cvRetrieveFrame( capture ); //�����cvGrabFrame����ץȡ��ͼƬ
      if (!frame){break;}   
      if (!frame_copy){
    frame_copy = cvCreateImage(cvSize(frame->width,frame->height),IPL_DEPTH_8U,frame->nChannels);
   }
      //ͼ��ԭ����������Ͻ� (img->origin=IPL_ORIGIN_TL)���������½�(img->origin=IPL_ORIGIN_BL)
      if (frame->origin == IPL_ORIGIN_TL){
        cvCopy (frame, frame_copy, 0);
   }
      else{
     // ��X-�ᷭת, flip_mode > 0 (�� 1) ��Y-�ᷭת�� flip_mode < 0 (�� -1) ��X-���Y-�ᷭת.������Ĺ�ʽ 
     //����cvFlip �����ַ�ʽ֮һ��ת���� (�к����±�����0Ϊ�����): 
        
		  cvFlip (frame, frame_copy, 0);//��תͼ��
   }
      detect_and_draw( frame_copy ); // ��Ⲣ�ұ�ʶ����
      if(cvWaitKey (10) >= 0)
      break;
  }
  
  //�ͷ�ָ��
  cvReleaseImage( &frame_copy );
  cvReleaseCapture( &capture);
 }
 
  cvDestroyWindow("����ʶ��");
  return 0;
}


void detect_and_draw(IplImage *img) //���ͻ��������ĺ�����
{
 //�����ɫ
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
 
   double scale = 1.3;
   IplImage *gray = cvCreateImage(cvSize(img->width,img->height), 8, 1);//�Ҷ�ͼ��
   IplImage *small_img = cvCreateImage(cvSize(cvRound(img->width/scale),cvRound(img->height/scale)),8, 1);
   int i;
   cvCvtColor(img, gray, CV_BGR2GRAY);//������Ĳ�ɫͼ��ת��Ϊ�Ҷ�ͼ��
   cvResize(gray, small_img,CV_INTER_LINEAR);//��С��ɫͼƬ
   cvEqualizeHist(small_img, small_img);//�Ҷ�ͼ��ֱ��ͼ���⻯
   cvClearMemStorage(storage);//�ͷ��ڴ��

   if (cascade)
   {
   double t = (double)cvGetTickCount();//��ȷ����������ִ��ʱ��
   //��Ŀ��ͼ��small_img�м�������
   CvSeq *faces = cvHaarDetectObjects(small_img, cascade,storage,1.1,2,0,cvSize(30, 30));
   t = (double)cvGetTickCount() - t; //�����⵽��������ʱ��
   printf("�������ʱ�� = %gms\n",t/((double)cvGetTickFrequency()*1000.));//��ӡ����Ļ

   //������⵽���������(�ɼ�⵽�������)
   for (i = 0; i < (faces ? faces->total : 0); i++)
   {
     //����������ָ����Ԫ��ָ��
     CvRect *r = (CvRect*)cvGetSeqElem(faces, i); 
     //�þ���
     //ȷ����������ȷ������λ����Ϊ��cvRetangle
     CvPoint pt1, pt2;
     //�ҵ������ε�������
     pt1.x = r->x*scale;
     pt2.x = (r->x+r->width)*scale;
     pt1.y = r->y*scale;
     pt2.y = (r->y+r->height)*scale;
     //��������
     cvRectangle( img, pt1, pt2, colors[i%8], 3, 8, 0 );
   }

   }
  cvShowImage("����ʶ��",img);
  cvReleaseImage(&gray);
  cvReleaseImage(&small_img);
}