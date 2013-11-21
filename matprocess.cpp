#include "highgui.h"
#include <cstdio>

//void sat_sv( IplImage* img ) ;
int main(int argc, char **argv)
{
    IplImage *img = cvLoadImage("lena.jpg", 1);
    CvScalar pixel;
	float Bvalue=0/*,Gvalue,Rvaluel*/;
    for (int i = 0; i < img->height; ++i)
    {
        for (int j = 0; j < img->width; ++j)
        {
            //获得像素的RGB值并显示, 注意内存中存储顺序是BGR
            pixel = cvGet2D(img, i, j);
			Bvalue=pixel.val[0]+Bvalue;
			printf("B=%f\n", Bvalue);
           //printf("B=%f,G=%f,R=%f\n", pixel.val[0], pixel.val[1], pixel.val[2]);
            //修改各点的值
            pixel.val[0] = 0;
            pixel.val[1] = 0;
            pixel.val[2] = 0;
            cvSet2D(img, i, j, pixel);
        }
    }
    cvNamedWindow("image", 1);
    cvShowImage("image", img);
    cvWaitKey(0);
    cvDestroyWindow("image");
    cvReleaseImage(&img);
    return 0;
}
//void sat_sv( IplImage* img ) {
//for( int y=0; y<img->height; y++ ) {
//    uchar* ptr = (uchar*) (
//      img->imageData + y * img->widthStep 
//    );
//    for( int x=0; x<img->width; x++ ) {
//      ptr[3*x+1] = 255;
//      ptr[3*x+2] = 255;
//		
//	 //printf("%p",ptr);
//	  getchar();
//    }
//}
//}