#include <stdlib.h>

#define SIZE 4096

double a[SIZE][SIZE], b[SIZE][SIZE], c[SIZE][SIZE];

int main()
{
	for(int i=0; i<SIZE; i++)
	{
		for(int j=0; j<SIZE; j++)
		{
			a[i][j]=rand();
			b[i][j]=rand();
			c[i][j]=0;
		}
	}

	for(int i=0; i<SIZE; i++)
	{
		for(int j=0; j<SIZE; j++)
		{
			for(int k=0; k<SIZE; k++)
			{
				c[i][k] += a[i][j]*b[j][k];
			}
		}
	}

	return 0;
}
