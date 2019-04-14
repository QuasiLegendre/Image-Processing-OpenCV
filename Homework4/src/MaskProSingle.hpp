#ifndef MASKPROSINGLE
#define MASKPROSINGLE
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "EDistanceSquare.hpp"
#include <functional>
using std::function;
using namespace cv;

Mat MaskPro(function<float(float)> f, const int rows, const int cols)
{
	Mat Mask(rows, cols, CV_32F, Scalar::all(0));
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j)
			Mask.at<float>(i, j) = f(EDistanceSquare(rows, cols, i, j));
	return Mask;
}
#endif
