#include"threadpool.hpp"
#include<stdio.h>
bool handler(int data)
{
	srand((unsigned long)time(NULL));
	int n=rand()%5;
	printf("Thread :%p Run Task: %d--sleep %d sec\n",pthread_self(),data,n);
	sleep(n);
	return true;
}

int main()
{
	ThreadPool pool;
	pool.PoolInit();
	for(int i=0;i<10;i++)
	{
		ThreadTask *tt=new ThreadTask(i,handler);
		pool.PushTask(tt);
		
	}
	pool.PoolQuit();
	return 0;
}
