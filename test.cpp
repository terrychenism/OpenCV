
#include <cv.h>
#include <highgui.h>
#include <stdio.h>
int main(int argc, char** argv)
{
   
  	IplImage *frame;
   CvCapture* capture         = NULL;
   if((argc =0)|| !(capture = cvCreateFileCapture( "tree.avi" ))){
   	printf("Failed to open %s\n",argv[1]);
   	return -1;
   }

	double f = cvGetCaptureProperty(
		capture,
		CV_CAP_PROP_FOURCC
	);
	char* fourcc = (char*) (&f);
	printf("Properties of %s are:\n",argv[1]);
	printf("FORCC = %d | %d | %d | %d |\n",fourcc[0],fourcc[1],fourcc[2],fourcc[3]);
    getchar();
   cvReleaseCapture( &capture );
   
   return 0;
}
