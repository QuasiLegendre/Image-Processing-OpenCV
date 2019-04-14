#include "IFFTNoNormalize.hpp"
#include "MaskProSingle.hpp"
#include "Shift.hpp"
#include <omp.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <iomanip>
//using namespace std;
using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::vector;
using std::exp;
using std::setprecision;
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
	//float D = 100.0;

	int H = getOptimalDFTSize(src.rows);
	int W = getOptimalDFTSize(src.cols);
	float GH[] = {1.0, 1.1, 1.2, 1.3, 1.4, 1.5};
	float GL[] = {0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
	float GC[] = {0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5};
	float D[] = {80.0, 90.0, 100.0, 110.0, 120.0};

	src.convertTo(src, CV_32F, 1/255.0);
	ofstream out5("Filters5x5.txt");
	ofstream out13("Filters13x13.txt");
	ofstream out21("Filters21x21.txt");
	#pragma omp parallel for collapse(4) schedule(dynamic)
	for (int i = 0; i < 6; ++i)
	for (int j = 0; j < 6; ++j)
	for (int k = 0; k < 11; ++k)
	for (int l = 0; l < 5; ++l)
	{
		function<float(float)> Hf = [&GH, &GL, &GC, &D, i, j, k, l](float DD){return GL[j] + (GH[i] - GL[j])*(1.0 - exp(-GC[k]*DD/(2.0*D[l]*D[l])));};
		Mat HomoMask = MaskPro(Hf, H, W);

		Shift(HomoMask);
		Mat HomoFilt = IFFT(HomoMask, src)*255.0;
		//cout << HomoFilt.cols/2 << HomoFilt.rows/2 << endl;
		out5 << setprecision(2) <<"GH" << GH[i] << "GL" << GL[j] << "GC" << GC[k] << "D" << D[l] << endl;
		Mat Homo5 = HomoFilt(Rect(HomoFilt.cols/2 - 2, HomoFilt.rows/2 - 2, 5, 5));
		out5 << Homo5 / sum(Homo5).val[0] << endl;
		out13 << setprecision(2) <<"GH" << GH[i] << "GL" << GL[j] << "GC" << GC[k] << "D" << D[l] << endl;
		Mat Homo13 = HomoFilt(Rect(HomoFilt.cols/2 - 6, HomoFilt.rows/2 - 6, 13, 13));
		out13 << Homo13 / sum(Homo13).val[0] << endl;
		out21 << setprecision(2) <<"GH" << GH[i] << "GL" << GL[j] << "GC" << GC[k] << "D" << D[l] << endl;
		Mat Homo21 = HomoFilt(Rect(HomoFilt.cols/2 - 10, HomoFilt.rows/2 - 10, 21, 21));
		out21 << Homo21 / sum(Homo21).val[0] << endl;
		//if (l == 4){out5 << endl;}
		//if (l == 2 || l == 4){out13 << endl;}	
		//Mat OutFilt;
		//HomoFilt.convertTo(OutFilt, CV_8U, 255);
		//stringstream name;
		//name << setprecision(2) << "Filt/" << "HomoFilter" << "GH" << GH[i] << "GL" << GL[j] << "GC" << GC[k] << "D" << D[l] << ".jpg";
		//imwrite(imagePrefix+name.str(), OutFilt);
	}
	//Frq.release();
	//ModIm.release();
	out5.close();
	out13.close();
	out21.close();
	src.release();
	return 0;
}
