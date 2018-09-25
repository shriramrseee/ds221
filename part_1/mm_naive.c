#include <stdlib.h>
#include <stdio.h>
#include <time.h>

double a[SIZE][SIZE], b[SIZE][SIZE], c[SIZE][SIZE];

int main()
{
	struct timespec start, end;
        srand(time(NULL));
	
	for(int i=0; i<SIZE; i++)
	{
		for(int j=0; j<SIZE; j++)
		{
			a[i][j]= (double) rand();
			b[i][j]= (double) rand();
			c[i][j]=0;
		}
	}

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);

	for(int i=0; i<SIZE; i++)
	{
		for(int j=0; j<SIZE; j++)
		{
			for(int k=0; k<SIZE; k++)
			{
				c[i][j] += a[i][k]*b[k][j];
			}
		}
	}

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

        printf ("%f s\n", (end.tv_nsec-start.tv_nsec)/1000000000.0 + (end.tv_sec-start.tv_sec));

	return 0;
}
