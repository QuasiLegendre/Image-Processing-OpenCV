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
	
	Mat src = imread(imagePrefix+imageName,IMREAD_COLOR);
	
	if(!src.data)
	{
		cout<<"Could not open or find the image"<<endl;
		return -1;
	}
	
	Mat Sobel_dst_dx, Sobel_dst_dy, Laplacian_dst, Other_dst;
	
	Sobel(src, Sobel_dst_dx, -1 ,1, 0, 3);
	imwrite(imagePrefix + "SobelX.jpg", Sobel_dst_dx);
	Sobel_dst_dx.release();

	Sobel(src, Sobel_dst_dy, -1, 0, 1, 3);
	imwrite(imagePrefix + "SobelY.jpg", Sobel_dst_dy);
	Sobel_dst_dy.release();

	Laplacian(src, Laplacian_dst, -1);
	imwrite(imagePrefix + "Laplacian.jpg", Laplacian_dst);
	Laplacian_dst.release();

	float mask[2][2] = {{0,1},{-1,0}};
	Mat krnl = Mat(2, 2, CV_32F, mask);
	cout << "The required kernel is:" <<endl;
	cout << krnl << endl;
	filter2D(src, Other_dst, -1, krnl);
	imwrite(imagePrefix + "Other.jpg", Other_dst);
	Other_dst.release();

	src.release();
	return 0;
}
