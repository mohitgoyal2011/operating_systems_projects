#include <stdio.h>
#include <time.h>
#include<stdlib.h>
#include<string.h>

#define writea(i) a[i]=i%sizeof(char)
#define reada2(i) reada1(i)

int main(){
    const int LEN = 1 << 30;    //  1GB

    int *a = (int*)malloc(LEN*sizeof(int));

    clock_t time0 = clock();

    for (int i = 0; i < 100; i++){
	memset(a,i,LEN);
    }

    clock_t time1 = clock();
    printf("%lf", (double)(time1 - time0) / CLOCKS_PER_SEC);
/*    clock_t time0 = clock();


    int i = 
    for (int i = 0; i < 100; i++){
        
    }

    clock_t time1 = clock();
    printf("%lf", (double)(time1 - time0) / CLOCKS_PER_SEC);*/
}
