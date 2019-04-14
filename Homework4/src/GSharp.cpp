#include "FFT.hpp"
#include "IFFT.hpp"
#include "MaskPro.hpp"
#include "Shift.hpp"

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
	float D = 100.0;
	function<float(float)> Gf = [D](float dd){return 2.0 - exp(-dd/(2.0*D*D));};
	int H = getOptimalDFTSize(src.rows);
	int W = getOptimalDFTSize(src.cols);
	Mat GaussMask = MaskPro(Gf, H, W);
	src.convertTo(src, CV_32F, 1/255.0);
	Mat Frq = FFT(src);
	vector<Mat> db;	
	Shift(Frq);
	
	split(Frq, db);
	Mat mg, ph;
	magnitude(db[0], db[1], mg);
	phase(db[0], db[1], ph);
	mg.convertTo(mg, CV_8U, 255);
	ph.convertTo(ph, CV_8U, 255);
	imwrite(imagePrefix+"FMag.jpg", mg);
	imwrite(imagePrefix+"FPha.jpg", ph);
	//cout << Frq.size() << Frq.channels() << GaussMask.size()<< GaussMask.channels() << endl;
	mg.release();
	ph.release();
	multiply(Frq, GaussMask, Frq);
	split(GaussMask, db);
	db[0].convertTo(db[0], CV_8U, 128);
	imwrite(imagePrefix+"Mask.jpg", db[0]);
	//imwrite(imagePrefix+"ModifiedFrequency.jpg", Frq);
	split(Frq, db);
	Mat Mmg, Mph;
	magnitude(db[0], db[1], Mmg);
	phase(db[0], db[1], Mph);
	Mmg.convertTo(Mmg, CV_8U, 255);
	Mph.convertTo(Mph, CV_8U, 255);
	imwrite(imagePrefix+"MFMag.jpg", Mmg);
	imwrite(imagePrefix+"MFPha.jpg", Mph);
	Mmg.release();
	Mph.release();
	Shift(Frq);
	Mat ModIm = IFFT(Frq, src);
	ModIm.convertTo(ModIm, CV_8U, 255);
	imwrite(imagePrefix+"ModifiedImage.jpg", ModIm);

	Frq.release();
	ModIm.release();
	src.release();
	return 0;
}
