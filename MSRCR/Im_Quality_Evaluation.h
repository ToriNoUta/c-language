#pragma once
#include"SSR.h"
class Im_Quality_Evaluation
{
public:
	Im_Quality_Evaluation();
	//�Ҷ�ͼ��õ�
	void getH(Mat&dstHist, int vec_num, string s_BGR_H);
	//��ͼ���ֵ�ͱ�׼�����ͼ�񣬴�ӡͼ���ֵ�ͱ�׼��
	void mean_std(Mat& im_input, string im_name);
	//��ͼ����Ϣ�أ�����ͼ�񣬴�ӡͼ����Ϣ��
	void im_entropy(Mat& im_input);
	~Im_Quality_Evaluation();
};

