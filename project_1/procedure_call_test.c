#define _GNU_SOURCE

#include <stdint.h> /* for uint64_t */
#include <time.h>  /* for struct timespec */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<sched.h>

 
/* assembly code to read the TSC */
static inline uint64_t RDTSC_start()
{
  unsigned int hi, lo;
  /*__asm__ volatile("rdtsc" : "=a" (lo), "=d" (hi));
  return ((uint64_t)hi << 32) | lo;*/
  asm volatile ("cpuid\n\t"
		  "rdtsc\n\t"
		  "mov %%edx, %0\n\t"
		  "mov %%eax, %1\n\t"
		  : "=r" (hi), "=r" (lo)
		  :: "%rax", "%rbx", "%rcx", "%rdx"); 
  return ((uint64_t)hi << 32) | lo;
}
static inline uint64_t RDTSC_stop()
{
  unsigned int hi, lo;
  asm volatile ("rdtscp\n\t"
		  "mov %%edx, %0\n\t"
		  "mov %%eax, %1\n\t"
		  "cpuid\n\t"
		  : "=r" (hi), "=r" (lo)
		  :: "%rax", "%rbx", "%rcx", "%rdx");
  return ((uint64_t)hi << 32) | lo;
}
void functioncall0(){
	return;
}
void functioncall1(int n1){
	return;
}
void functioncall2(int n1, int n2){
	return;
}
void functioncall3(int n1, int n2, int n3){
	return;
}
void functioncall4(int n1, int n2, int n3, int n4){
	return;
}
void functioncall5(int n1,int n2,int n3,int n4,int n5){
	return;
}
void functioncall6(int n1,int n2,int n3,int n4,int n5,int n6){
	return;
}
void functioncall7(int n1, int n2, int n3, int n4, int n5, int n6, int n7){
	return;
}
void main(){
	unsigned long cpuMask;
	cpuMask = 2;
	sched_setaffinity(0,sizeof(cpuMask), &cpuMask);
	srand(time(NULL));
	
	long i = 0;
	int j1 = 0;
	int j2 = 0;
	int j3 = 0;
	int j4 = 0;
	int j5 = 0;
	int j6 = 0;
	int j7 = 0;
        	
	for(i = 0;i<1000000;i++){
		unsigned long begin = RDTSC_start();
		functioncall0();
		unsigned long end = RDTSC_stop();
		printf("\n%lu %lu %lu", begin, end, end - begin);
	}
	printf("\n * * *");
	for(i = 0;i<1000000;i++){
		j1 = rand();
		unsigned long begin = RDTSC_start();
		functioncall1(j1);
		unsigned long end = RDTSC_stop();
		printf("\n%lu %lu %lu", begin, end, end - begin);
	}
	printf("\n * * *");
	for(i = 0;i<1000000;i++){
		j1 = rand();
		j2 = rand();
		unsigned long begin = RDTSC_start();
		functioncall2(j1,j2);
		unsigned long end = RDTSC_stop();
		printf("\n%lu %lu %lu", begin, end, end - begin);
	}
	printf("\n * * *");
	for(i = 0;i<1000000;i++){
		j1 = rand();
		j2 = rand();
		j3 = rand();
		unsigned long begin = RDTSC_start();
		functioncall3(j1,j2,j3);
		unsigned long end = RDTSC_stop();
		printf("\n%lu %lu %lu", begin, end, end - begin);
	}
	printf("\n * * *");
	for(i = 0;i<1000000;i++){
		j1 = rand();
		j2 = rand();
		j3 = rand();
		j4 = rand();
		unsigned long begin = RDTSC_start();
		functioncall4(j1,j2,j3,j4);
		unsigned long end = RDTSC_stop();
		printf("\n%lu %lu %lu", begin, end, end - begin);
	}
	printf("\n * * *");
	for(i = 0;i<1000000;i++){
		j1 = rand();
		j2 = rand();
		j3 = rand();
		j4 = rand();
		j5 = rand();
		unsigned long begin = RDTSC_start();
		functioncall5(j1,j2,j3,j4,j5);
		unsigned long end = RDTSC_stop();
		printf("\n%lu %lu %lu", begin, end, end - begin);
	}
	printf("\n * * *");
	for(i = 0;i<1000000;i++){
		j1 = rand();
		j2 = rand();
		j3 = rand();
		j4 = rand();
		j5 = rand();
		j6 = rand();
		unsigned long begin = RDTSC_start();
		functioncall6(j1,j2,j3,j4,j5,j6);
		unsigned long end = RDTSC_stop();
		printf("\n%lu %lu %lu", begin, end, end - begin);
	}
	printf("\n * * *");
	for(i = 0;i<1000000;i++){
		j1 = rand();
		j2 = rand();
		j3 = rand();
		j4 = rand();
		j5 = rand();
		j6 = rand();
		j7 = rand();
		unsigned long begin = RDTSC_start();
		functioncall7(j1,j2,j3,j4,j5,j6,j7);
		unsigned long end = RDTSC_stop();
		printf("\n%lu %lu %lu", begin, end, end - begin);
	}

}

