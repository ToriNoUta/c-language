#pragma once
#include"MSR.h"
class MSRCR
{
public:
	MSRCR();
	//MSRCR������ɫ�ָ��Ķ�߶�Retinex�㷨�����̣�������ԭͼ���MSR�㷨����ͼ�����MSRCR�㷨����ͼ��
	Mat MSRCR_main(Mat& MSR_result, string s_impath); 
	~MSRCR();
};

