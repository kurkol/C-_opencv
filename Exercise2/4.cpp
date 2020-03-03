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
	VideoCapture cap(0);
	pMOG2 = createBackgroundSubtractorMOG2();
	pMOG2->setDetectShadows(0);
	while (1)
	{
		cv::Mat frame;
		cap.read(frame);
		pMOG2->apply(frame, fgMaskMOG2);
		imshow("Frame", frame);
		imshow("FG Mask MOG 2", fgMaskMOG2);
		waitKey(30);
	}
	return 0;
}
