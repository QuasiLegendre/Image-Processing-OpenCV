#ifndef SHIFT
#define SHIFT
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;

void Shift(Mat &fImage)
{
    //For visualization purposes we may also rearrange the quadrants of the result, so that the origin (0,0), corresponds to the image center.
    Mat tmp, q0, q1, q2, q3;

    /*First crop the image, if it has an odd number of rows or columns.
    Operator & bit to bit by -2 (two's complement : -2 = 111111111....10) to eliminate the first bit 2^0 (In case of odd number on row or col, we take the even number in below)*/
    fImage = fImage(Rect(0, 0, fImage.cols & -2, fImage.rows & -2));
    int cx = fImage.cols/2;
    int cy = fImage.rows/2;

    /*Rearrange the quadrants of Fourier image so that the origin is at the image center*/
    q0 = fImage(Rect(0, 0, cx, cy));
    q1 = fImage(Rect(cx, 0, cx, cy));
    q2 = fImage(Rect(0, cy, cx, cy));
    q3 = fImage(Rect(cx, cy, cx, cy));

    /*We reverse each quadrant of the frame with its other quadrant diagonally opposite*/
    /*We reverse q0 and q3*/
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    /*We reverse q1 and q2*/
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
}
#endif
