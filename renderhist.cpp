#include <cv.h> 
#include <cxcore.h>
#include <highgui.h> 



//////////////////////////////////////////////////////////////////////////

// Camera_Capture_Histogram.cpp : Defines the entry point for the console application.


#include <iostream>
using namespace std;

const char* pstrSrcWnd = "Src";
const char* pstrBHistWnd = "b plane";
const char* pstrGHistWnd = "g plane";
const char* pstrRHistWnd = "r plane";



//计算和绘制直方图（R,G,B）
/* img 通道图像
 * hist_img: 直方图的绘图图像
 * pstrWndName: 绘图窗口
 */
void draw_histogram(IplImage* img,IplImage* hist_img,const char* pstrWndName)
{

	CvHistogram* hist = NULL;

	int bin_count = 256;
	float range[] = {0,255};
	float* ranges[]={range};

	hist = cvCreateHist(1,         //一维
		&bin_count, //每一维上bin（直方柱）的个数， 此处为 256 【由上述两个参数，函数就会创建一个1*256的矩阵】
		CV_HIST_ARRAY,
		ranges,
		1);
	cvClearHist(hist);   //防止初始化时有其它数据，先清理一下	

	cvCalcHist(&img,hist,0,0);

	//得到直方图的最值及标号
	float min,max;
	int min_idx,max_idx;
	cvGetMinMaxHistValue(hist,&min,&max,&min_idx,&max_idx);

	//cout<<"min: "<<min<<"  max:"<<max<<endl; 
	if(max == 0) {cout<<"max =0 err!"<<endl;max = 100;}

	//缩放直方图的大小，和图像相适应
	cvScale(hist->bins,hist->bins,((double)hist_img->height)/max,0);

	//设置所有的直方图的数值为255
	cvSet(hist_img,cvScalarAll(255),0);

	// 平均每个直放柱的宽度
	int bin_w=cvRound((double)hist_img->width/bin_count);

	//画直方图
	for(int i=0;i<bin_count;i++)
	{
	   cvRectangle(hist_img,
		cvPoint(i*bin_w,hist_img->height),  //左下角的点（i*bin_w，height）
		cvPoint((i+1)*bin_w, hist_img->height-cvRound(cvGetReal1D(hist->bins,i))),//右上角的点((i+1)*bin_w,图像高度-直方柱的高度)
		 cvScalarAll(0),
		-1,
		8,
		0);
	}

	// 显示直方图
	cvShowImage(pstrWndName,hist_img);
}
int main(int argc, char* argv[])
{
	// 创建窗口
	cvNamedWindow(pstrSrcWnd,1);
	cvNamedWindow(pstrBHistWnd,1);
	cvNamedWindow(pstrGHistWnd,1);
	cvNamedWindow(pstrRHistWnd,1);

	//读取摄像头
	CvCapture* capture = cvCreateCameraCapture(-1);
	if(!capture) cout<<"无法打开摄像头"<<endl;

	// 读取一帧数据以获取参数
	IplImage* frame = NULL;
	frame = cvQueryFrame(capture);

	// B G R 通道
	CvSize img_size;img_size.width = frame->width;img_size.height = frame->height;
	IplImage* b = cvCreateImage(img_size,8,1);
	IplImage* g = cvCreateImage(img_size,8,1);
	IplImage* r = cvCreateImage(img_size,8,1);

	// 直方图
	CvSize size;size.width = 320;size.height = 200;
	IplImage* b_hist_img = cvCreateImage(size,8,1);
	IplImage* g_hist_img = cvCreateImage(size,8,1);
	IplImage* r_hist_img = cvCreateImage(size,8,1);

	while(1)
	{			
		frame = cvQueryFrame(capture);
		if(!frame) break;
		
		// 分割BGR通道
		cvSplit(frame,b,g,r,0);

		// 显示摄像头图像
		cvShowImage(pstrSrcWnd,frame);

		// 绘制直方图
		draw_histogram(b,b_hist_img,pstrBHistWnd); 
		draw_histogram(g,g_hist_img,pstrGHistWnd); 
		draw_histogram(r,r_hist_img,pstrRHistWnd); 

		char c = cvWaitKey(330);
		if(c == 27) break;
	}
	
	cvReleaseImage(&frame);
	cvReleaseImage(&b);
	cvReleaseImage(&g);
	cvReleaseImage(&r);
	cvReleaseImage(&b);
	cvReleaseImage(&g);
	cvReleaseImage(&r);
	cvDestroyAllWindows();

	return 0;
}