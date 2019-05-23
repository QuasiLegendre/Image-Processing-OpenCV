#ifndef MIFWT
#define MIFWT
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <omp.h>

using namespace cv;

Mat up2(const Mat& src, const char* direction)
{
	if (direction == "X" || direction == "x" || direction == "cols" || direction == "column")
	{
		Mat dst(src.rows, src.cols * 2, CV_32FC1, Scalar(0.0));
		#pragma omp parallel for collapse(2) schedule(dynamic)
		for (int i = 0; i < src.rows; ++i)
		{
			for (int j = 0; j < src.cols; ++j)
			{
				dst.at<float>(i, j*2) = src.at<float>(i, j);
			}
		}
		return dst;
	}
	else if (direction == "Y" || direction == "y" || direction == "rows" || direction == "row")
	{
		Mat dst(src.rows * 2, src.cols, CV_32FC1, Scalar(0.0));
		#pragma omp parallel for collapse(2) schedule(dynamic)
		for (int i = 0; i < src.rows; ++i)
		{
			for (int j = 0; j < src.cols; ++j)
			{
				dst.at<float>(i*2, j) = src.at<float>(i, j);
			}
		}
		return dst;
	}
	else
	{
		Mat dst(src.rows * 2, src.cols * 2, CV_32FC1, Scalar(0.0));
		#pragma omp parallel for collapse(2) schedule(dynamic)
		for (int i = 0; i < src.rows; ++i)
		{
			for (int j = 0; j < src.cols; ++j)
			{
				dst.at<float>(i*2, j*2) = src.at<float>(i, j);
			}
		}
		return dst;
	}
}

Mat IFWT(const Mat& Im, const Mat& scaling, const Mat& wavelet, const int order)
{
	//Mat dst(Image.rows, Image.cols, CV_32FC1, Scalar(0.0));
	Mat Image;
	Im.copyTo(Image);
	Mat I({1.0}), Phi, D, H, V, scalingf, waveletf;
	flip(scaling, scalingf, 0);
	flip(wavelet, waveletf, 0);
	int orders = 1;
	for (int i = 0; i < order; ++i) {orders *= 2;}
	for (int i = 0; i < order; ++i)
	{
		Image(Rect(0, 0, Image.cols/orders, Image.rows/orders)).copyTo(Phi);	
		Image(Rect(Image.cols/orders, 0, Image.cols/orders, Image.rows/orders)).copyTo(H);
		Image(Rect(0, Image.rows/orders, Image.cols/orders, Image.rows/orders)).copyTo(V);
		Image(Rect(Image.cols/orders, Image.rows/orders, Image.cols/orders, Image.rows/orders)).copyTo(D);

		Phi = up2(Phi, "Y");
		sepFilter2D(Phi, Phi, CV_32FC1, I, scalingf);
		H = up2(H, "Y");
		sepFilter2D(H, H, CV_32FC1, I, waveletf);
		V = up2(V, "Y");
		sepFilter2D(V, V, CV_32FC1, I, scalingf);
		D = up2(D, "Y");
		sepFilter2D(D, D, CV_32FC1, I, waveletf);
		
		Phi += H;
		D += V;
		H.release();
		V.release();
		
		Phi = up2(Phi, "X");
		sepFilter2D(Phi, Phi, CV_32FC1, scalingf, I);
		D = up2(D, "X");
		sepFilter2D(D, D, CV_32FC1, waveletf, I);
		
		Phi += D;
		D.release();

		Phi.copyTo(Image(Rect(0, 0, Phi.cols, Phi.rows)));
		Phi.release();
		orders /= 2;
	}
	return Image;
}
#endif
