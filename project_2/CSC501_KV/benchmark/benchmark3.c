#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <time.h>
#include <keyvalue.h>
#include <fcntl.h>
#include <pthread.h>
#define NUM_THREADS 100
#define KEYS_PER_THREAD 1000
volatile int devfd;
volatile long int counter = 0;
void* produce(void* x){
	int i = 0;
	int number_of_keys = KEYS_PER_THREAD;
	int a;
    int tid;
    __u64 size;
    char data[1024];
	int devfd2;
    devfd2 = open("/dev/keyvalue",O_RDWR);
    srand((int)time(NULL)+(int)getpid());
    for(i = 0; i < number_of_keys; i++)
    {
		memset(data, 0, 1024);
        a = rand();
		tid = 0;
        sprintf(data,"%d",a);
        tid = kv_set(devfd2,i,strlen(data),data);
        fprintf(stderr,"%d: S\t%d\t%d\t%d\t%s\n",++counter,tid,i,strlen(data),data);
    }
	close(devfd2);
	
}

void* consume(void* x){
	int i=0;
	int number_of_transactions = KEYS_PER_THREAD;
	int number_of_keys = KEYS_PER_THREAD;
	char data2[4096];
    int tid;
    __u64 size;
	int devfd2;
    devfd2 = open("/dev/keyvalue",O_RDWR);
    srand((int)time(NULL)+(int)getpid());
    for(i = 0; i < number_of_transactions; i++)
    {	__u64 key = rand()%number_of_keys;
        tid = kv_get(devfd2,key,&size,data2);
        fprintf(stderr,"%d: G\t%d\t%d\t%d\t%s\n",++counter,tid,key,size,(char*)data2);
        tid = kv_delete(devfd2,key);
        fprintf(stderr,"%d: D\t%d\t%d\n",++counter,tid,key);
        
    }
	close(devfd2);

}

int main(int argc, char *argv[])
{
    int i=0,number_of_threads = 1, number_of_keys=1024, number_of_transactions = 65536; 
    int a;
	int *b = malloc(sizeof(int));
    int tid;
    __u64 size;
    char data[1024];
    int devfd;
	pthread_t threads[20];
	pid_t pids[20];
    if(argc < 3)
    {
        fprintf(stderr, "Usage: %s number_of_keys number_of_transactions\n",argv[0]);
        exit(1);
    }
    number_of_keys = atoi(argv[1]);
    number_of_transactions = atoi(argv[2]);
//	number_of_threads = atoi(argv[3]);
    devfd = open("/dev/keyvalue",O_RDWR);
    if(devfd < 0)
    {
        fprintf(stderr, "Device open failed");
        exit(1);
    }
    srand((int)time(NULL)+(int)getpid());
	for(i = 0;i<NUM_THREADS;i=i+2){
		pids[i] = pthread_create(&threads[i], NULL, produce, NULL);
		pids[i+1] = pthread_create(&threads[i+1], NULL, consume, NULL);
	}
	for(i = 0;i<NUM_THREADS;i++){
		pthread_join(threads[i], NULL);
	}
    // Initializing the keys
    /*for(i = 0; i < number_of_keys; i++)
    {
		memset(data, 0, 1024);
        a = rand();
        sprintf(data,"%d",a);
        tid = kv_set(devfd,i,strlen(data),data);
        fprintf(stderr,"S\t%d\t%d\t%d\t%s\t%d\n",tid,i,strlen(data),data,data);
    }
	//tid = kv_delete(devfd, 10);
	//tid = kv_delete(devfd, 20);
	char data2[4096];
    for(i = 0; i < number_of_transactions; i++)
    {
        fprintf(stderr,"\nMohit");
        tid = kv_get(devfd,i,&size,&a);
        fprintf(stderr,"G\t%d\t%d\t%d\n",tid,size,a);
        
    }
    fprintf(stderr,"GOT\t%d\t%d\t%d\n",tid,size,a);*/
    
	close(devfd);
    return 0;
}

