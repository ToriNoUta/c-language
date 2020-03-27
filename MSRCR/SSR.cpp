#include "SSR.h"


SSR::SSR()
{
}

//SSR�㷨��Ҫ�������̣�����bmp����ԭʼͼ�񼰳߶ȳ���c�����Mat����ͼ��
Mat SSR::SSR_main(string s_impath, int c)
{


	//�ɵó�����ĳ��� {
	Mat  I_xy = imread(s_impath, IMREAD_UNCHANGED);
	if (I_xy.empty())cout << "false";

	string windowName = "1.bmpԭʼͼ��";
	namedWindow(windowName, WINDOW_AUTOSIZE);
	//normalize(R_xy, R_xy, 1.0, 0.0, NORM_MINMAX);//��һ��0~1֮��
	imshow(windowName, I_xy);
	waitKey(0);

	Mat I_xy_d(I_xy.rows, I_xy.cols, CV_64FC1);
	if (I_xy.dims >= 3)
		I_xy_d.create(I_xy.rows, I_xy.cols, CV_64FC3);
	//��I(x,y)��ֵ����Mat����
	I_xy.convertTo(I_xy_d, I_xy_d.type(), 1, 0);
	SSR ssr;
	//ȷ�����ƺ���F(x,y):����I��x,y���ͻ��ƺ����ĳ߶ȳ���c�����F(x,y)
	Mat F_xy = ssr.creat_F_xy(I_xy_d, c);
	//���빫ʽȷ���㷨���������I(x,y)��F(x,y),���r(x,y)
	//t(x,y)=G(x,y)*F(x,y)
	//r(x,y)=log(I(x,y))-log(t(x,y))
	Mat t_xy(I_xy_d.size(), I_xy_d.type());
	filter2D(I_xy_d, t_xy, I_xy_d.depth(), F_xy);
	//��ʾ�ն�ͼ��
	windowName = "1.bmp���ն�ͼ��";
	namedWindow(windowName, WINDOW_AUTOSIZE);
	normalize(t_xy, t_xy, 1.0, 0.0, NORM_MINMAX);//��һ��0~1֮��
	imshow(windowName, t_xy);
	waitKey(0);
	Mat r_xy(I_xy_d.size(), I_xy_d.type());
	Mat I_xy_d_log(I_xy_d.size(), I_xy_d.type());
	Mat t_xy_log(I_xy_d.size(), I_xy_d.type());
	log(I_xy_d, I_xy_d_log);
	log(t_xy, t_xy_log);
	r_xy = I_xy_d_log - t_xy_log;
	Mat R_xy(r_xy.size(), r_xy.type());
	//����������ͼ��r(x,y)ת����ʵ����
	exp(r_xy, R_xy);
	Mat R_xy_u = ssr.change_to_uchar(R_xy);
	windowName = "c=80ʱ 1.bmp��Retinex�㷨����ͼ��";
	namedWindow(windowName, WINDOW_AUTOSIZE);
	//normalize(R_xy, R_xy, 1.0, 0.0, NORM_MINMAX);//��һ��0~1֮��
	imshow(windowName, R_xy_u);
	waitKey(0);
	//����ĳ���ĩβ }
	return R_xy_u;

}


