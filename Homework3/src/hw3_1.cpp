#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace cv;

using namespace std;

void SaltAndPepper(Mat& src, int num)
{
	random_device rd;
	mt19937 gen(rd());
	
	//auto cols = src.cols;
	
	for (int i = 0; i < num; ++i)
	{
		auto row = static_cast<int>(gen() % src.rows);
		auto col = static_cast<int>(gen() % src.cols);
		
		src.at<Vec3b>(row,col)[0] = 255;
		src.at<Vec3b>(row,col)[1] = 255;
		src.at<Vec3b>(row,col)[2] = 255; 
	}
	for (int i = 0; i < num; ++i)
	{
		auto row = static_cast<int>(gen() % src.rows);
		auto col = static_cast<int>(gen() % src.cols);
		
		src.at<Vec3b>(row,col)[0] = 0;
		src.at<Vec3b>(row,col)[1] = 0;
		src.at<Vec3b>(row,col)[2] = 0; 
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
	
	Mat src = imread(imagePrefix+Name,IMREAD_COLOR);

	
	if(src.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	SaltAndPepper(src,4096);
	imwrite(imagePrefix+"SaltAndPepper.jpg", src);

	Mat blur_dst, gaussian_dst, median_dst;

	blur(src, blur_dst, Size(3,3));
	imwrite(imagePrefix+"AverageConv.jpg", blur_dst);
	blur_dst.release();

	GaussianBlur(src, gaussian_dst, Size(3,3), 1);
	imwrite(imagePrefix+"GaussianConv.jpg", gaussian_dst);
	gaussian_dst.release();

	medianBlur(src, median_dst, 3);
	imwrite(imagePrefix+"MedianConv.jpg", median_dst);
	median_dst.release();
	
	src.release();
	return 0;
}
