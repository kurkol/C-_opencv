#include "stdio.h"
#include <iostream> 
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat frame;
Mat fgMaskMOG2;
Ptr<BackgroundSubtractorMOG2> pMOG2;


int main()
{
	cv::Mat img_edge, labels, img_color, stats, centroids;
	VideoCapture cap(0);
	pMOG2 = createBackgroundSubtractorMOG2();
	pMOG2->setDetectShadows(0);
	while (1)
	{
		cv::Mat frame;
		cv::Rect rect;
		cap.read(frame);
		pMOG2->apply(frame, fgMaskMOG2);
		int i, nccomps = cv::connectedComponentsWithStats(fgMaskMOG2, labels, stats, centroids);
		for (int i = 1; i < stats.rows; i++)
		{
			rect.x = stats.at<int>(i, 0);
			rect.y = stats.at<int>(i, 1);
			rect.width = stats.at<int>(i, 2);
			rect.height = stats.at<int>(i, 3);
			rectangle(frame, rect, CV_RGB(255, 0, 0), 1, 8, 0);
		}
		imshow("Frame", frame);
		imshow("FG Mask MOG 2", fgMaskMOG2);
		waitKey(30);
	}


	return 0;
}