//SSR�㷨��Ҫ�������̣�����bmp����ԭʼͼ�񼰳߶ȳ���c�����Mat����ͼ��
Mat SSR::SSR_main(string s_impath, string s_imtitle, int c)
{

	//�ɵó�����ĳ��� {
	Mat  I_xy = imread(s_impath, IMREAD_UNCHANGED);
	if (I_xy.empty())cout << "false";

	string windowName = "1.bmp";
	namedWindow(windowName, WINDOW_AUTOSIZE);
	//normalize(I_xy_d, I_xy_d, 1.0, 0.0, NORM_MINMAX);//��һ��0~1֮��
	imshow("1.bmp", I_xy);
	waitKey(0);

	Mat I_xy_d(I_xy.rows, I_xy.cols, CV_64FC1);
	if (I_xy.dims >= 3)
		I_xy_d.create(I_xy.rows, I_xy.cols, CV_64FC3);
	//��I(x,y)��ֵ����Mat����
	I_xy.convertTo(I_xy_d, I_xy_d.type(), 1, 0);
	


	SSR ssr;
	//ȷ�����ƺ���F(x,y):����I��x,y���ͻ��ƺ����ĳ߶ȳ���c�����F(x,y)
	Mat F_xy = ssr.creat_F_xy(I_xy_d, c);
	//���빫ʽȷ���㷨���������I(x,y)��F(x,y),���r(x,y)
	//t(x,y)=G(x,y)*F(x,y)
	//r(x,y)=log(I(x,y))-log(t(x,y))
	Mat t_xy(I_xy_d.size(), I_xy_d.type());
	filter2D(I_xy_d, t_xy, I_xy_d.depth(), F_xy);
	//��ʾ�ն�ͼ��
	windowName = "1.bmp���ն�ͼ��";
	namedWindow(windowName, WINDOW_AUTOSIZE);
	normalize(t_xy, t_xy, 1.0, 0.0, NORM_MINMAX);//��һ��0~1֮��
	imshow(windowName, t_xy);
	waitKey(0);
	Mat r_xy(I_xy_d.size(), I_xy_d.type());
	Mat I_xy_d_log(I_xy_d.size(), I_xy_d.type());
	Mat t_xy_log(I_xy_d.size(), I_xy_d.type());
	log(I_xy_d, I_xy_d_log);
	log(t_xy, t_xy_log);
	r_xy = I_xy_d_log - t_xy_log;
	Mat R_xy(r_xy.size(), r_xy.type());
	//����������ͼ��r(x,y)ת����ʵ����
	exp(r_xy, R_xy);
	//normalize(I_xy_d, I_xy_d, 1.0, 0.0, NORM_MINMAX);//��һ��0~1֮��
	/*Mat R_xy(r_xy.size(), r_xy.type());*/
	//ssr.liner_drawing(R_xy);
	Mat R_xy_u = ssr.change_to_uchar(R_xy);
	windowName = s_imtitle;
	namedWindow(windowName, WINDOW_AUTOSIZE);
	//normalize(R_xy, R_xy, 1.0, 0.0, NORM_MINMAX);//��һ��0~1֮��
	imshow(windowName, R_xy_u);
	waitKey(0);
	//����ĳ���ĩβ }

	


	return R_xy_u;
	//string result = "2.bmp";
	//imwrite(result, R_xy_u);
}

//��I��x,y��ת��ΪCV_8U��
Mat SSR::change_to_uchar(Mat& R_xy)
{
	//�����������ά�������洢ת����ͼ�����ݵ�Mat��
	Mat change(R_xy.rows, R_xy.cols, CV_8UC1);
	if (R_xy.dims >= 3)
		change.create(R_xy.rows, R_xy.cols, CV_8UC3);
	//��I(x,y)��ֵ����Mat����
	R_xy.convertTo(change, change.type(), 1, 0);
	/*change = I_xy;*/
	return change;
}


//��I��x,y��ת��Ϊdouble��
Mat SSR::change_to_double(Mat& I_xy)
{
	//�����������ά�������洢ת����ͼ�����ݵ�Mat��
	Mat change(I_xy.rows, I_xy.cols, CV_64FC1);
	if (I_xy.dims >= 3)
		change.create(I_xy.rows, I_xy.cols, CV_64FC3);
	//��I(x,y)��ֵ����Mat����
	I_xy.convertTo(change,change.type(),1,0);
	/*change = I_xy;*/
	return change;
}

