#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<assert.h>

//使用位运算寻找整型数组中不成对的数
int serch_arr_alone_int(int* a_, int size_)
{
	assert(a_);
	int result_ = 0;
	int i_ = 0;
	for (i_ = 0; i_ < size_; i_++)
	{
		result_ ^= a_[i_];
	}
	if (size_ % 2 == 0)
	{
		if (result_ == 0)
		{
			printf("该数组中没有不成对的数\n");
			return 0;
		}
		else
		{
			printf("该数组不符合要求\n");
			return 0;
		}
	}
	return result_;
}

int main()
{
	int arr[] = { 1, 2, 2, 3, 5, 1, 5};
	int result = serch_arr_alone_int(arr, sizeof(arr) / sizeof(arr[0]));
	printf("该数组中不成对的数为：%d", result);
	return 0;
}