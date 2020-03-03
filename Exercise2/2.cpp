#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {

	Mat  dst, labels, stats, centroids, src_color;

	cv::Mat src = imread("C:/Users/Administrator/Desktop/222.png", 0);

	threshold(src, dst, 129, 255, THRESH_BINARY);

	int num = connectedComponentsWithStats(dst, labels, stats, centroids, 8, CV_32S);

	vector<Vec3b> color(num + 1);
	color[0] = Vec3b(0, 0, 0);

	for (int m = 1; m <= num; m++) {
		color[m] = Vec3b(rand() % 256, rand() % 256, rand() % 256);
	}


	src_color = Mat::zeros(labels.size(), CV_8UC3);

	for (int x = 0; x < labels.rows; x++)
		for (int y = 0; y < labels.cols; y++)
		{
			int label = labels.at<int>(x, y);
			src_color.at<Vec3b>(x, y) = color[label];
		}

	imshow("src_color", src_color);
	cout << "stats:" << stats << endl;
	cout << "centroids:" << centroids << endl;

	waitKey(0);

	return 0;
}
