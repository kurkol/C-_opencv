#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main()

{
	Mat img = imread("C:/Users/Administrator/Desktop/111.jpg", 0);



	imshow("test", img);

	waitKey(0);

	return 0;
}
