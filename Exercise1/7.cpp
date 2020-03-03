#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main()

{
	Mat img = imread("C:/Users/Administrator/Desktop/111.jpg");
	cv::Point pt;
	pt.x = 10;
	pt.y = 10;
	circle(img, pt, 200, CV_RGB(255, 0, 0), 1, 8, 0);

	line(img, pt1, pt2, CV_RGB(255, 0, 0), 1, 8, 0);

	cv::Rect rect;
	rect.x = 10;
	rect.y = 10;
	rect.width;
	rect.height;
	rectangle(img, rect, CV_RGB(255, 0, 0), 1, 8, 0);

	waitKey(0);

	return 0;
}
