#include "MSR.h"
#include"Im_Quality_Evaluation.h"

MSR::MSR()
{
}

//MSR(3尺度)算法主流程
Mat MSR::MSR_main(string s_impath,int flag=0)
{
	vector<double> index;
	//求得低中高3个不同的单尺度SSR算法结果
	int c[] = { 15, 80, 300 };
	SSR ssr;
	Mat ssr_result[3];
	string s_imtitle[] = { "c=15时的单尺度Retinex算法处理图像", "c=80时的单尺度Retinex算法处理图像", "c=300时的单尺度Retinex算法处理图像" };
	for (int s = 0; s < 3; s++)
	{
		ssr_result[s] = ssr.SSR_main(s_impath, s_imtitle[s], c[s]);
	}

	//评价大中小尺度SSR处理结果图像质量
	string im_name[] = { "小尺度(c=15)SSR_RESULT", "中尺度(c=80)SSR_RESULT", "大尺度(c=300)SSR_RESULT" };
	Im_Quality_Evaluation Iqe;
	for(int s = 0; s < 3; s++ )
	{
		Iqe.mean_std(ssr_result[s], im_name[s]);
		Iqe.im_entropy(ssr_result[s]);
	}

	//将单尺度SSR算法结果转化为double型加权求和
	//权值
	double W[] = { 1.0 / 3, 1.0 / 3, 1.0 / 3 };


	Mat ssr_result_double = ssr.change_to_double(ssr_result[0]);
	Mat ssr_ans(ssr_result_double.size(), ssr_result_double.type());
	ssr_ans = (ssr_ans + ssr_result_double);


	for (int s = 1; s < 3; s++)
	{
		ssr_result_double = ssr.change_to_double(ssr_result[s]);
		ssr_ans += W[s] * ssr_result_double;
	}

	for (int x = 0; x < ssr_ans.rows; x++)
	{
		for (int y = 0; y < ssr_ans.cols; y++)
		{
			index.push_back(ssr_ans.at<double>(x, y));
		}
	}

	return ssr_ans;
}


//MSR(3尺度)算法主流程
Mat MSR::MSR_main(string s_impath)
{

	vector<double> index;

	//求得低中高3个不同的单尺度SSR算法结果
	int c[] = {15,80,300};
	SSR ssr;
	Mat ssr_result[3];
	string s_imtitle[] = { "c=15时的单尺度Retinex算法处理图像", "c=80时的单尺度Retinex算法处理图像", "c=300时的单尺度Retinex算法处理图像" };
	for (int s = 0; s < 3; s++)
	{
		ssr_result[s] = ssr.SSR_main(s_impath, s_imtitle[s], c[s]);
	}

	//评价原图像质量
	Mat  I_xy = imread(s_impath, IMREAD_UNCHANGED);
	if (I_xy.empty())cout << "false";
	Im_Quality_Evaluation Iqe;
	Iqe.mean_std(I_xy,"原图像");
	Iqe.im_entropy(I_xy);

	//评价大中小尺度SSR处理结果图像质量
	string im_name[] = { "小尺度(c=15)SSR_RESULT", "中尺度(c=80)SSR_RESULT", "大尺度(c=300)SSR_RESULT" };
	for (int s = 0; s < 3; s++)
	{
		Iqe.mean_std(ssr_result[s], im_name[s]);
		Iqe.im_entropy(ssr_result[s]);
	}

	//将单尺度SSR算法结果转化为double型加权求和
	//权值
	double W[] = { 1.0 / 3, 1.0 / 3, 1.0 / 3 };
	Mat ssr_result_double = ssr.change_to_double(ssr_result[0]);
	Mat ssr_ans(ssr_result_double.size(), ssr_result_double.type());
	ssr_ans = (ssr_ans+ssr_result_double);
	for (int s = 1; s < 3; s++)
	{
		ssr_result_double=ssr.change_to_double(ssr_result[s]);
		ssr_ans += W[s] * ssr_result_double;
	}
	
	//gain/offset（增益/偏移）方法对图像像素修正
	ssr_ans = ssr_ans*192.0 + (-30);
	/*ssr[0].liner_drawing(ssr_ans);*/
	//线性拉伸把像素归一化到0~255之间
	//获取R（x,y）中元素最大最小值
	double minVal, maxVal;
	minMaxIdx(ssr_ans, &minVal, &maxVal);
	//result=255.0*(R_xy-R_xy_min)/(R_xy_max-R_xy_min)
	Mat temp = (ssr_ans - minVal) / (maxVal - minVal);
	Mat liner_drawing_result = temp*255.0;
	//线性拉伸结果转变为CV_8U类型
	Mat R_xy_u = ssr.change_to_uchar(liner_drawing_result);
	string windowName = "1.bmp经3尺度Retinex算法结果加权求和后的处理图像";
	namedWindow(windowName, WINDOW_AUTOSIZE);
	//normalize(R_xy, R_xy, 1.0, 0.0, NORM_MINMAX);//归一到0~1之间
	imshow(windowName, R_xy_u);
	waitKey(0);
	return R_xy_u;
}



MSR::~MSR()
{
}
