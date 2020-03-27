#include "Im_Quality_Evaluation.h"


Im_Quality_Evaluation::Im_Quality_Evaluation()
{
}

//��ͼ���ֵ�ͱ�׼�����ͼ�񣬴�ӡͼ���ֵ�ͱ�׼��
void Im_Quality_Evaluation::mean_std(Mat& im_input,string im_name)
{
	Mat im_mean, im_std;
	cout << "**************************" << endl;
	meanStdDev(im_input, im_mean, im_std);
	cout << im_name << endl;
	cout << "��ֵ��" << im_mean << endl;
	cout << "��׼�" << im_std << endl;
}

//��ͼ����Ϣ�أ�����ͼ�񣬴�ӡͼ����Ϣ��
void Im_Quality_Evaluation::im_entropy(Mat& im_input)
{
	//����ͼ��ֱ��ͼȻ�����ͼ�����ظ����õ��Ҷ����ظ���
	//ͼ�����ظ���
	int vec_num = im_input.rows*im_input.cols;
	MatND dstHist;//�õ���ֱ��ͼ     
	int dims = 1;//�õ���ֱ��ͼ��ά�� �Ҷ�ͼ��ά��Ϊ1����ɫͼ��Ϊ3ά
	float hranges[2] = { 0, 255 };
	const float *ranges[] = { hranges};   // ������ҪΪconst���ͣ���ά��������ָ��ÿ������ķ�Χ  
	int size = 256;//ֱ��ͼ������������� �������걻�ֳ�256��
	int channels = 0;//ͼ���ͨ�� �Ҷ�ͼ��ͨ����Ϊ0,��ɫͼ���ͨ������Ϊ0,1,2

	string s_BGR_H[] = { "Bͨ����Ϣ�أ�", "Gͨ����Ϣ�أ�", "Rͨ����Ϣ�أ�" };
	//����ͼ��BGR��Ϣ��
	//Bͨ��
	calcHist(&im_input, 1, &channels, Mat(), dstHist, dims, &size, ranges);
	getH(dstHist, vec_num, s_BGR_H[0]);
	//Gͨ��
	channels = 1;
	calcHist(&im_input, 1, &channels, Mat(), dstHist, dims, &size, ranges);
	getH(dstHist, vec_num, s_BGR_H[1]);
	//Rͨ��
	channels = 2;
	calcHist(&im_input, 1, &channels, Mat(), dstHist, dims, &size, ranges);
	getH(dstHist, vec_num, s_BGR_H[2]);
	cout << "**************************" << endl;
	cout << endl;
}

//��Ҷ�ͼ�����Ϣ�أ�����Ҷ�ͼ��ֱ��ͼ��ͼ��Ԫ�ظ�������ӡ��õĻҶ�ͼ����Ϣ��
void Im_Quality_Evaluation::getH(Mat&dstHist, int vec_num, string s_BGR_H)
{
	//�Ҷ�ֱ��ͼ����ͼ��Ԫ�ظ�������Ϣ�Ҷȼ�����
	Mat Pi(dstHist.size(), CV_64FC1);
	Pi = dstHist / vec_num;
	//���ݹ�ʽ����Ϣ�أ�H = - ��(Pi * log(Pi))
	Mat Pi_log(Pi.size(), Pi.type());
	log(Pi, Pi_log);
	Mat temp(Pi.size(), Pi.type());
	temp = Pi.mul(Pi_log);

	temp = -temp;
	SSR ssr;
	Mat temp_d = ssr.change_to_double(temp);
	//cout << temp_d << endl;
	double ans = 0;
	for (int x = 0; x < temp_d.rows; x++){
		for (int y = 0; y < temp_d.cols; y++){
			double t = temp_d.at<double>(x, y);
			if (t >= 0)ans += t;
		}
	}
	cout << s_BGR_H << ans << endl;
}

Im_Quality_Evaluation::~Im_Quality_Evaluation()
{
}
