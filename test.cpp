#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main()

{

	//读取本地的一张图片便显示出来
	//imread后面的文件路径可以根据自己的实际路径修改。

	Mat img = imread("C:/Users/Administrator/Desktop/111.jpg");

	imshow("test", img);

	//等等待用户按键

	waitKey(0);

	return 0;
}
