#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/stitching.hpp>
#include <iostream>
#include <string>
#include <vector>


using std::cout;
using std::endl;
using std::string;
using std::vector;
using namespace cv;


//优化两图的连接处，使得拼接自然
void OptimizeSeam(Mat& img1, Mat& trans, Mat& dst, int startTop, int startBottom)
{
    int start = MIN(startTop, startBottom);//开始位置，即重叠区域的左边界  

    double processWidth = img1.cols - start;//重叠区域的宽度  
    int rows = dst.rows;
    int cols = img1.cols; //注意，是列数*通道数
    double alpha = 1;//img1中像素的权重  
    for (int i = 0; i < rows; i++)
    {
        uchar* p = img1.ptr<uchar>(i);  //获取第i行的首地址
        uchar* t = trans.ptr<uchar>(i);
        uchar* d = dst.ptr<uchar>(i);
        for (int j = start; j < cols; j++)
        {
            //如果遇到图像trans中无像素的黑点，则完全拷贝img1中的数据
            if (t[j * 3] == 0 && t[j * 3 + 1] == 0 && t[j * 3 + 2] == 0)
            {
                alpha = 1;
            }
            else
            {
                //img1中像素的权重，与当前处理点距重叠区域左边界的距离成正比，实验证明，这种方法确实好  
                alpha = (processWidth - (j - start)) / processWidth;
            }

            d[j * 3] = p[j * 3] * alpha + t[j * 3] * (1 - alpha);
            d[j * 3 + 1] = p[j * 3 + 1] * alpha + t[j * 3 + 1] * (1 - alpha);
            d[j * 3 + 2] = p[j * 3 + 2] * alpha + t[j * 3 + 2] * (1 - alpha);

        }
    }

}

int main(int argc, char** argv)
{
	string imagePrefix = "../data/";
	string Name1, Name2;
	if(argc == 3) 
	{
		Name1 = argv[1];
		Name2 = argv[2];
	}
	else if(argc == 5 && argv[1] == "absolute")
	{
		imagePrefix = argv[2];
		Name1 = argv[3];
		Name2 = argv[4];
	}
	else
	{
		cout << "Incorrect input" << endl;
		return -1;
	}
	
	Mat src1 = imread(imagePrefix+Name1, IMREAD_GRAYSCALE);
	Mat src2 = imread(imagePrefix+Name2, IMREAD_GRAYSCALE);


	if(src1.empty() || src2.empty())
	{
		cout << "Could not open or find the images" << endl;
		return -1;
	}
	Mat dst;
	Mat window = src1(Rect(3200, 0, 101, 101));

	double minVal, maxVal;
	Point minLoc, maxLoc, matchLoc;
	matchTemplate(window, src2, dst, TM_CCORR_NORMED);
	minMaxLoc(dst, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
	matchLoc = maxLoc;
	matchLoc.x = 3500 - matchLoc.x;
	cout << matchLoc << endl;
	window.release();
	src1.release();
	src2.release();	
/*
	Ptr<xfeatures2d::SurfFeatureDetector> detector = xfeatures2d::SurfFeatureDetector::create(5000);//hession矩阵的阈值自己设置
    vector<KeyPoint> key_points_1, key_points_2;//将提取的特征点以keypoint形式存储
    Mat dstImage1, dstImage2;
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce"); //描述匹配特征点    
    vector<DMatch> mach;
    detector->detectAndCompute(src1, Mat(), key_points_1, dstImage1);
    detector->detectAndCompute(src2, Mat(), key_points_2, dstImage2);
    matcher->match(dstImage1, dstImage2, mach);

	//删除错误匹配的特征点
	vector<DMatch> InlierMatches;//定义内点集合
	vector<Point2f> p1, p2;//先把keypoint转换为Point格式
	for (int i = 0; i < mach.size(); i++)
	{
		p1.push_back(key_points_1[mach[i].queryIdx].pt);// pt是position
		p2.push_back(key_points_2[mach[i].trainIdx].pt);
	}
	//RANSAC FindFundamental剔除错误点
	vector<uchar> RANSACStatus;//用以标记每一个匹配点的状态，等于0则为外点，等于1则为内点。
	findFundamentalMat(p1, p2, RANSACStatus, FM_RANSAC);//p1 p2必须为float型
	for (int i = 0; i < mach.size(); i++)
	{
		if (RANSACStatus[i] != 0)
		{
			InlierMatches.push_back(mach[i]); //不等于0的是内点
		}
	}

	vector<Point2f> src1_point, src2_point;
	for (int i = 0; i < InlierMatches.size(); i++)
	{
		src1_point.push_back(key_points_1[InlierMatches[i].queryIdx].pt);
		src2_point.push_back(key_points_2[InlierMatches[i].trainIdx].pt);
	}
	Mat Homography = findHomography(src1_point, src2_point, RANSAC); //计算将p2投影到p1上的单映性矩阵
	Mat Registration;
	warpPerspective(src1, Registration, Homography, Size(src2.cols, src2.rows));
	imwrite(imagePrefix+"Reg.jpg", Registration);
*/
	src1 = imread(imagePrefix+Name1, IMREAD_COLOR);
	src2 = imread(imagePrefix+Name2, IMREAD_COLOR);
	bool try_use_gpu = false;
	Stitcher::Mode mode = Stitcher::PANORAMA;
	vector<Mat> merge;
	merge.push_back(src1);
	merge.push_back(src2);
	Mat pano;
	Ptr<Stitcher> stitcher = Stitcher::create(mode);
    Stitcher::Status status = stitcher->stitch(merge, pano);
	if (status != Stitcher::OK)
    {
        cout << "Can't stitch images, error code = " << int(status) << endl;
        return EXIT_FAILURE;
    }
	imwrite(imagePrefix+"Merge.jpg", pano);
	pano.release();
	src1.release();
	src2.release();
	return 0;
}
