#include "cv.h"
#include "highgui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h> //用于防御式编程
#include <math.h>
#include <float.h>//<float.h>与<limits.h>一样是定义边界值的,<float.h>定义的是浮点数的边界值
#include <limits.h>
#include <time.h>
#include <ctype.h>//在调用字符函数时，在源文件中包含的头文件

#ifdef _EiC
#define WIN32
#endif


static CvMemStorage *storage = 0;
static CvHaarClassifierCascade *cascade = 0;//harr 分类器级联的内部标识形式

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
  fprintf( stderr, "ERROR:没有文件\n");
  return -1;
 }
 storage = cvCreateMemStorage(0);//创建内存块
 capture = cvCaptureFromCAM(0);//获取摄像头
 cvNamedWindow( "人脸识别", 1);//创建格式化窗口

 if (capture)
 {
  //循环从摄像头读出图片进行检测
  while(1)
  {
      //从摄像头或者视频文件中抓取帧 
      //函数cvQueryFrame从摄像头或者文件中抓取一帧，然后解压并返回这一帧。
      //这个函数仅仅是函数cvGrabFrame和函数cvRetrieveFrame在一起调用的组合。返回的图像不可以被用户释放或者修改。
   if (!cvGrabFrame( capture )){
         break;
   }
      frame = cvRetrieveFrame( capture ); //获得由cvGrabFrame函数抓取的图片
      if (!frame){break;}   
      if (!frame_copy){
    frame_copy = cvCreateImage(cvSize(frame->width,frame->height),IPL_DEPTH_8U,frame->nChannels);
   }
      //图像原点或者是左上角 (img->origin=IPL_ORIGIN_TL)或者是左下角(img->origin=IPL_ORIGIN_BL)
      if (frame->origin == IPL_ORIGIN_TL){
        cvCopy (frame, frame_copy, 0);
   }
      else{
     // 沿X-轴翻转, flip_mode > 0 (如 1) 沿Y-轴翻转， flip_mode < 0 (如 -1) 沿X-轴和Y-轴翻转.见下面的公式 
     //函数cvFlip 以三种方式之一翻转数组 (行和列下标是以0为基点的): 
        
		  cvFlip (frame, frame_copy, 0);//反转图像
   }
      detect_and_draw( frame_copy ); // 检测并且标识人脸
      if(cvWaitKey (10) >= 0)
      break;
  }
  
  //释放指针
  cvReleaseImage( &frame_copy );
  cvReleaseCapture( &capture);
 }
 
  cvDestroyWindow("人脸识别");
  return 0;
}


void detect_and_draw(IplImage *img) //检测和画出人脸的函数体
{
 //随机颜色
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
   IplImage *gray = cvCreateImage(cvSize(img->width,img->height), 8, 1);//灰度图像
   IplImage *small_img = cvCreateImage(cvSize(cvRound(img->width/scale),cvRound(img->height/scale)),8, 1);
   int i;
   cvCvtColor(img, gray, CV_BGR2GRAY);//把输入的彩色图像转化为灰度图像
   cvResize(gray, small_img,CV_INTER_LINEAR);//缩小灰色图片
   cvEqualizeHist(small_img, small_img);//灰度图象直方图均衡化
   cvClearMemStorage(storage);//释放内存块

   if (cascade)
   {
   double t = (double)cvGetTickCount();//精确测量函数的执行时间
   //从目标图像small_img中检测出人脸
   CvSeq *faces = cvHaarDetectObjects(small_img, cascade,storage,1.1,2,0,cvSize(30, 30));
   t = (double)cvGetTickCount() - t; //计算检测到人脸所需时间
   printf("检测所用时间 = %gms\n",t/((double)cvGetTickFrequency()*1000.));//打印到屏幕

   //画出检测到的人脸外框(可检测到多个人脸)
   for (i = 0; i < (faces ? faces->total : 0); i++)
   {
     //返回索引所指定的元素指针
     CvRect *r = (CvRect*)cvGetSeqElem(faces, i); 
     //用矩形
     //确定两个点来确定人脸位置因为用cvRetangle
     CvPoint pt1, pt2;
     //找到画矩形的两个点
     pt1.x = r->x*scale;
     pt2.x = (r->x+r->width)*scale;
     pt1.y = r->y*scale;
     pt2.y = (r->y+r->height)*scale;
     //画出矩形
     cvRectangle( img, pt1, pt2, colors[i%8], 3, 8, 0 );
   }

   }
  cvShowImage("人脸识别",img);
  cvReleaseImage(&gray);
  cvReleaseImage(&small_img);
}