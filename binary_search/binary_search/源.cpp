#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>

class search
{
public:
	int act(int *a, int left, int right,int key)
	{
		int mid = (left+right)>>1;
		if (key == a[mid])
			return mid;
		else if (left > right)
			return -1;
		else
		{
			if (a[mid] > key)
				act(a, left, mid - 1, key);
			else if (a[mid] < key)
				act(a, mid+1,right, key);
		}
	};
};


int main()
{
	class search s;
	int a[7] = { 1, 2, 3, 4, 5, 6, 7 };
	std::cout<<s.act(a, 0, 6, 3);
	return 0;
}