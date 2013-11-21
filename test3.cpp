////////////////////////////////////////////////////////////////////////
//
// test3.cpp
//
// �ó���ʵ����Ƶ��ͼƬ���໥ת��.
// Image_to_video()������һ��ͼƬ�ϳ�AVI��Ƶ�ļ�.
// Video_to_image()������AVI��Ƶ�ļ����룬��ÿһ֡�洢Ϊjpg�ļ�.
//
////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>
#define NUM_FRAME 1500 //ֻ����ǰ300֡��������Ƶ֡�����޸�

void Video_to_image(char* filename)
{
printf("------------- video to image ... ----------------\n");
//��ʼ��һ����Ƶ�ļ���׽��
CvCapture* capture = cvCaptureFromAVI(filename);
//��ȡ��Ƶ��Ϣ
cvQueryFrame(capture);
int frameH    = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
int frameW    = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
int fps       = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
int numFrames = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);
printf("\tvideo height : %d\n\tvideo width : %d\n\tfps : %d\n\tframe numbers : %d\n", frameH, frameW, fps, numFrames);
//����ͳ�ʼ������
int i = 0;
IplImage* img = 0;
char image_name[13];

cvNamedWindow( "mainWin", CV_WINDOW_AUTOSIZE );
//��ȡ����ʾ
while(1)
{
  
   img = cvQueryFrame(capture); //��ȡһ֡ͼƬ
   cvShowImage( "mainWin", img ); //������ʾ
   char key = cvWaitKey(20);
  
   //sprintf(image_name, "%s%d%s", "image", ++i, ".jpg");//�����ͼƬ��
  sprintf(image_name, "%s%d%s", "", ++i, ".jpg");//�����ͼƬ��
   cvSaveImage( image_name, img);   //����һ֡ͼƬ

   if(i == NUM_FRAME) break;
}
cvReleaseCapture(&capture);
cvDestroyWindow("mainWin");
}
 
void Image_to_video()
{
int i = 0;
IplImage* img = 0;
char image_name[13];
printf("------------- image to video ... ----------------\n");
//��ʼ����Ƶ��д������������ʵ����Ƶ�ļ��޸�
CvVideoWriter *writer = 0;
int isColor = 1;
int fps     = 30; // or 25
int frameW = 400; // 744 for firewire cameras
int frameH = 240; // 480 for firewire cameras
writer=cvCreateVideoWriter("out.avi",CV_FOURCC('X','V','I','D'),fps,cvSize(frameW,frameH),isColor);
printf("\tvideo height : %d\n\tvideo width : %d\n\tfps : %d\n", frameH, frameW, fps);
//��������
cvNamedWindow( "mainWin", CV_WINDOW_AUTOSIZE );
while(i<NUM_FRAME)
{
   sprintf(image_name, "%s%d%s", "image", ++i, ".jpg");
   img = cvLoadImage(image_name);
   if(!img)
   {
    printf("Could not load image file...\n");
    exit(0);
   }
   cvShowImage("mainWin", img);
   char key = cvWaitKey(20);
   cvWriteFrame(writer, img);
}
cvReleaseVideoWriter(&writer);
cvDestroyWindow("mainWin");
}

int main(int argc, char *argv[])
{
char filename[20] = "VideoTest.avi";
Video_to_image(filename); //��ƵתͼƬ
Image_to_video();    //ͼƬת��Ƶ
return 0;
}