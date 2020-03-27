#define _CRT_SECURE_NO_WARNINGS 1
#include"SSR.h"
#include"MSR.h"
#include"MSRCR.h"
#include"Im_Quality_Evaluation.h"
int main()
{
	string pathname = "G:\\win32app\\ConsoleApplication1\\4.bmp";
	/*SSR s;
	s.SSR_main(pathname);*/


	MSR m;
	Mat MSR_result = m.MSR_main(pathname);

	MSRCR mcr;
	Mat MSRCR_result = mcr.MSRCR_main(MSR_result, pathname);
	
	//评价MSR处理结果图像质量
	string result_name[] = { "MSR_RESULT", "MSRCR_RESULT" };
	Im_Quality_Evaluation ImQE;
	ImQE.mean_std(MSR_result,result_name[0]);
	ImQE.im_entropy(MSR_result);

	//评价MSRCR处理结果图像质量
	ImQE.mean_std(MSRCR_result, result_name[1]);
	ImQE.im_entropy(MSRCR_result);
	return 0;
}