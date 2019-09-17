#include<iostream>
#include<pthread.h>
#include<stdlib.h>
#include<vector>
#include<semaphore.h>
#include<unistd.h>

#define NUM 16

class RingQueue
{
private:
	std::vector<int> q;
	int cap;
	sem_t data_sem;
	sem_t space_sem;
	int productor_step;
	int consumer_step;
public:
	RingQueue(int _cap=NUM):q(_cap),cap(_cap)
{
	sem_init(&data_sem,0,0);
	sem_init(&space_sem,0,cap);
	productor_step=0;
	consumer_step=0;
}	

	void putdata(const int &data)
{
	sem_wait(&space_sem);
	q[productor_step++]=data;
	productor_step=productor_step%cap;
	sem_post(&data_sem);
}	

	void getdata(int &data)
{
	sem_wait(&data_sem);
	data=q[consumer_step++];
	consumer_step=consumer_step%cap;
	sem_post(&space_sem);

}
	~RingQueue()
{
	sem_destroy(&data_sem);
	sem_destroy(&space_sem);
}
};

void *consumer(void *arg)
{
	RingQueue *rqp=(RingQueue*)arg;
	int data;
	for(;;)
	{
		rqp->getdata(data);
		std::cout<<"consume data: "<<data<<std::endl;
		sleep(1);
	}

}

void *productor(void *arg)
{	
	RingQueue *rqp=(RingQueue*)arg;
	int data;
	srand((unsigned long)time(NULL));
	for(;;)
	{
		data=rand()%1024;
		rqp->putdata(data);
		std::cout<<"product data: "<<data<<std::endl;
		sleep(1);
	}
}

int main()
{
	RingQueue rp;
	pthread_t p;
	pthread_t c;
	pthread_create(&p,NULL,productor,(void*)&rp);
	pthread_create(&c,NULL,consumer,(void*)&rp);
	pthread_join(p,NULL);
	pthread_join(c,NULL);

}


