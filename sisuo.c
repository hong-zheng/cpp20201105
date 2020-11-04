
// 造死锁
// 法一：互斥量的循环等待
// 法二：最简单的方法：连续两次对互斥量加锁
	#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
pthread_mutex_t mutex_a ;
pthread_mutex_t mutex_b ;
void* r1(void* arg){
        while(1){
                pthread_mutex_lock(&mutex_a) ;
                int ret = 0 ;
                if((ret = pthread_mutex_trylock(&mutex_b)) != 0){
                        printf("1 %s\n",strerror(errno)) ;
                        return NULL ;
                }
                printf("hong Ye 1\n") ;
                pthread_mutex_unlock(&mutex_b) ;
                pthread_mutex_unlock(&mutex_a) ;
        }
}
void* r2(void* arg){
        while(1){
                pthread_mutex_lock(&mutex_b) ;
                int ret = 0 ; 
                if( ( ret = pthread_mutex_trylock(&mutex_a)) != 0){
                       printf("r2 %s\n",strerror(errno)) ;
                        return NULL ;
                } ;
                printf("hong Ye 2\n") ;
                pthread_mutex_unlock(&mutex_a) ;
                pthread_mutex_unlock(&mutex_b) ;
        }
}
void main(){
        pthread_t t1 , t2 ;
                                         
        pthread_mutex_init(&mutex_a,NULL) ;
        pthread_mutex_init(&mutex_b,NULL) ;
        pthread_create(&t1,NULL,r1,NULL) ;
        pthread_create(&t2,NULL,r2,NULL) ;
        pthread_join(t1,NULL) ;
        pthread_join(t2,NULL) ;
        pthread_mutex_destroy(&mutex_b) ;
        pthread_mutex_destroy(&mutex_a) ;
}
