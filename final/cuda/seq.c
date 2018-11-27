#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>


int main()
{
	int data[SIZE];
	long sum = 0;
	long start, end;
	struct timeval timecheck;
 
	for(int i=0; i<SIZE; i++)
	{
		scanf("%d", &data[i]);
	}
	
	gettimeofday(&timecheck, NULL);
	start = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;

	for(int i=0; i<SIZE; i++)
	{
		sum += data[i];
	}
	
	gettimeofday(&timecheck, NULL);
	end = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;

	printf("%ld\n", sum);
	printf("%f\n", (end - start)/1000.0);	

	return 0;
} 
