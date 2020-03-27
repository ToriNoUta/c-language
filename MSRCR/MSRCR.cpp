#include "MSRCR.h"


MSRCR::MSRCR()
{
}


//MSRCR������ɫ�ָ��Ķ�߶�Retinex�㷨�����̣�������ԭͼ���MSR�㷨����ͼ�����MSRCR�㷨����ͼ��
Mat MSRCR::MSRCR_main(Mat& MSR_result, string s_impath)
{


	//ԭʼͼ��S(x,y)
	Mat  S_xy = imread(s_impath, IMREAD_UNCHANGED);
	if (S_xy.empty())cout << "false";

	//��ԭͼ����ñ�ɫ�任���ӣ�ɫ�ʻָ����ӣ�c(x,y)���Ƚ���ͼ��ת��ΪDOUBLE�ͣ�
	//Ȼ�󰴹�ʽc(x,y)=46*{log[123*S(x,y)]-log(��iSi(x,y))}�����ɫ�任���ӣ�ɫ�ʻָ����ӣ�
	//SSR�㷨�������
	SSR ssr;
	Mat S_xy_d=ssr.change_to_double(S_xy);

	string windowName = "1.bmpԭͼ��";
	/*namedWindow(windowName, WINDOW_AUTOSIZE);*/
	normalize(S_xy_d, S_xy_d, 1.0, 0.0, NORM_MINMAX);//��һ��0~1֮��
	/*imshow(windowName, S_xy_d);
	waitKey(0);
	*/
	//ͨ������
	vector<Mat> sbgr(S_xy_d.channels());
	Mat sumC1(S_xy_d.size(),CV_64FC1);
	Mat sumC3(S_xy_d.size(), S_xy_d.type());
	split(S_xy_d, sbgr);
	vector<Mat> mbgr(S_xy_d.channels());
	//ͨ�����
	for (int sbgr_chan = 0; sbgr_chan < S_xy_d.channels(); sbgr_chan++)
	{

		sumC1 += sbgr[sbgr_chan];
	}
	for (int mbgr_chan = 0; mbgr_chan < S_xy_d.channels(); mbgr_chan++)
	{
		mbgr[mbgr_chan] = sumC1;
		
	}
	//ͨ���ϳ�
	merge(mbgr, sumC3);
	Mat sumC3_log(S_xy_d.size(), S_xy_d.type());
	Mat S_xy_d_log(S_xy.size(), S_xy.type());
	Mat c_xy(S_xy.size(), S_xy.type());
	S_xy_d=123.0*S_xy_d;
	log(S_xy_d, S_xy_d_log);
	log(sumC3, sumC3_log);
	c_xy = (S_xy_d_log - sumC3_log);


	
	
	//����ɫ�任������MSR�㷨����ڶ�������˵õ�MSRCR�㷨��������
	Mat MSR_result_d = ssr.change_to_double(MSR_result);
	Mat MSR_result_d_log(MSR_result.size(), MSR_result.type());
	normalize(MSR_result_d, MSR_result_d, 1.0, 0.0, NORM_MINMAX);//��һ��0~1֮��
	log(MSR_result_d, MSR_result_d_log);
	Mat r_xy(MSR_result.size(), MSR_result.type());
	r_xy=MSR_result_d_log.mul(c_xy);
	//��r(x,y)ת��ʵ����
	Mat R_xy(r_xy.size(), r_xy.type());
	exp(r_xy, R_xy);

	Mat R_xy_u(R_xy.size(), CV_8UC1);
	if (R_xy.dims >= 3)
		R_xy_u.create(R_xy.size(), CV_8UC3);
	R_xy.convertTo(R_xy_u, R_xy_u.type(), 255, 0);
	windowName = "1.bmp MSRCR�㷨����ͼ��";
	namedWindow(windowName, WINDOW_AUTOSIZE);
	//normalize(R_xy, R_xy, 1.0, 0.0, NORM_MINMAX);//��һ��0~1֮��
	imshow(windowName, R_xy_u);
	waitKey(0);

	return R_xy_u;
}

MSRCR::~MSRCR()
{
}
