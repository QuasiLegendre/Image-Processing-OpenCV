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
	ofstream out("Functions.txt");
	imwrite(imagePrefix+"Gray.jpg", src);
	Mat HarrS({1.0, 1.0});
	Mat HarrW({1.0, -1.0});
	out << "Scaling base of Harr function:" << endl;
	out << HarrS << endl;
	out << "Wavelet base of Harr function:" << endl;
	out << HarrW << endl;
	normalize(HarrS, HarrS);
	normalize(HarrW, HarrW);
	out << "Scaling base of normalized Harr function:" << endl;
	out << HarrS << endl;
	out << "Wavelet base of normalized Harr function:" << endl;
	out << HarrW << endl;
	Mat dst = FWT(src, HarrS, HarrW, 1);
	imwrite(imagePrefix+"HarrFWT.jpg", dst);
	dst.release();

	
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
	dst = FWT(src, Db4S, Db4W, 1);
	imwrite(imagePrefix+"Db4FWT.jpg", dst);

	dst.release();
	src.release();
	
	out.close();
	return 0;
}
