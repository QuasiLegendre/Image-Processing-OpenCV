#include "FWT.hpp"
#include "IFWT.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

//using namespace std;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::exp;
using std::sqrt;
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
	
	Mat src = imread(imagePrefix+Name,IMREAD_GRAYSCALE);


	if(src.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}
	double sqrt2 = sqrt(2.0);
	imwrite(imagePrefix+"Gray.jpg", src);
	Mat scale({1.0/sqrt2, 1.0/sqrt2});
	Mat wavelet({1.0/sqrt2, -1.0/sqrt2});
	Mat dst = FWT(src, scale, wavelet, 2);
	imwrite(imagePrefix+"FWT.jpg", dst);
	Mat srcTT = IFWT(dst, scale, wavelet, 2);
	imwrite(imagePrefix+"TT.jpg", srcTT);
	srcTT.release();
	dst.release();
	src.release();
	return 0;
}
