#pragma once
#include"SSR.h"
class Im_Quality_Evaluation
{
public:
	Im_Quality_Evaluation();
	//灰度图像得到
	void getH(Mat&dstHist, int vec_num, string s_BGR_H);
	//求图像均值和标准差：输入图像，打印图像均值和标准差
	void mean_std(Mat& im_input, string im_name);
	//求图像信息熵：输入图像，打印图像信息熵
	void im_entropy(Mat& im_input);
	~Im_Quality_Evaluation();
};

