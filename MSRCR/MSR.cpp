#include "MSR.h"
#include"Im_Quality_Evaluation.h"

MSR::MSR()
{
}

//MSR(3�߶�)�㷨������
Mat MSR::MSR_main(string s_impath,int flag=0)
{
	vector<double> index;
	//��õ��и�3����ͬ�ĵ��߶�SSR�㷨���
	int c[] = { 15, 80, 300 };
	SSR ssr;
	Mat ssr_result[3];
	string s_imtitle[] = { "c=15ʱ�ĵ��߶�Retinex�㷨����ͼ��", "c=80ʱ�ĵ��߶�Retinex�㷨����ͼ��", "c=300ʱ�ĵ��߶�Retinex�㷨����ͼ��" };
	for (int s = 0; s < 3; s++)
	{
		ssr_result[s] = ssr.SSR_main(s_impath, s_imtitle[s], c[s]);
	}

	//���۴���С�߶�SSR������ͼ������
	string im_name[] = { "С�߶�(c=15)SSR_RESULT", "�г߶�(c=80)SSR_RESULT", "��߶�(c=300)SSR_RESULT" };
	Im_Quality_Evaluation Iqe;
	for(int s = 0; s < 3; s++ )
	{
		Iqe.mean_std(ssr_result[s], im_name[s]);
		Iqe.im_entropy(ssr_result[s]);
	}

	//�����߶�SSR�㷨���ת��Ϊdouble�ͼ�Ȩ���
	//Ȩֵ
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


//MSR(3�߶�)�㷨������
Mat MSR::MSR_main(string s_impath)
{

	vector<double> index;

	//��õ��и�3����ͬ�ĵ��߶�SSR�㷨���
	int c[] = {15,80,300};
	SSR ssr;
	Mat ssr_result[3];
	string s_imtitle[] = { "c=15ʱ�ĵ��߶�Retinex�㷨����ͼ��", "c=80ʱ�ĵ��߶�Retinex�㷨����ͼ��", "c=300ʱ�ĵ��߶�Retinex�㷨����ͼ��" };
	for (int s = 0; s < 3; s++)
	{
		ssr_result[s] = ssr.SSR_main(s_impath, s_imtitle[s], c[s]);
	}

	//����ԭͼ������
	Mat  I_xy = imread(s_impath, IMREAD_UNCHANGED);
	if (I_xy.empty())cout << "false";
	Im_Quality_Evaluation Iqe;
	Iqe.mean_std(I_xy,"ԭͼ��");
	Iqe.im_entropy(I_xy);

	//���۴���С�߶�SSR������ͼ������
	string im_name[] = { "С�߶�(c=15)SSR_RESULT", "�г߶�(c=80)SSR_RESULT", "��߶�(c=300)SSR_RESULT" };
	for (int s = 0; s < 3; s++)
	{
		Iqe.mean_std(ssr_result[s], im_name[s]);
		Iqe.im_entropy(ssr_result[s]);
	}

	//�����߶�SSR�㷨���ת��Ϊdouble�ͼ�Ȩ���
	//Ȩֵ
	double W[] = { 1.0 / 3, 1.0 / 3, 1.0 / 3 };
	Mat ssr_result_double = ssr.change_to_double(ssr_result[0]);
	Mat ssr_ans(ssr_result_double.size(), ssr_result_double.type());
	ssr_ans = (ssr_ans+ssr_result_double);
	for (int s = 1; s < 3; s++)
	{
		ssr_result_double=ssr.change_to_double(ssr_result[s]);
		ssr_ans += W[s] * ssr_result_double;
	}
	
	//gain/offset������/ƫ�ƣ�������ͼ����������
	ssr_ans = ssr_ans*192.0 + (-30);
	/*ssr[0].liner_drawing(ssr_ans);*/
	//������������ع�һ����0~255֮��
	//��ȡR��x,y����Ԫ�������Сֵ
	double minVal, maxVal;
	minMaxIdx(ssr_ans, &minVal, &maxVal);
	//result=255.0*(R_xy-R_xy_min)/(R_xy_max-R_xy_min)
	Mat temp = (ssr_ans - minVal) / (maxVal - minVal);
	Mat liner_drawing_result = temp*255.0;
	//����������ת��ΪCV_8U����
	Mat R_xy_u = ssr.change_to_uchar(liner_drawing_result);
	string windowName = "1.bmp��3�߶�Retinex�㷨�����Ȩ��ͺ�Ĵ���ͼ��";
	namedWindow(windowName, WINDOW_AUTOSIZE);
	//normalize(R_xy, R_xy, 1.0, 0.0, NORM_MINMAX);//��һ��0~1֮��
	imshow(windowName, R_xy_u);
	waitKey(0);
	return R_xy_u;
}



MSR::~MSR()
{
}
