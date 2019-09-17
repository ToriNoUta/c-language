#include<iostream>
#include<queue>
#include<stdlib.h>
#include<pthread.h>
#define NUM 8

class blockQueue{
private:
	std::queue<int> q;
	int cap;
	pthread_mutex_t lock;
	pthread_cond_t full;
	pthread_cond_t empty;
private:
	void lockQueue()
{	
	pthread_mutex_lock(&lock);
}


	void unlockQueue()
{	
	pthread_mutex_unlock(&lock);
}

	void consumer_wait()
{
	pthread_cond_wait(&empty,&lock);
}


	void productor_wait()
{
	pthread_cond_wait(&full,&lock);
}

	void consumer_notify()
{
	pthread_cond_signal(&empty);
}


	void productor_notify()
{
	pthread_cond_signal(&full);
}

	bool Is_empty()
{
	return (q.size()==0?true:false);
}

	bool Is_full()
{
	return (q.size()==cap?true:false);
}

public:
	blockQueue(int _cap=NUM):cap(_cap)
{
	pthread_mutex_init(&lock,NULL);
	pthread_cond_init(&full,NULL);
	pthread_cond_init(&empty,NULL);
}

	void push_data(const int &data)
{
	lockQueue();
	while(Is_full())
	{
		consumer_notify();
		std::cout<<"queue full,notify consume data,product stop."<<std::endl;
		productor_wait();
	}
	q.push(data);
	unlockQueue();
}

	void pop_data(int &data)
{
	lockQueue();
	while(Is_empty())
	{
		productor_notify();
		std::cout<<"queue empty,notify product data,consume stop.\n"<<std::endl;
		consumer_wait();
	}
	data=q.front();
	q.pop();
	unlockQueue();
}

	~blockQueue()
{
	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&full);
	pthread_cond_destroy(&empty);
}
};

void *consumer(void *arg)
{
	blockQueue *bqp=(blockQueue*)arg;
	int data;
	for(;;)
	{
		bqp->pop_data(data);
		std::cout<<"Consume data done: "<<data<<std::endl;
	}
}

void *productor(void*arg)
{
	blockQueue *bqp=(blockQueue*)arg;
	srand((unsigned long)time(NULL));
	int data;
	for(;;)
	{
		data=rand()%1024;
		bqp->push_data(data);
		std::cout<<"Product data done: "<<data<<std::endl;
	}
}	

int main()
{
	blockQueue bq;
	pthread_t c,p;
	pthread_create(&p,NULL,productor,(void *)&bq);
	pthread_create(&c,NULL,consumer,(void *)&bq);
	pthread_join(p,NULL);
	pthread_join(c,NULL);
	return 0;
}



