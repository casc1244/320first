#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{

	cv::Mat labelMat;
	cv::Mat statsMat;
	cv::Mat centrMat;
	cv::Mat OpenMat;
	cv::Mat resultMat;
	cv::Mat srcMat = imread("D:\\360downloads\\5.jpg", 0);
	Mat invertImage;
	srcMat.copyTo(invertImage);
	int channels = srcMat.channels();
	int rows = srcMat.rows;
	int col = srcMat.cols;
	cout << channels << " "<<rows<<endl;	
	int cols = srcMat.cols * channels;
	cout << cols << endl;	
	if (srcMat.isContinuous()) {		cols *= rows;         		rows = 1;	}
	uchar* p1;	uchar* p2;	for (int row = 0; row < rows; row++) {
		p1 = srcMat.ptr<uchar>(row);
		p2 = invertImage.ptr<uchar>(row);		for (int col = 0; col < cols; col++) {
			*p2 = 255 - *p1;
			// 取反			
			p2++;			p1++;
		}
	}
	cv::Mat kernel;
	kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	cv::morphologyEx(srcMat, OpenMat, 2, kernel);

	int nComp = cv::connectedComponentsWithStats(OpenMat,
		labelMat,
		statsMat,
		centrMat,
		8,
		CV_32S);

	for (int i = 0; i < nComp; i++)
	{
		cout << "connected Components NO. " << i << endl;
		cout << "pixels = " << statsMat.at<int>(i, 4) << endl;
		cout << "width = " << statsMat.at<int>(i, 2) << endl;
		cout << "height = " << statsMat.at<int>(i, 3) << endl;
		cout << endl;
	}
	cout << " 数量是 = " << nComp - 1 << endl;
	imshow("frame", srcMat);
	moveWindow("frame", 0, 20);
	imshow("OpenMat", OpenMat);
	moveWindow("binaryMat", srcMat.cols, 20);
	moveWindow("results", srcMat.cols * 2, 20);
	waitKey(0);
	return 0;
}