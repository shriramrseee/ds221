#include <stdio.h>
#include <math.h>
#include <float.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>


#define CLUSTERS 20


int main()
{
 float pts[SIZE][2];
 int label[SIZE];
 int min_label;
 float centroid[CLUSTERS][2];
 float temp[CLUSTERS][3];
 float min_dist, dist;
 long start, end;
 struct timeval timecheck;

 for(int i=0; i<SIZE; i++) {
   scanf("%f,%f", &pts[i][0], &pts[i][1]);
 }

  gettimeofday(&timecheck, NULL);
  start = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;


 // Assign Initial centroid

 for(int i=0; i<CLUSTERS; i++) {
  centroid[i][0] = pts[i*SIZE/CLUSTERS][0];
  centroid[i][1] = pts[i*SIZE/CLUSTERS][1];
 }

 // Run k-means clustering for 100 iterations

 for(int i=0; i<ITER; i++) {
  // Reset temp
  for(int k=0; k<CLUSTERS; k++) {
   temp[k][0]=0;
   temp[k][1]=0;
   temp[k][2]=0;
  }
  // Assign Labels for all points
  for(int j=0; j<SIZE; j++) {
   min_dist = FLT_MAX;
   for(int k=0; k<CLUSTERS; k++) {
    dist = (pts[j][0]-centroid[k][0])*(pts[j][0]-centroid[k][0]) + (pts[j][1]-centroid[k][1])*(pts[j][1]-centroid[k][1]);
    if(dist<min_dist) {
     min_dist = dist;
     min_label = k;
    }
   }
   label[j] = min_label;
   temp[min_label][0] += pts[j][0];
   temp[min_label][1] += pts[j][1];
   temp[min_label][2] += 1;
  }
  // Compute and update centroid
  for(int k=0; k<CLUSTERS; k++) {
   if(temp[k][2] == 0)
    continue;
   centroid[k][0] = temp[k][0]/temp[k][2];
   centroid[k][1] = temp[k][1]/temp[k][2];
  }
 }

  gettimeofday(&timecheck, NULL);
  end = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;


 // Print output

 for(int i=0; i<CLUSTERS; i++) {
  printf("%d %d %f %f \n", i, (int)temp[i][2], centroid[i][0], centroid[i][1]);
 }

  printf("%f\n", (end - start)/1000.0);

 return 0;
}

