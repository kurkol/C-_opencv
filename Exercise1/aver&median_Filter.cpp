#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;


// =================================== global varibales declaration section ======================
//    Describe: global varibales 全局变量
// ========================================================================================
Mat srcImage, dstImage0, dstImage1, dstImage2, dstImage3;
int medianBlurValue = 5; //中值滤波参数值

int gaussianBlurValue = 6; //高斯滤波内核值


// ================================== global function declaration section ==========================
//    Describe: global function
// =============================================================================================
// the callback function of TrackBar --- 轨迹条回调函数
static void onMedianBlur(int, void *);  //中值滤波

static void onGaussianBlur(int, void *); //高斯滤波

//添加椒盐噪声
Mat addSaltNoise(const Mat srcImage, int n)
{
	Mat dstImage = srcImage.clone();
	for (int k = 0; k < n; k++)
	{
		//随机取值行列  
		int i = rand() % dstImage.rows;
		int j = rand() % dstImage.cols;
		//图像通道判定  
		if (dstImage.channels() == 1)
		{
			dstImage.at<uchar>(i, j) = 255;       //盐噪声  
		}
		else
		{
			dstImage.at<Vec3b>(i, j)[0] = 255;
			dstImage.at<Vec3b>(i, j)[1] = 255;
			dstImage.at<Vec3b>(i, j)[2] = 255;
		}
	}
	for (int k = 0; k < n; k++)
	{
		//随机取值行列  
		int i = rand() % dstImage.rows;
		int j = rand() % dstImage.cols;
		//图像通道判定  
		if (dstImage.channels() == 1)
		{
			dstImage.at<uchar>(i, j) = 0;     //椒噪声  
		}
		else
		{
			dstImage.at<Vec3b>(i, j)[0] = 0;
			dstImage.at<Vec3b>(i, j)[1] = 0;
			dstImage.at<Vec3b>(i, j)[2] = 0;
		}
	}
	return dstImage;
}

//均值滤波
void AverFiltering(const Mat &src, Mat &dst) {
	if (!src.data) return;
	//at访问像素点
	for (int i = 1; i<src.rows; ++i)
		for (int j = 1; j < src.cols; ++j) {
			if ((i - 1 >= 0) && (j - 1) >= 0 && (i + 1)<src.rows && (j + 1)<src.cols) {//边缘不进行处理
				dst.at<Vec3b>(i, j)[0] = (src.at<Vec3b>(i, j)[0] + src.at<Vec3b>(i - 1, j - 1)[0] + src.at<Vec3b>(i - 1, j)[0] + src.at<Vec3b>(i, j - 1)[0] +
					src.at<Vec3b>(i - 1, j + 1)[0] + src.at<Vec3b>(i + 1, j - 1)[0] + src.at<Vec3b>(i + 1, j + 1)[0] + src.at<Vec3b>(i, j + 1)[0] +
					src.at<Vec3b>(i + 1, j)[0]) / 9;
				dst.at<Vec3b>(i, j)[1] = (src.at<Vec3b>(i, j)[1] + src.at<Vec3b>(i - 1, j - 1)[1] + src.at<Vec3b>(i - 1, j)[1] + src.at<Vec3b>(i, j - 1)[1] +
					src.at<Vec3b>(i - 1, j + 1)[1] + src.at<Vec3b>(i + 1, j - 1)[1] + src.at<Vec3b>(i + 1, j + 1)[1] + src.at<Vec3b>(i, j + 1)[1] +
					src.at<Vec3b>(i + 1, j)[1]) / 9;
				dst.at<Vec3b>(i, j)[2] = (src.at<Vec3b>(i, j)[2] + src.at<Vec3b>(i - 1, j - 1)[2] + src.at<Vec3b>(i - 1, j)[2] + src.at<Vec3b>(i, j - 1)[2] +
					src.at<Vec3b>(i - 1, j + 1)[2] + src.at<Vec3b>(i + 1, j - 1)[2] + src.at<Vec3b>(i + 1, j + 1)[2] + src.at<Vec3b>(i, j + 1)[2] +
					src.at<Vec3b>(i + 1, j)[2]) / 9;
			}
			else {//边缘赋值
				dst.at<Vec3b>(i, j)[0] = src.at<Vec3b>(i, j)[0];
				dst.at<Vec3b>(i, j)[1] = src.at<Vec3b>(i, j)[1];
				dst.at<Vec3b>(i, j)[2] = src.at<Vec3b>(i, j)[2];
			}
		}
}

// ================================== main() function ===================================

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    

    // read the original image 载入原图
    srcImage = imread("C:/Users/Administrator/Desktop/222.jpg",1);
    // exception handling 异常处理
    if(!srcImage.data) {printf("Errpr: we can't read the image 1.jpg!"); return false;}
   
    
    // show the original image 显示原图
    namedWindow("the original image");
    imshow("the original image", srcImage);

	//加椒盐噪声
	Mat dstImage0 = addSaltNoise(srcImage, 3000);
	imshow("添加椒盐噪声的图像", dstImage0);
    
    // ---------------------------- Median Blur 中值滤波 --------------------------------
    // create a new window 创建窗口
    namedWindow("the median blur image");
    // create a TrackBar 创建轨迹条
    createTrackbar("参数值", "the median blur image", &medianBlurValue, 50, onMedianBlur);
    onMedianBlur(medianBlurValue, 0);
    
	// ---------------------------- 均值滤波 --------------------------------
	Mat image1(srcImage.size(), srcImage.type());
	AverFiltering(srcImage, image1);
	imshow("自定义均值滤波", image1);
	// ---------------------------- Gaussian Blur 高斯滤波 ------------------------------
	// create a new window 创建窗口
	namedWindow("the gaussian blur image");
	// create a TrackBar 创建轨迹条
	createTrackbar("内核值", "the gaussian blur image", &gaussianBlurValue, 40, onGaussianBlur);
	onGaussianBlur(gaussianBlurValue, 0);

	// output some helpful infomation
	cout << endl << "\t ok! now please change the TRACKBAR to observe the result of the image~ \n\n"
		<< "\t if you type 'q', the program will quit! \n"
		<< "\n\n\t\t\t\t by ZHHJemotion";
	while (char(waitKey(1)) != 'q') {}
 


    waitKey(0);
    
    return 0;
}



// ============================ onMedianBlur() Funciton ===============================
//    Describe: the callback of the median blur 中值滤波的回调函数
// ====================================================================================
static void onMedianBlur(int, void *)
{
    medianBlur(srcImage, dstImage1, medianBlurValue*2+1);
    imshow("the median blur image", dstImage1);
}

// =========================== onGaussianBlur() Function ============================
//    Describe: the callback of the guassian blur 高斯滤波的回调函数
// ==================================================================================
static void onGaussianBlur(int, void *)
{
	GaussianBlur(srcImage, dstImage3, Size(gaussianBlurValue * 2 + 1, gaussianBlurValue * 2 + 1), 0, 0);
	imshow("the gaussian blur image", dstImage3);
}
