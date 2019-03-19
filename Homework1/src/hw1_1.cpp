#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <string>

using namespace cv;

using namespace std;

void HLSConverter(const Mat& image, string Name, double PlusH = 0.0, double MulL = 1.0, double MulS = 1.0, string prefix = "../data/")
{
	if(PlusH<0.0 || PlusH>360.0 || MulL<0.0 || MulS<0.0){cout<<"Invalid Range"<<endl; return ;}
	string imageName = Name.substr(0,Name.find('.'));
	string postfix = Name.substr(1,Name.find('.'));
	string wholeName = prefix+Name;
	Mat imageHLS;
	image.copyTo(imageHLS);
	imageHLS.convertTo(imageHLS,CV_32FC3,1/255.0);
	cvtColor(imageHLS, imageHLS, COLOR_BGR2HLS);
	if (PlusH != 0.0)
	{
		for(int i=0;i<imageHLS.rows;++i)
		{
			for(int j=0;j<imageHLS.cols;++j)
			{
				imageHLS.at<Vec3f>(i,j)[0]+=PlusH;
				if(imageHLS.at<Vec3f>(i,j)[0] > 360.0)
				{
					imageHLS.at<Vec3f>(i,j)[0]-=360.0;
				}
				if(imageHLS.at<Vec3f>(i,j)[0] < 0.0)
				{
					imageHLS.at<Vec3f>(i,j)[0]+=360.0;
				}
			}
		}
		char ph[16];
		sprintf(ph,"%.1f",PlusH);
		string phs = ph;
		imageName+=("H+"+phs);
	}
	
	if (MulL != 1.0)
	{
		for(int i=0;i<imageHLS.rows;++i)
		{
			for(int j=0;j<imageHLS.cols;++j)
			{
				imageHLS.at<Vec3f>(i,j)[1]*=MulL;
				if(imageHLS.at<Vec3f>(i,j)[1] > 1.0)
				{
					imageHLS.at<Vec3f>(i,j)[1]=1.0;
				}
			}
		}
		char ml[16];
		sprintf(ml,"%.1f",MulL);
		string mls = ml;
		imageName+=("L*"+mls);
	}

	if (MulS != 1.0)
	{
		for(int i=0;i<imageHLS.rows;++i)
		{
			for(int j=0;j<imageHLS.cols;++j)
			{
				imageHLS.at<Vec3f>(i,j)[2]*=MulS;
				if(imageHLS.at<Vec3f>(i,j)[2] > 1.0)
				{
					imageHLS.at<Vec3f>(i,j)[2]=1.0;
				}
			}
		}
		char ms[16];
		sprintf(ms,"%.1f",MulS);
		string mss = ms;
		imageName+=("S*"+mss);
	}
	
	cvtColor(imageHLS,imageHLS,COLOR_HLS2BGR);
	imageHLS.convertTo(imageHLS,CV_8UC3,255);
	imwrite((prefix+imageName+".jpg"),imageHLS);
	imageHLS.release();
	cout<<"Successfully create "<<(imageName+".jpg")<<endl;
	return ;
}

int main(int argc, char** argv)
{
	string imagePrefix = "../data/";
	string imageName;
	if(argc == 2) 
	{
		imageName = argv[1];
	}
	else if(argc == 4 && argv[1] == "absolute")
	{
		imagePrefix = argv[2];
		imageName = argv[3];
	}
	else
	{
		cout<<"Incorrect input"<<endl;
		return -1;
	}
	
	Mat image = imread(imagePrefix+imageName,IMREAD_COLOR);
	//image = imread(imagePrefix+imageName,IMREAD_COLOR);
	imshow("ZJU",image);
	if(image.empty())
	{
		cout<<"Could not open or find the image"<<endl;
		return -1;
	}
	
	//HLSConverter(image, imageName, 45.0);//PlusH = 45.0
	HLSConverter(image, imageName, 60.0);//PlusH = 60.0
	HLSConverter(image, imageName, 120.0);//PlusH = 120.0
	HLSConverter(image, imageName, 180.0);//PlusH = 180.0
	HLSConverter(image, imageName, 0.0, 0.5);//MulL = 0.5
	//HLSConverter(image, imageName, 0.0, 1.0);//MulL = 1.0
	HLSConverter(image, imageName, 0.0, 1.5);//MulL = 1.5
	HLSConverter(image, imageName, 0.0, 1.0, 0.1);//MulS = 0.1
	HLSConverter(image, imageName, 0.0, 1.0, 0.5);//MulS = 0.5
	HLSConverter(image, imageName, 0.0, 1.0, 0.8);//MulS = 0.8

	image.release();
	return 0;
}
