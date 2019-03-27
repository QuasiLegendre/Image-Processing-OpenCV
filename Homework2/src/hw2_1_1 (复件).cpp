#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <string>
#include <vector>

using namespace cv;

using namespace std;

class HistogramHLS
{
private:
	int histSize[1];
	float hrange[2];
	const float* ranges[1];
	int channels[1];
public:
	HistogramHLS()
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
	
	Mat getHistogramS(const Mat& image)
	{
		vector<Mat> hls;
		Mat imageHLS;
		cvtColor(image, imageHLS, COLOR_BGR2HLS);
		split(imageHLS, hls);
		//Mat l_hist, g_hist, r_hist, hist;
		Mat s_hist;
		//calcHist(&bgr[0], 1, channels, Mat(), b_hist, 1, histSize, ranges);
		//calcHist(&bgr[1], 1, channels, Mat(), g_hist, 1, histSize, ranges);
		calcHist(&hls[2], 1, channels, Mat(), s_hist, 1, histSize, ranges);
		//Mat bgr_hist[3] = {b_hist, g_hist, r_hist};
		//merge(bgr_hist,3,hist);
		imageHLS.release();
		return s_hist;
	}
};
void histogram_specify(const Mat& src, const Mat& dst, Mat& result)
{
	HistogramHLS histHLS;
	Mat src_hist = histHLS.getHistogramS(src);
	Mat dst_hist = histHLS.getHistogramS(dst);
	
	Mat src_cdf = Mat::zeros(1,256,CV_32F);
	Mat dst_cdf = Mat::zeros(1,256,CV_32F);
	
	src_hist /= (src.rows * src.cols);
	dst_hist /= (dst.rows * dst.cols);
	
	for (int i=0; i < 256; ++i)
	{
		if (i == 0)
		{
			src_cdf.at<float>(i) = src_hist.at<float>(i);
			dst_cdf.at<float>(i) = dst_hist.at<float>(i);
		}
		else
		{
			src_cdf.at<float>(i) = src_cdf.at<float>(i-1) + src_hist.at<float>(i);
			dst_cdf.at<float>(i) = src_cdf.at<float>(i-1) + dst_hist.at<float>(i);
		}
	}
	
	Mat diff_cdf(256,256,CV_32F);
	for (int i = 0; i < 256; ++i)
		for (int j = 0; j < 256; ++j)
			diff_cdf.at<float>(i,j) = src_cdf.at<float>(i) - dst_cdf.at<float>(j);
	diff_cdf=abs(diff_cdf);
	
	Mat lut(1, 256, CV_8U);
	for (int i = 0; i < 256; ++i)
	{
		float min = diff_cdf.at<float>(i,0);
		int index = 0;
		for (int j = 1; j < 256; ++j)
		{
			if (min > diff_cdf.at<float>(i,j))
			{
				min = diff_cdf.at<float>(i,j);
				index = j;
			}
		}
	lut.at<uchar>(i) = static_cast<uchar>(index);
	}
	cvtColor(src, result, COLOR_BGR2HLS);
	vector<Mat> hls;
	split(result, hls);
	LUT(hls[2], lut, hls[2]);
	merge(hls, result);
	cvtColor(result, result, COLOR_HLS2BGR);
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
	imwrite(imagePrefix+"Result1.jpg", res);
	
	src.release();
	dst.release();
	res.release();
	return 0;
}
