#ifndef MFFT
#define MFFT
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;

Mat FFT(const Mat& Im)
{
	Mat Image;
	int H = getOptimalDFTSize(Im.rows);
	int W = getOptimalDFTSize(Im.cols);
	copyMakeBorder(Im, Image, 0, H - Im.rows, 0, W - Im.cols, BORDER_CONSTANT, Scalar::all(float(0.0)));
	Mat ImagePlanes[] = {Mat_<float>(Image), Mat::zeros(Image.size(), CV_32F)};
	Mat ImageComplex;
    	merge(ImagePlanes, 2, ImageComplex);
	dft(Image, ImageComplex, DFT_COMPLEX_OUTPUT);
	return ImageComplex;
}
#endif
