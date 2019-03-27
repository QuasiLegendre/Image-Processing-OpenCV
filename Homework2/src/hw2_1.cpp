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
		Mat h_hist, l_hist, s_hist, hist;
		//Mat s_hist;
		calcHist(&hls[0], 1, channels, Mat(), h_hist, 1, histSize, ranges);
		calcHist(&hls[1], 1, channels, Mat(), l_hist, 1, histSize, ranges);
		calcHist(&hls[2], 1, channels, Mat(), s_hist, 1, histSize, ranges);
		Mat hls_hist[3] = {h_hist, l_hist, s_hist};
		merge(hls_hist,3,hist);
		imageHLS.release();
		return hist;
	}
};
void histogram_specify(const Mat& src, const Mat& dst, Mat& result)
{
	HistogramHLS histHLS;
	Mat src_hist = histHLS.getHistogramS(src);
	Mat dst_hist = histHLS.getHistogramS(dst);
	
	Mat src_cdf = Mat::zeros(1,256,CV_32FC3);
	Mat dst_cdf = Mat::zeros(1,256,CV_32FC3);
	
	src_hist /= (src.rows * src.cols);
	dst_hist /= (dst.rows * dst.cols);
	for (int i=0; i < 180; ++i)
	{
		if (i == 0)
		{
			src_cdf.at<Vec3f>(i)[0] = src_hist.at<Vec3f>(i)[0];
			dst_cdf.at<Vec3f>(i)[0] = dst_hist.at<Vec3f>(i)[0];
		}
		else
		{
			src_cdf.at<Vec3f>(i)[0] = src_cdf.at<Vec3f>(i-1)[0] + src_hist.at<Vec3f>(i)[0];
			dst_cdf.at<Vec3f>(i)[0] = src_cdf.at<Vec3f>(i-1)[0] + dst_hist.at<Vec3f>(i)[0];
		}
	}
	for (int c = 1; c < 3 ;++c)
	{
		for (int i=0; i < 256; ++i)
		{
			if (i == 0)
			{
				src_cdf.at<Vec3f>(i)[c] = src_hist.at<Vec3f>(i)[c];
				dst_cdf.at<Vec3f>(i)[c] = dst_hist.at<Vec3f>(i)[c];
			}
			else
			{
				src_cdf.at<Vec3f>(i)[c] = src_cdf.at<Vec3f>(i-1)[c] + src_hist.at<Vec3f>(i)[c];
				dst_cdf.at<Vec3f>(i)[c] = src_cdf.at<Vec3f>(i-1)[c] + dst_hist.at<Vec3f>(i)[c];
			}
		}
	}
	Mat diff_cdf(256,256,CV_32FC3);
	for (int i = 0; i < 180; ++i)
		for (int j = 0; j < 180; ++j)
			diff_cdf.at<Vec3f>(i,j)[0] = src_cdf.at<Vec3f>(i)[0] - dst_cdf.at<Vec3f>(j)[0];
	for (int c = 1; c < 3; ++c)
	{
		for (int i = 0; i < 256; ++i)
			for (int j = 0; j < 256; ++j)
				diff_cdf.at<Vec3f>(i,j)[c] = src_cdf.at<Vec3f>(i)[c] - dst_cdf.at<Vec3f>(j)[c];
	}
	diff_cdf=abs(diff_cdf);
	
	Mat lut(1, 256, CV_8UC3);
	for (int i = 0; i < 180; ++i)
	{
		float min = diff_cdf.at<Vec3f>(i,0)[0];
		int index = 0;
		for (int j = 1; j < 180; ++j)
		{
			if (min > diff_cdf.at<Vec3f>(i,j)[0])
			{
				min = diff_cdf.at<Vec3f>(i,j)[0];
				index = j;
			}
		}
	lut.at<Vec3b>(i)[0] = static_cast<uchar>(index);
	}

	for (int c = 1; c < 3; ++c)	
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
	
	cvtColor(src, result, COLOR_BGR2HLS);
	vector<Mat> hls, luts;
	split(result, hls);
	split(lut, luts);
	//LUT(result, lut, result);
	LUT(hls[0], luts[0], hls[0]);
	LUT(hls[2], luts[2], hls[2]);
	merge(hls, result);
	cvtColor(result, result, COLOR_HLS2BGR);
	lut.release();
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
	imwrite(imagePrefix+"ResultHS.jpg", res);
	
	src.release();
	dst.release();
	res.release();
	return 0;
}
