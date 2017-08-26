#define _GNU_SOURCE
#include <stdint.h> /* for uint64_t */
#include <time.h>  /* for struct timespec */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sched.h>

 
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
void functioncall(int n1){
	int x=n1;
}
void main(int args, char *argv[]){
	unsigned long cpuMask;
	cpuMask = 2;
	sched_setaffinity(0,sizeof(cpuMask), &cpuMask);
	srand(time(NULL));
	int memsize = atoi(argv[1]);
	long i = 0;
	long j = 0;
	int* strarr = malloc(memsize);
	memset(strarr,rand(),memsize);
	for(i = 0;i<10000000;i++){
		unsigned long int j = rand()%(memsize);
		unsigned long begin = RDTSC_start();
		int a = strarr[j];
		unsigned long end = RDTSC_stop();
		printf("\n%lu %lu %lu", begin, end, end - begin);
	}
	free(strarr);	

}

