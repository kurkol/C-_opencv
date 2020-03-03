#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main()

{
	Mat img = imread("C:/Users/Administrator/Desktop/111.jpg");

	int height = img.rows;
	int width = img.cols;
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			uchar average = (img.at<Vec3b>(j, i)[0] + img.at<Vec3b>(j, i)[1] + img.at<Vec3b>(j, i)[2]) / 3;
			uchar threshold=100;
			if (average > threshold) {
				average = 255;
			}
			else {
				average = 0;
			}
			img.at<Vec3b>(j, i)[0] = average;
			img.at<Vec3b>(j, i)[1] = average;
			img.at<Vec3b>(j, i)[2] = average;
		}
	}

	imshow("test", img);


	waitKey(0);

	return 0;
}
