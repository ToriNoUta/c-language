#pragma once
#include<iostream>
#include"opencv2/opencv.hpp"
#include<math.h>
#include<stdlib.h>
#include<vector>
using namespace std;
using namespace cv;


//bool cc(vector<double>& index_1, vector<double>& index_2);

class SSR
{
public:
	SSR();
	//SSR�㷨��Ҫ�������̣�����bmp����ԭʼͼ�����Mat����ͼ��
	Mat SSR_main(string s_impath, string s_imtitle, int c = 80);
	Mat SSR_main(string s_impath, int c = 80);

	//��I��x,y��ת��Ϊdouble��
	Mat change_to_double(Mat& I_xy);

	 //ȷ�����ƺ���F(x, y) :����I��x, y�������F(x, y)
	Mat creat_F_xy(Mat& I_xy,int c);

	//���빫ʽȷ���㷨���������I(x,y)��F(x,y),���r(x,y)
	void SSR_caculate(Mat& I_xy, Mat& F_xy,Mat& r_xy);

	//����������ͼ��r(x,y)ת����ʵ��������r(x,y),���R(x,y)
	void chang_exp(Mat& r_xy, Mat& R_xy);

	//ͼ�������������
	void liner_drawing(Mat& R_xy);

	Mat change_to_uchar(Mat& R_xy);

	~SSR();
};