//ȷ�����ƺ���F(x, y) :����I��x, y���ͻ��ƺ����ĳ߶ȳ���c�����F(x, y)
Mat SSR::creat_F_xy(Mat& I_xy,int c)
{
	//����F(x,y)��Ԫ�صļӺ�
	double ans = 0;
	//��һ������v
	double v = 0;
	if (I_xy.dims = 2){
		Mat F_xy(c, c, CV_64FC1);
		for (int x = 0; x < c; x++){
			for (int y = 0; y < c; y++)
			{
				double ex = ((-1)*((x*x) + (y*y)) / (2.0 * (c * c)));
				F_xy.at<double>(x, y) = exp(ex);
				ans += exp(ex);
			}
		}
		v = 1 / ans;
		F_xy = F_xy*v;
		return F_xy;
	}
	else if (I_xy.dims >= 3){
		Mat F_xy(c, c, CV_64FC3);
		for (int x = 0; x < c; x++){
			for (int y = 0; y < c; y++)
			{
				double ex = ((-1)*((x*x) + (y*y)) / (2.0 * (c * c)));
				Vec3d temp;
				temp[0] = exp(ex);
				temp[1] = exp(ex);
				temp[2] = exp(ex);
				F_xy.at<Vec3d>(x, y) = temp;
				ans += exp(ex);
			}
		}
		v = 1 / ans;
		F_xy = F_xy*v;
		return F_xy;
	}


	
}

//���빫ʽȷ���㷨���������I(x,y)��F(x,y),���r(x,y)
void SSR::SSR_caculate(Mat& I_xy,Mat& F_xy,Mat& r_xy)
{
	//t(x,y)=G(x,y)*S(x,y)
	//r(x,y)=log(I(x,y))-log(t(x,y))
	Mat t_xy(I_xy.size(),I_xy.type());
	filter2D(I_xy, t_xy, I_xy.depth(), F_xy);

	string windowName = "����ͼ��.bmp";
	namedWindow(windowName, WINDOW_AUTOSIZE);
	normalize(t_xy, t_xy, 1.0, 0.0, NORM_MINMAX);//��һ��0~1֮��
	imshow(windowName, t_xy);
	waitKey(0);

	Mat I_xy_log(I_xy.size(), I_xy.type());
	Mat t_xy_log(I_xy.size(), I_xy.type());
	log(I_xy, I_xy_log);
	log(t_xy, t_xy_log);
	r_xy = I_xy_log - t_xy_log;

	
}


//����������ͼ��r(x,y)ת����ʵ��������r(x,y),���R(x,y)
void SSR::chang_exp(Mat& r_xy,Mat& R_xy)
{
	vector<double> index;
	exp(r_xy, R_xy);

}

//ͼ�������������
void SSR::liner_drawing(Mat& R_xy)
{
	/*vector<double> index;*/
	//��ȡR��x,y����Ԫ�������Сֵ
	double minVal, maxVal;
	minMaxIdx(R_xy, &minVal, &maxVal);
	if (R_xy.dims = 2){
		for (int x = 0; x < R_xy.rows; x++){
			for (int y = 0; y < R_xy.cols; y++)
			{
				//255��((R(x,y)-minVal)/(maxVal-minVal))
				double temp = R_xy.at<double>(x, y);
				temp = 255.0*(temp - minVal);
				double result = temp/(maxVal-minVal);
				R_xy.at<double>(x, y) = result;
			}
		}
	}
	else if (R_xy.dims >= 3){
		for (int x = 0; x < R_xy.rows; x++){
			for (int y = 0; y < R_xy.cols; y++)
			{
				Vec3d temp = R_xy.at<Vec3d>(x, y);
				Vec3d result;
				temp[0] = 255.0*(temp[0] - minVal);
				result[0] = temp[0] / (maxVal - minVal);
				temp[1] = 255.0*(temp[1] - minVal);
				result[1] = temp[1] / (maxVal - minVal);
				temp[2] = 255.0*(temp[2] - minVal);
				result[2] = temp[2] / (maxVal - minVal);
				R_xy.at<Vec3d>(x, y) = result;
			}
		}
	}
	return;
}

SSR::~SSR()
{
}
