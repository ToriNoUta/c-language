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
	//SSR算法主要计算流程：输入bmp类型原始图像，输出Mat类型图像
	Mat SSR_main(string s_impath, string s_imtitle, int c = 80);
	Mat SSR_main(string s_impath, int c = 80);

	//将I（x,y）转换为double型
	Mat change_to_double(Mat& I_xy);

	 //确定环绕函数F(x, y) :输入I（x, y），输出F(x, y)
	Mat creat_F_xy(Mat& I_xy,int c);

	//代入公式确定算法输出：输入I(x,y)和F(x,y),输出r(x,y)
	void SSR_caculate(Mat& I_xy, Mat& F_xy,Mat& r_xy);

	//对数域的输出图像r(x,y)转换到实数域：输入r(x,y),输出R(x,y)
	void chang_exp(Mat& r_xy, Mat& R_xy);

	//图像线性拉伸输出
	void liner_drawing(Mat& R_xy);

	Mat change_to_uchar(Mat& R_xy);

	~SSR();
};

