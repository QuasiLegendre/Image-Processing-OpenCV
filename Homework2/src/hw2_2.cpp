#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <string>
#include <vector>

using namespace cv;

using namespace std;

int main(int argc, char** argv)
{
	string imagePrefix = "../data/";
	string imageName;
	if(argc == 2) 
	{
		imageName = argv[1];
	}
	else if(argc == 4 && argv[1] == "absolute")
	{
		imagePrefix = argv[2];
		imageName = argv[3];
	}
	else
	{
		cout<<"Incorrect input"<<endl;
		return -1;
	}
	
	Mat image = imread(imagePrefix+imageName,IMREAD_GRAYSCALE);
	
	if(!image.data)
	{
		cout<<"Could not open or find the image"<<endl;
		return -1;
	}
	
	Rect rect(0, 0, int(image.cols/2), image.rows-1);
	Mat half = image(rect).clone();
	equalizeHist(half,half);
	Mat result = image.clone();
	half.copyTo(result(rect));
	imwrite(imagePrefix+"Result2.jpg", result);
	
	image.release();
	half.release();
	result.release();
	return 0;
}
