#include "FWT.hpp"
#include "IFWT.hpp"
#include <iostream>
#include <fstream>
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
using std::ofstream;
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
	ofstream out("MyFunction.txt");
	Mat Db4S({-0.0105974018, 0.0328830117, 0.0308413818, -0.1870348117, -0.0279837694, 0.6308807679, 0.7148465706, 0.2303778133});  
	Mat Db4W({-0.2303778133, 0.7148465706, -0.6308807679, -0.0279837694, 0.1870348117, 0.0308413818, -0.0328830117, -0.0105974018});
	out << "Scaling base of Daubechies 4 tap function:" << endl;
	out << Db4S << endl;
	out << "Wavelet base of Daubechies 4 tap function:" << endl;
	out << Db4W << endl;
	normalize(Db4S, Db4S);
	normalize(Db4W, Db4W);
	out << "Scaling base of normalized Daubechies 4 tap function:" << endl;
	out << Db4S << endl;
	out << "Wavelet base of normalized Daubechies 4 tap function:" << endl;
	out << Db4W << endl;	
	Mat dst = FWT(src, Db4S, Db4W, 1);

	Mat H, V, D;
	dst(Rect(dst.cols/2, 0, dst.cols/2, dst.rows/2)).copyTo(H);
	dst(Rect(0, dst.rows/2, dst.cols/2, dst.rows/2)).copyTo(V);
	dst(Rect(dst.cols/2, dst.rows/2, dst.cols/2, dst.rows/2)).copyTo(D);
	imwrite(imagePrefix+"Horizonal.jpg", H);
	imwrite(imagePrefix+"Vertical.jpg", V);
	imwrite(imagePrefix+"Diagonal.jpg", D);
	
	H.release();
	V.release();
	D.release();

	Mat ZEROS = Mat::zeros(dst.rows/2, dst.cols/2, CV_32FC1);
	ZEROS.copyTo(dst(Rect(0, 0, dst.cols/2, dst.rows/2)));
	ZEROS.release();
	dst = IFWT(dst, Db4S, Db4W, 1);
	/*
	double Max, Min;
	max(dst, Max);
	min(dst, Min);
	cout << Max << '\n' << Min << endl;
	dst /= Max;
	dst *= 255
	*/
	dst *= 25;
	imwrite(imagePrefix+"ZeroPhi.jpg", dst);

	dst.release();
	src.release();
	
	out.close();
	return 0;
}
