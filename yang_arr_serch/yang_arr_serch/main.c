#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<assert.h>
//�����Ͼ����в���ĳ������ʱ�临�Ӷ�ΪO��N��
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
	printf("�봫��һ��Ҫ�ھ�����Ѱ�ҵ���:\n");
	scanf("%d", &key);
	result = yang_arr_serch(yang, key, sizeof(yang)/sizeof(yang[0]),sizeof(yang[0])/sizeof(yang[0][0]));
	if (result == 1)
	{
		printf("�ҵ�Ŀ��\n");

	}
	else printf("δ�ҵ�Ŀ��\n");
	return 0;
}