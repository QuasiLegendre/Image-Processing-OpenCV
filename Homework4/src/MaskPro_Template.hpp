#ifndef TYPE_DEDUCE
#define TYPE_DEDUCE

template<typename _T>
struct TypeDeduce
{
	using type = _T;
};
#endif

#ifndef MASKPRO
#define MASKPRO
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "EDistanceSquare.hpp"
#include <functional>
using std::function;
using namespace cv;
template<typename _F>
Mat MaskPro(typename TypeDeduce<function<_F(_F)> >::type f, const int rows, const int cols)
{
	int _Type;
	if (typeid(_F) == typeid(double))
	{
		_Type = CV_64F;
	}
	else
	{
		_Type = CV_32F;
	}
	Mat Mask(rows, cols, _Type, Scalar::all(0));
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j)
			Mask.at<_F>(i, j) = f(EDistanceSquare(rows, cols, i, j));

	return Mask;
}
#endif
