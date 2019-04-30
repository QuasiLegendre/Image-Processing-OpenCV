#ifndef MFWT
#define MFWT
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;

Mat FWT(const Mat& Im, const Mat& scaling, const Mat& wavelet, const int order)
{
	Mat Image;
	int Height = getOptimalDFTSize(Im.rows);
	int Width = getOptimalDFTSize(Im.cols);
	copyMakeBorder(Im, Image, 0, Height - Im.rows, 0, Width - Im.cols, BORDER_CONSTANT, Scalar::all(float(0.0)));
	Mat dst(Image.rows, Image.cols, CV_32FC1, Scalar(0.0));
	Mat I({1.0}), Phi, D, H, V;
	for (int i = 0; i < order; ++i)
	{
		sepFilter2D(Image, Phi, CV_32FC1, scaling, I);
		resize(Phi, Phi, Size(), 0.5, 1.0, INTER_NEAREST);
		sepFilter2D(Image, D, CV_32FC1, wavelet, I);
		resize(D, D, Size(), 0.5, 1.0, INTER_NEAREST);

		sepFilter2D(Phi, H, CV_32FC1, I, wavelet);
		resize(H, H, Size(), 1.0, 0.5, INTER_NEAREST);
		sepFilter2D(D, V, CV_32FC1, I, scaling);
		resize(V, V, Size(), 1.0, 0.5, INTER_NEAREST);
		sepFilter2D(Phi, Phi, CV_32FC1, I, scaling);
		resize(Phi, Phi, Size(), 1.0, 0.5, INTER_NEAREST);
		sepFilter2D(D, D, CV_32FC1, I, wavelet);
		resize(D, D, Size(), 1.0, 0.5, INTER_NEAREST);
		Image.release();

		Phi.copyTo(dst(Rect(0, 0, Phi.cols, Phi.rows)));
		H.copyTo(dst(Rect(Phi.cols, 0, H.cols, H.rows)));
		V.copyTo(dst(Rect(0, Phi.rows, V.cols, V.rows)));
		D.copyTo(dst(Rect(Phi.cols, Phi.rows, D.cols, D.rows)));
		Image = Phi;
		Phi.release();
		H.release();
		V.release();
		D.release();
	}
	return dst;
}
#endif
