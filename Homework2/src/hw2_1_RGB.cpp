#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <string>
#include <vector>

using namespace cv;

using namespace std;

class Histogram3D
{
private:
	int histSize[1];
	float hrange[2];
	const float* ranges[1];
	int channels[1];
public:
	Histogram3D()
	{
		hrange[0] = 0.0;
		hrange[1] = 255.0;
		for(int i = 0; i < 1; ++i)
		{
			histSize[i] = 256;
			ranges[i] = hrange;
			channels[i] = i;
		}
	}
	
	Mat getHistogram(const Mat& image)
	{
		vector<Mat> bgr;
		split(image, bgr);
		Mat b_hist, g_hist, r_hist, hist;
		calcHist(&bgr[0], 1, channels, Mat(), b_hist, 1, histSize, ranges);
		calcHist(&bgr[1], 1, channels, Mat(), g_hist, 1, histSize, ranges);
		calcHist(&bgr[2], 1, channels, Mat(), r_hist, 1, histSize, ranges);
		Mat bgr_hist[3] = {b_hist, g_hist, r_hist};
		merge(bgr_hist,3,hist);
		return hist;
	}
};
void histogram_specify(const Mat& src, const Mat& dst, Mat& result)
{
	Histogram3D hist3D;
	Mat src_hist = hist3D.getHistogram(src);
	Mat dst_hist = hist3D.getHistogram(dst);
	
	Mat src_cdf = Mat::zeros(1,256,CV_32FC3);
	Mat dst_cdf = Mat::zeros(1,256,CV_32FC3);
	
	src_hist /= (src.rows * src.cols);
	dst_hist /= (dst.rows * dst.cols);
	
	for (int i=0; i < 256; ++i)
	{
		if (i == 0)
		{
			src_cdf.at<Vec3f>(i) = src_hist.at<Vec3f>(i);
			dst_cdf.at<Vec3f>(i) = dst_hist.at<Vec3f>(i);
		}
		else
		{
			src_cdf.at<Vec3f>(i) = src_cdf.at<Vec3f>(i-1) + src_hist.at<Vec3f>(i);
			dst_cdf.at<Vec3f>(i) = src_cdf.at<Vec3f>(i-1) + dst_hist.at<Vec3f>(i);
		}
	}
	
	Mat diff_cdf(256,256,CV_32FC3);
	for (int i = 0; i < 256; ++i)
		for (int j = 0; j < 256; ++j)
			diff_cdf.at<Vec3f>(i,j) = src_cdf.at<Vec3f>(i) - dst_cdf.at<Vec3f>(j);
	diff_cdf=abs(diff_cdf);
	
	Mat lut(1, 256, CV_8UC3);
	for (int c = 0; c < 3; ++c)	
	{
		for (int i = 0; i < 256; ++i)
		{
			float min = diff_cdf.at<Vec3f>(i,0)[c];
			int index = 0;
			for (int j = 1; j < 256; ++j)
			{
				if (min > diff_cdf.at<Vec3f>(i,j)[c])
				{
					min = diff_cdf.at<Vec3f>(i,j)[c];
					index = j;
				}
			}
		lut.at<Vec3b>(i)[c] = static_cast<uchar>(index);
		}
	}
	//cout << lut <<endl;
	LUT(src, lut, result);
	
}
int main(int argc, char** argv)
{
	string imagePrefix = "../data/";
	string srcName, dstName;
	if(argc == 3) 
	{
		srcName = argv[1];
		dstName = argv[2];
	}
	else if(argc == 5 && argv[1] == "absolute")
	{
		imagePrefix = argv[2];
		srcName = argv[3];
		dstName = argv[4];
	}
	else
	{
		cout<<"Incorrect input"<<endl;
		return -1;
	}
	
	Mat src = imread(imagePrefix+srcName,IMREAD_COLOR);
	Mat dst = imread(imagePrefix+dstName,IMREAD_COLOR);
	
	if(src.empty() || dst.empty())
	{
		cout<<"Could not open or find the image"<<endl;
		return -1;
	}
	
	Mat res;
	histogram_specify(src, dst, res);
	imwrite(imagePrefix+"Result1_1.jpg", res);
	
	src.release();
	dst.release();
	res.release();
	return 0;
}
