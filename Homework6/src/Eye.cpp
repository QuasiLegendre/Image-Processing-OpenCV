#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>
#include <vector>


using std::cout;
using std::endl;
using std::string;
using std::vector;
using namespace cv;

int main(int argc, char** argv)
{
	string imagePrefix = "../data/";
	string Name;
	if(argc == 2) 
	{
		Name = argv[1];
	}
	else if(argc == 4 && argv[1] == "absolute")
	{
		imagePrefix = argv[2];
		Name = argv[3];
	}
	else
	{
		cout << "Incorrect input" << endl;
		return -1;
	}
	
	Mat src = imread(imagePrefix+Name, IMREAD_COLOR);


	if(src.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	Mat leye = src(Rect(1600, 1400, 120, 50));
	Mat reye = src(Rect(1320, 1420, 120, 50));
	
	Mat leyeLinear, reyeLinear, leyeCubic, reyeCubic; 
	resize(leye, leyeLinear, Size(), 1.2, 1.2, INTER_LINEAR);
	resize(reye, reyeLinear, Size(), 1.2, 1.2, INTER_LINEAR);
	resize(leye, leyeCubic, Size(), 1.2, 1.2, INTER_CUBIC);
	resize(reye, reyeCubic, Size(), 1.2, 1.2, INTER_CUBIC);
	leye.release();
	reye.release();
	Mat dstL, dstC, dstR;
	src.copyTo(dstL);
	src.copyTo(dstC);
	src.copyTo(dstR);
	src.release();
	rotate(dstR(Rect(0, 0, 800, 800)), dstR(Rect(0, 0, 800, 800)), ROTATE_90_COUNTERCLOCKWISE);
	leyeLinear.copyTo(dstL(Rect(1588, 1395, 144, 60)));
	reyeLinear.copyTo(dstL(Rect(1308, 1415, 144, 60)));
	leyeCubic.copyTo(dstC(Rect(1588, 1395, 144, 60)));
	reyeCubic.copyTo(dstC(Rect(1308, 1415, 144, 60)));
	leyeLinear.release();
	reyeLinear.release();
	leyeCubic.release();
	reyeCubic.release();
	imwrite(imagePrefix+"Linear.jpeg", dstL);
	imwrite(imagePrefix+"Cubic.jpeg", dstC);
	imwrite(imagePrefix+"Rotate.jpeg", dstR);
	dstL.release();
	dstC.release();
	return 0;
}
