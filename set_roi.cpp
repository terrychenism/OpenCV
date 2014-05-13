#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    if( argc != 2)
    {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }

     IplImage* img;
     img= cvLoadImage(argv[1], IMREAD_COLOR); // Read the file
    //Mat img = imread(argv[1], IMREAD_COLOR); 

    int imageWidth=img->width;
              int imageHeight=img->height;
    //          int imageSize=img->nSize;
    //          cvRectangle(img,cvPoint(imageWidth/6,imageHeight/15), cvPoint(900, 500),cvScalar(255, 255, 0, 0),1,8,0);
             //cvSetImageROI(img,cvRect(50,50,(imageWidth-50),(imageHeight-50))); 



    cvRectangle(img, cvPoint(380,350), cvPoint(430,430), cvScalar(255, 255, 0, 0),1,8,0);
    namedWindow( "Display window", WINDOW_AUTOSIZE ); // Create a window for display.
    cvShowImage(  "Display window", img );                // Show our image inside it.

    waitKey(0); // Wait for a keystroke in the window
    return 0;
}
/*http://stackoverflow.com/questions/10628304/how-to-draw-a-rectangle-in-opencv-dynamically-according-to-image-width-and-heigh */
