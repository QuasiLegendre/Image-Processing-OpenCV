#ifndef MIFFT
#define MIFFT
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;

Mat IFFT(const Mat& Fr, const Mat& Im)
{
	Mat Image;
	idft(Fr, Image, DFT_REAL_OUTPUT);
	return Image;
	//return Image(Rect((Fr.cols - Im.cols)/2, (Fr.rows - Im.rows)/2, Im.cols, Im.rows));
}
#endif
