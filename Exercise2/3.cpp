#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	
	Mat  dst,labels, stats, centroids, src_color;
	cv::Rect rect;

	cv::Mat src = imread("C:/Users/Administrator/Desktop/222.png", 0);

	threshold(src, dst, 129, 255, THRESH_BINARY);

	int num = connectedComponentsWithStats(dst, labels, stats, centroids,8, CV_32S);

	cout << "轮廓数" << num << endl;
	vector<Vec3b> color(num + 1);
	color[0] = Vec3b(0, 0, 0);

	int result = 0;
	for (int m = 1; m <= num; m++) {
		color[m] = Vec3b(rand() % 256, rand() % 256, rand() % 256);
		if (stats.at<int>(m - 1, CC_STAT_AREA) > 1500) {
			result++;
		}

			
	}

	src_color = Mat::zeros(labels.size(), CV_8UC3);
	for (int x = 0; x < labels.rows; x++)
		for (int y = 0; y < labels.cols; y++)
		{
			int label = labels.at<int>(x, y);
			src_color.at<Vec3b>(x, y) = color[label];
		}





	cout << "硬币数：" << result-1 << endl;

	for (int i = 1; i < stats.rows; i++)
	{
		rect.x = stats.at<int>(i, 0);
		rect.y = stats.at<int>(i, 1);
		rect.width = stats.at<int>(i, 2);
		rect.height = stats.at<int>(i, 3);
		rectangle(src_color, rect, CV_RGB(255, 0, 0), 1, 8, 0);
	}

	imshow("src_color", src_color);

	waitKey(0);

	return 0;
}
