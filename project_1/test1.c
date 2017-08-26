#include <stdint.h> /* for uint64_t */
#include <time.h>  /* for struct timespec */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


 
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
void main(){
	unsigned long cpuMask;
	cpuMask = 2;
	sched_setaffinity(0,sizeof(cpuMask), &cpuMask);
	srand(time(NULL));
	
	long i = 0;
	long j = 0;
	char* strarr = malloc(sizeof(char)*1024*1024*128);
	memset(strarr,'a',sizeof(char)*1024*1024*128);
	for(i = 0;i<10000000;i++){
		unsigned long int j = rand()%(1024*1024*128);
		unsigned long begin = RDTSC_start();
		char a = strarr[j];
		unsigned long end = RDTSC_stop();
		printf("\n%lu %lu %lu", begin, end, end - begin);
	}
	free(strarr);	

}

