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



//����ͻ���ֱ��ͼ��R,G,B��
/* img ͨ��ͼ��
 * hist_img: ֱ��ͼ�Ļ�ͼͼ��
 * pstrWndName: ��ͼ����
 */
void draw_histogram(IplImage* img,IplImage* hist_img,const char* pstrWndName)
{

	CvHistogram* hist = NULL;

	int bin_count = 256;
	float range[] = {0,255};
	float* ranges[]={range};

	hist = cvCreateHist(1,         //һά
		&bin_count, //ÿһά��bin��ֱ�������ĸ����� �˴�Ϊ 256 �����������������������ͻᴴ��һ��1*256�ľ���
		CV_HIST_ARRAY,
		ranges,
		1);
	cvClearHist(hist);   //��ֹ��ʼ��ʱ���������ݣ�������һ��	

	cvCalcHist(&img,hist,0,0);

	//�õ�ֱ��ͼ����ֵ�����
	float min,max;
	int min_idx,max_idx;
	cvGetMinMaxHistValue(hist,&min,&max,&min_idx,&max_idx);

	//cout<<"min: "<<min<<"  max:"<<max<<endl; 
	if(max == 0) {cout<<"max =0 err!"<<endl;max = 100;}

	//����ֱ��ͼ�Ĵ�С����ͼ������Ӧ
	cvScale(hist->bins,hist->bins,((double)hist_img->height)/max,0);

	//�������е�ֱ��ͼ����ֵΪ255
	cvSet(hist_img,cvScalarAll(255),0);

	// ƽ��ÿ��ֱ�����Ŀ��
	int bin_w=cvRound((double)hist_img->width/bin_count);

	//��ֱ��ͼ
	for(int i=0;i<bin_count;i++)
	{
	   cvRectangle(hist_img,
		cvPoint(i*bin_w,hist_img->height),  //���½ǵĵ㣨i*bin_w��height��
		cvPoint((i+1)*bin_w, hist_img->height-cvRound(cvGetReal1D(hist->bins,i))),//���Ͻǵĵ�((i+1)*bin_w,ͼ��߶�-ֱ�����ĸ߶�)
		 cvScalarAll(0),
		-1,
		8,
		0);
	}

	// ��ʾֱ��ͼ
	cvShowImage(pstrWndName,hist_img);
}
int main(int argc, char* argv[])
{
	// ��������
	cvNamedWindow(pstrSrcWnd,1);
	cvNamedWindow(pstrBHistWnd,1);
	cvNamedWindow(pstrGHistWnd,1);
	cvNamedWindow(pstrRHistWnd,1);

	//��ȡ����ͷ
	CvCapture* capture = cvCreateCameraCapture(-1);
	if(!capture) cout<<"�޷�������ͷ"<<endl;

	// ��ȡһ֡�����Ի�ȡ����
	IplImage* frame = NULL;
	frame = cvQueryFrame(capture);

	// B G R ͨ��
	CvSize img_size;img_size.width = frame->width;img_size.height = frame->height;
	IplImage* b = cvCreateImage(img_size,8,1);
	IplImage* g = cvCreateImage(img_size,8,1);
	IplImage* r = cvCreateImage(img_size,8,1);

	// ֱ��ͼ
	CvSize size;size.width = 320;size.height = 200;
	IplImage* b_hist_img = cvCreateImage(size,8,1);
	IplImage* g_hist_img = cvCreateImage(size,8,1);
	IplImage* r_hist_img = cvCreateImage(size,8,1);

	while(1)
	{			
		frame = cvQueryFrame(capture);
		if(!frame) break;
		
		// �ָ�BGRͨ��
		cvSplit(frame,b,g,r,0);

		// ��ʾ����ͷͼ��
		cvShowImage(pstrSrcWnd,frame);

		// ����ֱ��ͼ
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