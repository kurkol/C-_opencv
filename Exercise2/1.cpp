#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main() {

	Mat  dst;

	cv::Mat src = imread("C:/Users/Administrator/Desktop/222.png", 0);

	threshold(src, dst, 129, 255, THRESH_BINARY);


	imshow("dst", dst);


	waitKey(0);

	return 0;
}
