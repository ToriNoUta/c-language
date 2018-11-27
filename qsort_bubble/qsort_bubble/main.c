#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
//自定义的比较函数
int int_cmp(const void* p1, const void* p2)
{
	return(*(int*)p1 - *(int*)p2);
}

//按字节交换函数
void _swap(void* p1, void* p2, int size)
{
	int i = 0;
	for (i = 0; i<size; i++)
	{
		char tmp = *((char*)p1 + i);
		*((char*)p1 + i) = *((char*)p2 + i);
		*((char*)p2 + i) = tmp;
	}
}

//使用冒泡排序模拟qsort
void bubble(void* base, int count, int size, int(*cmp)(void*, void*))
{
	int i = 0;
	int j = 0;
	for (i = 0; i<count - 1; i++)
	{
		for (j = 0; j<count - i - 1; j++)
		{
			if (cmp((char*)base + j*size, (char*)base + (j + 1)*size)>0)
			{
				_swap((char*)base + j*size, (char*)base + (j + 1)*size, size);
			}
		}
	}
}

int main()
{
	int arr[6] = { 1, 8, 5, 3, 2, 6 };
	bubble(arr, sizeof(arr) / sizeof(arr[0]), sizeof(arr[0]), int_cmp);
	return 0;
}