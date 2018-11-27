#include <stdio.h>
#include <time.h>

__global__ void reduce(int *g_idata, int *g_odata)
{
	extern __shared__ int sdata[THREADS_PER_BLOCK];
	
	unsigned int tid = threadIdx.x;
 	unsigned int offset = tid * (SIZE / THREADS_PER_BLOCK);	

	sdata[tid] = 0;


	for(unsigned int k=0; k < SIZE/THREADS_PER_BLOCK; k++)
	{
		sdata[tid] += g_idata[offset+k];
	}

	__syncthreads();

	for(unsigned int s=1; s < blockDim.x; s*=2)
	{
		if(tid % (2*s) == 0)
			sdata[tid] += sdata[tid+s];
		__syncthreads();
	}

	if(tid == 0)
		*g_odata = sdata[0];
}


int main()
{
	int *h_idata, *h_odata;
	int *d_idata, *d_odata;
	clock_t start, end;

        h_idata = (int*) malloc(SIZE * sizeof(int));
	h_odata = (int*) malloc(sizeof(int));
	cudaMalloc((void **) &d_idata, SIZE * sizeof(int));
	cudaMalloc((void **) &d_odata, sizeof(int));


	for(int i=0; i<SIZE; i++)
	{
		scanf("%d", &h_idata[i]);
	}
	
	start = clock();	

 	cudaMemcpy(d_idata, h_idata, SIZE * sizeof(int), cudaMemcpyHostToDevice);
	
	dim3 dimBlock(THREADS_PER_BLOCK, 1, 1);
	dim3 dimGrid(1, 1, 1);

	reduce<<<dimGrid, dimBlock>>>(d_idata, d_odata);

	cudaMemcpy(h_odata, d_odata, sizeof(int), cudaMemcpyDeviceToHost);

	end = clock();

	printf("%d\n", *h_odata);	
	printf("%f\n", (double) (end - start));
	
	cudaFree(d_idata);
	cudaFree(d_odata);	

	return 0;

}
