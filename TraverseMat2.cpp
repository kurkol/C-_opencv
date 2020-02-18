#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main()

{
	cv::Mat M6;
	cv::Mat M7;
	M6.create(3, 4, CV_8UC1);
	M7.create(3, 4, CV_8UC3);
	
	for (int j = 0; j < M6.rows; j++) {
		uchar* data = M6.ptr<uchar>(j);
		for (int i = 0; i < M6.cols; i++) {
			data[i] = j;
		}
	}

	for (int j = 0; j < M7.rows; j++) {
		for (int i = 0; i < M7.cols; i++) {
			M7.at<Vec3b>(j, i)[0] = j;
			M7.at<Vec3b>(j, i)[1] = j+1;
			M7.at<Vec3b>(j, i)[2] = j+2;
		}
	}

	std::cout << "M6 =" << std::endl;
	std::cout << M6 << std::endl;
	std::cout << "M7 =" << std::endl;
	std::cout << M7 << std::endl;

	getchar();

	return 0;
}
