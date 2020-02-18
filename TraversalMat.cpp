#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main()

{
	std::cout << "hello opencv!" << std::endl;
	//读取本地的一张图片便显示出来
	//imread后面的文件路径可以根据自己的实际路径修改。

	Mat img = imread("C:/Users/Administrator/Desktop/111.jpg");

	int height = img.rows;
	int width = img.cols * img.channels();
	for (int j = 0; j < height; j++) {
		uchar* data = img.ptr<uchar>(j);
		for (int i = 0; i < width; i++) {
			data[i] = data[i] / 3;
		}
	}

	imshow("test", img);

	//等等待用户按键

	waitKey(0);

	return 0;
}
