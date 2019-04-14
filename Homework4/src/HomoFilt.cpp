#include "FFT.hpp"
#include "IFFT.hpp"
#include "MaskPro.hpp"
#include "Shift.hpp"
#include <omp.h>
#include <iostream>
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
//using std::exp;
using std::setprecision;
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


	int H = getOptimalDFTSize(src.rows);
	int W = getOptimalDFTSize(src.cols);
	float GH[] = {1.0, 1.1, 1.2, 1.3, 1.4, 1.5};
	float GL[] = {0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
	float GC[] = {0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5};
	float D[] = {80.0, 90.0, 100.0, 110.0, 120.0};

	src.convertTo(src, CV_32F, 1/255.0);
	copyMakeBorder(src, src, 0, H - src.rows, 0, W - src.cols, BORDER_CONSTANT, Scalar::all(float(0.0)));
	Mat lnsrc = src;
	log(lnsrc + 1.0, lnsrc);
	#pragma omp parallel for collapse(4) schedule(dynamic)
	for (int i = 0; i < 6; ++i)
	for (int j = 0; j < 6; ++j)
	for (int k = 0; k < 11; ++k)
	for (int l = 0; l < 5; ++l)
	{
		function<float(float)> Hf = [&GH, &GL, &GC, &D, i, j, k, l](float DD){return GL[j] + (GH[i] - GL[j])*(1.0 - std::exp(-GC[k]*DD/(2.0*D[l]*D[l])));};
		Mat HomoMask = MaskPro(Hf, H, W);
		Mat Frq = FFT(lnsrc);
		Shift(Frq);
		multiply(Frq, HomoMask, Frq);
		Shift(Frq);
		Mat ModIm;
		Mat Res = IFFT(Frq, lnsrc);
		exp(Res, Res);
		Res -= 1.0;
		Res += src;
		Res.convertTo(ModIm, CV_8U, 255);
		stringstream name;
		name << setprecision(2) << "HOMO/" << "ModifiedImage" << "GH" << GH[i] << "GL" << GL[j] << "GC" << GC[k] << "D" << D[l] << ".jpg";
		imwrite(imagePrefix+name.str(), ModIm);
	}

	lnsrc.release();
	src.release();
	return 0;
}
