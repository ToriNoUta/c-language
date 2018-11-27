#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<assert.h>
//在杨氏矩阵中查找某个数，时间复杂度为O（N）
int yang_arr_serch(int arr_[3][3],int key_, int lin_,int row_)
{
	assert(arr_);
	int lin_1 = 0;
	int row_1 = row_-1;
	int result_ = 0;
	while (lin_1 < lin_&&row_1 >= 0)
	{
		if (key_>arr_[lin_1][row_1])
		{
			lin_1++;
			continue;
		}
			else if (key_ < arr_[lin_1][row_1])row_1--;
			else { result_ = 1; break; }
	}
	return result_;
}
int main()
{
	int key = 0;
	int result = 0;
	int yang[3][3] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	printf("请传入一个要在矩阵中寻找的数:\n");
	scanf("%d", &key);
	result = yang_arr_serch(yang, key, sizeof(yang)/sizeof(yang[0]),sizeof(yang[0])/sizeof(yang[0][0]));
	if (result == 1)
	{
		printf("找到目标\n");

	}
	else printf("未找到目标\n");
	return 0;
}