#include "FWT.hpp"
#include "IFWT.hpp"
#include <iostream>
#include <random>
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
using std::random_device;
using std::mt19937;
using namespace cv;

double generateGaussianNoise(double mu, double sigma)
{
	const double epsilon = std::numeric_limits<double>::min();
	static double z0, z1;
	static bool flag = false;
	flag = !flag;
	if(!flag) return z1 * sigma + mu;
	double u1, u2;
	do
	{
		u1 = rand() * (1.0 / RAND_MAX);
		u2 = rand() * (1.0 / RAND_MAX);
	} while (u1 <= epsilon);
	z0 = sqrt(-2.0 * log(u1)) * cos(2 * CV_PI * u2);
	z1 = sqrt(-2.0 * log(u1)) * sin(2 * CV_PI * u2);
	return z0 * sigma + mu;
}
 
Mat addGaussianNoise(const Mat& image)
{
	Mat result = image.clone();
	int channels = image.channels();
	int rows = image.rows, cols = image.cols * image.channels();
	if (result.isContinuous()) cols = rows * cols, rows = 1;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int val = result.ptr<uchar>(i)[j] + generateGaussianNoise(2, 0.8) * 32;
			if (val < 0) val = 0;
			if (val > 255) val = 255;
			result.ptr<uchar>(i)[j] = (uchar)val;
		}
	}
	return result;
}

void SaltAndPepper(Mat& src, int num)
{
    random_device rd;
    mt19937 gen(rd());

    for (int i = 0; i < num; ++i)
    {
        auto row = static_cast<int>(gen() % src.rows);
        auto col = static_cast<int>(gen() % src.cols);

        src.at<uchar>(row,col) = 255;
    }
    for (int i = 0; i < num; ++i)
    {
        auto row = static_cast<int>(gen() % src.rows);
        auto col = static_cast<int>(gen() % src.cols);

        src.at<uchar>(row,col) = 0;
    }
}


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

	Mat GaussN = addGaussianNoise(src);
	Mat SP;
	src.copyTo(SP);
	SaltAndPepper(SP, int(src.cols*src.rows*0.2));
	src.release();
	
	imwrite(imagePrefix+"GaussianBlur.jpg", GaussN);
	imwrite(imagePrefix+"SaltAndPepper.jpg", SP);
	
	Mat Db4S({-0.0105974018, 0.0328830117, 0.0308413818, -0.1870348117, -0.0279837694, 0.6308807679, 0.7148465706, 0.2303778133});  
	Mat Db4W({-0.2303778133, 0.7148465706, -0.6308807679, -0.0279837694, 0.1870348117, 0.0308413818, -0.0328830117, -0.0105974018});
	normalize(Db4S, Db4S);
	normalize(Db4W, Db4W);
	Mat FWTG = FWT(GaussN, Db4S, Db4W, 2);
	Mat FWTSP = FWT(SP, Db4W, Db4W, 2);

	Mat ZEROG = Mat::zeros(FWTG.rows, FWTG.cols, CV_32FC1);
	Mat ZEROSP = Mat::zeros(FWTG.rows, FWTG.cols, CV_32FC1);

	FWTG = FWTG(Rect(0, 0, FWTG.cols/4, FWTG.rows/4));
	FWTSP = FWTSP(Rect(0, 0, FWTG.cols/4, FWTG.rows/4));

	FWTG.copyTo(ZEROG(Rect(0, 0, FWTG.cols, FWTG.rows)));
	FWTSP.copyTo(ZEROSP(Rect(0, 0, FWTSP.cols, FWTSP.rows)));

	FWTG.release();
	FWTSP.release();
	
	Mat RefinedG = IFWT(ZEROG, Db4S, Db4W, 2);
	Mat RefinedSP = IFWT(ZEROSP, Db4S, Db4W, 2);

	ZEROG.release();
	ZEROSP.release();
	
	imwrite(imagePrefix+"RefinedGaussian.jpg", RefinedG);
	imwrite(imagePrefix+"RefinedSaltAndPepper.jpg", RefinedSP);

	RefinedG.release();
	RefinedSP.release();

	return 0;
}
