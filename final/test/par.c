#include <stdio.h>
#include <math.h>
#include <float.h>
#include <omp.h>
#include <time.h>

#define SIZE 200000000
#define ITER 1
#define CLUSTERS 20

int main()
{
    float temp, centroid[CLUSTERS][2];
    clock_t t;

    t = clock();

    // Assign Initial centroid
    for (int i = 0; i < CLUSTERS; i++)
    {
        centroid[i][0] = i*i;
        centroid[i][1] = i*i+1;
    }

    // Run k-means clustering for 100 iterations

   // for (int i = 0; i < ITER; i++)
   // {
          // #pragma omp parallel num_threads(2) private(temp)

          // {
             
            
            #pragma omp parallel for num_threads(2) private(temp) 
            for (int j = 0; j < SIZE; j++)
            {
                 
                 for(int k=0; k<CLUSTERS; k++) {
                  temp = centroid[k][0]*centroid[k][1];
                 }
            }
              
           //} 
   //}

    t = clock() - t;

    printf("%f\n", ((double)t)/CLOCKS_PER_SEC);

    return 0;
}
