#pragma once
#include"SSR.h"
#include "Im_Quality_Evaluation.h"
class MSR
{
public:
	MSR();
	//MSR��3�߶ȣ��㷨������
	Mat MSR_main(string s_impath,int flag);
	//MSR��3�߶ȣ��㷨������
	Mat MSR_main(string s_impath);
	~MSR();
};

