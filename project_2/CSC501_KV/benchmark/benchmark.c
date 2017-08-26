#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <time.h>
#include <keyvalue.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int i=0,number_of_threads = 1, number_of_keys=1024, number_of_transactions = 65536; 
    int a;
	int *b = malloc(sizeof(int));
    int tid;
    __u64 size;
    char data[4096];
    int devfd;
    if(argc < 3)
    {
        fprintf(stderr, "Usage: %s number_of_keys number_of_transactions\n",argv[0]);
        exit(1);
    }
    number_of_keys = atoi(argv[1]);
    number_of_transactions = atoi(argv[2]);
    devfd = open("/dev/keyvalue",O_RDWR);
    if(devfd < 0)
    {
        fprintf(stderr, "Device open failed");
        exit(1);
    }
    srand((int)time(NULL)+(int)getpid());
    // Initializing the keys
    for(i = 0; i < number_of_keys; i++)
    {
		memset(data, 0, 4096);
        a = rand();
        sprintf(data,"%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a);
        tid = kv_set(devfd,i,strlen(data),data);
        fprintf(stderr,"S\t%d\t%d\t%d\t%s\t%d\n",tid,i,strlen(data),data,data);
    }
	//tid = kv_delete(devfd, 10);
	//tid = kv_delete(devfd, 20);
	/*char data2[4096];
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

