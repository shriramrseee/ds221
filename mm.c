#include <stdio.h>
#include <stdlib.h>

double a[1024][1024], b[1024][1024], c[1024][1024];

int main()
{
	for(int i=0; i<1024; i++)
	{
		for(int j=0; j<1024; j++)
		{
			a[i][j]=rand();
			b[i][j]=rand();
			c[i][j]=0;
		}
	}

	for(int i=0; i<1024; i++)
	{
		for(int j=0; j<1024; j++)
		{
			for(int k=0; k<1024; k++)
			{
				c[i][k] += a[i][j]*b[j][k];
			}
		}
	}

	return 0;
}
