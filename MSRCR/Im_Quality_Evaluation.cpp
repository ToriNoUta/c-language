#include "Im_Quality_Evaluation.h"


Im_Quality_Evaluation::Im_Quality_Evaluation()
{
}

//求图像均值和标准差：输入图像，打印图像均值和标准差
void Im_Quality_Evaluation::mean_std(Mat& im_input,string im_name)
{
	Mat im_mean, im_std;
	cout << "**************************" << endl;
	meanStdDev(im_input, im_mean, im_std);
	cout << im_name << endl;
	cout << "均值：" << im_mean << endl;
	cout << "标准差：" << im_std << endl;
}

//求图像信息熵：输入图像，打印图像信息熵
void Im_Quality_Evaluation::im_entropy(Mat& im_input)
{
	//计算图像直方图然后除以图像像素个数得到灰度像素概率
	//图像像素个数
	int vec_num = im_input.rows*im_input.cols;
	MatND dstHist;//得到的直方图     
	int dims = 1;//得到的直方图的维数 灰度图的维数为1，彩色图像为3维
	float hranges[2] = { 0, 255 };
	const float *ranges[] = { hranges};   // 这里需要为const类型，二维数组用来指出每个区间的范围  
	int size = 256;//直方图横坐标的区间数 即横坐标被分成256份
	int channels = 0;//图像得通道 灰度图的通道数为0,彩色图像的通道数定为0,1,2

	string s_BGR_H[] = { "B通道信息熵：", "G通道信息熵：", "R通道信息熵：" };
	//计算图像BGR信息熵
	//B通道
	calcHist(&im_input, 1, &channels, Mat(), dstHist, dims, &size, ranges);
	getH(dstHist, vec_num, s_BGR_H[0]);
	//G通道
	channels = 1;
	calcHist(&im_input, 1, &channels, Mat(), dstHist, dims, &size, ranges);
	getH(dstHist, vec_num, s_BGR_H[1]);
	//R通道
	channels = 2;
	calcHist(&im_input, 1, &channels, Mat(), dstHist, dims, &size, ranges);
	getH(dstHist, vec_num, s_BGR_H[2]);
	cout << "**************************" << endl;
	cout << endl;
}

//求灰度图像的信息熵：输入灰度图像直方图和图像元素个数，打印求得的灰度图像信息熵
void Im_Quality_Evaluation::getH(Mat&dstHist, int vec_num, string s_BGR_H)
{
	//灰度直方图除以图像元素个数求信息灰度级概率
	Mat Pi(dstHist.size(), CV_64FC1);
	Pi = dstHist / vec_num;
	//根据公式求信息熵：H = - Σ(Pi * log(Pi))
	Mat Pi_log(Pi.size(), Pi.type());
	log(Pi, Pi_log);
	Mat temp(Pi.size(), Pi.type());
	temp = Pi.mul(Pi_log);

	temp = -temp;
	SSR ssr;
	Mat temp_d = ssr.change_to_double(temp);
	//cout << temp_d << endl;
	double ans = 0;
	for (int x = 0; x < temp_d.rows; x++){
		for (int y = 0; y < temp_d.cols; y++){
			double t = temp_d.at<double>(x, y);
			if (t >= 0)ans += t;
		}
	}
	cout << s_BGR_H << ans << endl;
}

Im_Quality_Evaluation::~Im_Quality_Evaluation()
{
}
