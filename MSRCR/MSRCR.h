#pragma once
#include"MSR.h"
class MSRCR
{
public:
	MSRCR();
	//MSRCR（带彩色恢复的多尺度Retinex算法主流程）：输入原图像和MSR算法处理图像，输出MSRCR算法处理图像
	Mat MSRCR_main(Mat& MSR_result, string s_impath); 
	~MSRCR();
};

