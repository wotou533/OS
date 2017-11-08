#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define Max 10
pthread_mutex_t the_mutex;
pthread_cond_t condC;
pthread_cond_t condP;
int bufferSize = 2;
int buffer = 0;

void *producer1(void *ptr)
{
	printf("pro1\n");
	for(int i = 0; i < Max; i++)
	{
		pthread_mutex_lock(&the_mutex);
		while(buffer == bufferSize)
		{
			printf("The buffer is full! Producer1 is waiting.\n");		
			pthread_cond_wait(&condP, &the_mutex);
		}
		buffer++;
		printf("Producer1 produced a pizza......%d\n", i);
		sleep(1);
		pthread_cond_broadcast(&condP);
		pthread_cond_broadcast(&condC);
		pthread_mutex_unlock(&the_mutex);
	}
	pthread_exit(0);
}
void *producer2(void *ptr)
{
	printf("pro2\n");
	for(int i = 0; i < Max; i++)
	{
		pthread_mutex_lock(&the_mutex);
		while(buffer == bufferSize)
		{
			printf("The buffer is full! Producer2 is waiting.\n");
			pthread_cond_wait(&condP, &the_mutex);
		}
		buffer++;
		printf("Producer2 produced a pizza......%d\n", i);
		sleep(1);
		pthread_cond_broadcast(&condP);
		pthread_cond_broadcast(&condC);
		pthread_mutex_unlock(&the_mutex);
	}
	pthread_exit(0);
}
void *producer3(void *ptr)
{
	printf("pro3\n");
	for(int i = 0; i < Max; i++)
	{
		pthread_mutex_lock(&the_mutex);
		while(buffer == bufferSize)
		{
			printf("The buffer is full! Producer3 is waiting.\n");
			pthread_cond_wait(&condP, &the_mutex);
		}
		buffer++;
		printf("Producer3 produced a pizza......%d\n", i);
		sleep(1);
		pthread_cond_broadcast(&condP);
		pthread_cond_broadcast(&condC);
		pthread_mutex_unlock(&the_mutex);
	}
	pthread_exit(0);
}
void *consumer1(void *ptr)
{
	printf("con1\n");
	for(int i =0; i < Max; i++)
	{
		pthread_mutex_lock(&the_mutex);
		while(buffer == 0)
		{
			printf("The buffer is empty! Consumer1 is waiting.\n");
			pthread_cond_wait(&condC, &the_mutex);
		}
		buffer--;
		printf("Consumer1 retrived a pizza......%d\n", i);
		sleep(1);
		pthread_mutex_unlock(&the_mutex);
		pthread_cond_broadcast(&condC);
		pthread_cond_broadcast(&condP);
	}
	pthread_exit(0);
}
void *consumer2(void *ptr)
{
	printf("con2\n");
	for(int i =0; i < Max; i++)
	{
		pthread_mutex_lock(&the_mutex);
		while(buffer == 0)
		{
			printf("The buffer is empty! Consumer2 is waiting.\n");
			pthread_cond_wait(&condC, &the_mutex);
		}
		buffer--;
		printf("Consumer2 retrived a pizza......%d\n", i);
		sleep(1);
		pthread_cond_broadcast(&condC);
		pthread_cond_broadcast(&condP);
		pthread_mutex_unlock(&the_mutex);
	}
	pthread_exit(0);
}
void *consumer3(void *ptr)
{
	printf("con3\n");
	for(int i =0; i < Max; i++)
	{
		pthread_mutex_lock(&the_mutex);
		while(buffer == 0)
		{
			printf("The buffer is empty! Consumer3 is waiting.\n");
			pthread_cond_wait(&condC, &the_mutex);
		}
		buffer--;
		printf("Consumer3 retrived a pizza......%d\n", i);
		sleep(1);
		pthread_cond_broadcast(&condC);
		pthread_cond_broadcast(&condP);
		pthread_mutex_unlock(&the_mutex);
	}
	pthread_exit(0);
}
int main(int argc, char **argv)
{
	pthread_t pro1, con1, pro2, con2, pro3, con3;
	pthread_mutex_init(&the_mutex, 0);
	pthread_cond_init(&condC, 0);
	pthread_cond_init(&condP, 0);
	pthread_create(&con3, 0, consumer3, 0);
	printf("Have create con3\n");
	sleep(1);
	pthread_create(&con2, 0, consumer2, 0);
	printf("Have create con2\n");
	sleep(1);
	pthread_create(&con1, 0, consumer1, 0);
	printf("Have create con1\n");
	sleep(1);
	pthread_create(&pro3, 0, producer3, 0);
	printf("Have create pro3\n");
	//sleep(1);
	pthread_create(&pro2, 0, producer2, 0);
	printf("Have create pro2\n");
	//sleep(1);
	pthread_create(&pro1, 0, producer1, 0);
	printf("Have create pro1\n");
	//sleep(1);
	pthread_join(pro1, 0);
	pthread_join(pro2, 0);
	pthread_join(con2, 0);
	pthread_join(con1, 0);
	pthread_cond_destroy(&condC);
	pthread_cond_destroy(&condP);
}
