#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>
using namespace std;
using namespace cv;


int main(int argc, char * argv[]){
	int a[12] = {1,2,23,34,5,6,6,7,7,78,16,76};
	cout<<a[2]<<endl;

	int r=1;
	int c=12;

	std::vector<float> box1;
	for(int i = 0; i<12;i++){
		 box1.push_back(a[i]);
	}


	cout<<box1.front()<<endl;

	//create Mat
	Mat N=Mat(r,c,CV_32FC1);
	//copy vector to mat
	memcpy(N.data,box1.data(),box1.size()*sizeof(float));

	//print Mat
	cout <<  N <<  endl;

	
	printf("/////////////////////////////////////////////////////////////\n");
	printf("//vector to Mat\n");
	

	vector< float> Vf;

	//insert value
	int cnt=0;
	for(int i=0; i< c; ++i) 
	  for(int j=0; j< r; ++j)  
	    Vf.push_back(cnt++);
  
	 //create Mat
	 Mat M=Mat(r,c,CV_32FC1);
	 //copy vector to mat
	 memcpy(M.data,Vf.data(),Vf.size()*sizeof(float));

	 //print Mat
	 cout <<  M <<  endl;

	 Mat C;
	 absdiff(N, M, C);
	 cout <<  C <<  endl;

	 printf("/////////////////////////////////////////////////////////////\n");
	 printf("//Mat to vector\n");
	 vector< float> Vf2;
	 //copy mat to vector
	 Vf2.assign((float*)C.datastart, (float*)C.dataend);

	  //confirm
	 cnt=0;
	 for(int i=0; i< c; ++i)
	 {
	  for(int j=0; j< r; ++j)  
	    printf("%lf ", Vf2[cnt++]);
	  printf("\n");
	 }


 getchar();

}



