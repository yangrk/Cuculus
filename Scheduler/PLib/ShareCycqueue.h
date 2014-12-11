#ifndef _SHARE_CYCQUEUE_H_
#define _SHARE_CYCQUEUE_H_
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>


template<typename ITEM>
class ShareBuffer
{
public:
	ShareBuffer(int bufer_size)
	{
		int ret = 0;
		size_ = bufer_size;
		
		if(size_ <=0) 
			throw "Invalid Size";
		
		item_buf_ = new ITEM[size_];
		
		if(pthread_mutex_init(&mutex, NULL) == -1)
		{
			throw "mutex_init mutex failed";
		}

		if(sem_init(&full, 0, 0) == -1){
			throw "sem_init full failed";
		}

		if(sem_init(&empty, 0, size_) == -1){
			throw "sem_init empty failed";
		}

		head_ = 0;
		tail_ = 0;
	};

	int producer(ITEM item);
	ITEM consumer();

private:
	int insert_item(ITEM item);
	ITEM remove_item();

public:
	int size_;
	ITEM *item_buf_;
	int head_;
	int tail_;
	pthread_mutex_t mutex;
	sem_t full, empty;
};


template<typename ITEM>
int ShareBuffer<ITEM>::producer(ITEM item) 
{
	int ret = 0;
	do{
		sem_wait(&empty);
	}while(ret == -1 && errno == EINTR);
	
	pthread_mutex_lock(&mutex);

	if(insert_item(item)) 
	{
		fprintf(stderr, " Producer report error condition\n");
	}
	else 
	{
	}
	
	/* release the mutex lock */
	pthread_mutex_unlock(&mutex);
	
	/* signal full */
	sem_post(&full);
	
	return 0;
}


/* Consumer Thread */
template<typename ITEM>
ITEM ShareBuffer<ITEM>::consumer() 
{
	ITEM item;
	int ret = 0;
	do{
		ret = sem_wait(&full);
	}while(ret == -1 && errno == EINTR);
	
	/* aquire the mutex lock */
	pthread_mutex_lock(&mutex);
	item = remove_item();
	
	/* release the mutex lock */
	pthread_mutex_unlock(&mutex);
	
	/* signal empty */
	sem_post(&empty);
	
	return item;

}


template<typename ITEM>
int ShareBuffer<ITEM>::insert_item(ITEM item) 
{
	if(tail_>= size_)
	{
		tail_ %= size_;
	}
	
	item_buf_[tail_++] = item;
	
	return 0;

}


/* Remove an item from the buffer */
template<typename ITEM>
ITEM ShareBuffer<ITEM>::remove_item() 
{
	if(head_>= size_){
		head_ %= size_;
	}
	return (item_buf_[head_++]);
}



#endif //end _SHARE_CYCQUEUE_H_
