
#include <complex>
#include <opencv2\opencv.hpp>  
#include<iostream>
#include <valarray>
using namespace std;

 
const double PI = 3.141592653589793238460;


typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;



char filename[1000];
void fft(CArray& x)
{
    const size_t N = x.size();
    if (N <= 1) return;
 
    // divide
    CArray even = x[std::slice(0, N/2, 2)];
    CArray  odd = x[std::slice(1, N/2, 2)];
 
    // conquer
    fft(even);
    fft(odd);
 
    // combine
    for (size_t k = 0; k < N/2; ++k)
    {
        Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
        x[k    ] = even[k] + t;
        x[k+N/2] = even[k] - t;
    }
}
 
//void getMean(IplImage *src)
//{
//	int height, width;
//	uchar** ImageData;
//	uchar* data;
//		height = src->height;
//		width = src->width;
//		
//		cout << "This image has " << width << " by " << height << " pixels." << endl;
//		cvGetRawData(src, (uchar**)&data);
//		ImageData = new uchar* [height];
//		for(int i = 0; i < height; i++)
//		{
//			ImageData[i] = new uchar [width];
//		}
//		//Calculate the mean of the image
//		double total = 0;
//		for (int i = 0; i < height; i++)
//		{
//			for (int j = 0; j < width; j++)
//			{
//				//total += ImageData[i][j];
//				total += data[width*src->width + height];
//			}
//		}
//		double mean = (total/ (height * width));
//		cout << "Mean: " << mean  << endl;
//	
//}

void main()
{
	IplImage *src;
	int height, width;
		uchar** ImageData;
	uchar* data;
	int count=0;

	CvScalar MeanScalar; 
    CvScalar StandardDeviationScalar; 
	Complex beat[1500];
	for(int i=1;i<=1500;i++)
	 {
	  sprintf(filename,"C:/Users/hzhou/Desktop/RGB/photo1/%d.jpg",i);
	  IplImage* src = cvLoadImage(filename);
	  /*cvNamedWindow("lena",CV_WINDOW_AUTOSIZE);

		CvSize s = cvSize(src->width, src->height);
		int d = src->depth;
		IplImage* R = cvCreateImage(s, d, 1);
		IplImage* G = cvCreateImage(s, d, 1);
		IplImage* B = cvCreateImage(s, d, 1);
		cvSplit(src, R, G, B, NULL);


		getMean(src);
		getMean(R);
		getMean(G);
		getMean(B);*/

		height = src->height;
		width = src->width;
		
		//cout << "This image has " << width << " by " << height << " pixels." << endl;
		cvGetRawData(src, (uchar**)&data);
		ImageData = new uchar* [height];
		//for(int i = 0; i < height; i++)
		//{
		//	ImageData[i] = new uchar [width];
		//}
		////Calculate the mean of the image
		//double total = 0;
		//for (int i = 0; i < height; i++)
		//{
		//	for (int j = 0; j < width; j++)
		//	{
		//		//total += ImageData[i][j];
		//		total += data[width*src->width + height];
		//	}
		//}
		
		cvAvgSdv(src,&MeanScalar,&StandardDeviationScalar); 
		beat[i] = MeanScalar.val[1] ;
		
		//double MeanScalar.val[0] = (total/ (height * width));
		/*if(MeanScalar.val[0]!=0){
			count++;
		}*/
		cout << "Mean: " << MeanScalar.val[1]  << endl;
		
		cvWaitKey(0);
		cvReleaseImage( &src );
		
	 }


    CArray data2(beat, 1500);
 
    fft(data2);

	for (int i = 0; i < 1500; ++i)
    {
        cout << data2[i] << std::endl;
    }
	//src = cvLoadImage("lena.jpg"); 
	//cout << "heartrate: " << count  << endl;
	getchar();

	
	//cvShowImage("lena",src);

	//cvWaitKey(0);
	//cvDestroyWindow("lena");

	//cvReleaseImage(&src);
}
