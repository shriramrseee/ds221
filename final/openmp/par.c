#include <stdio.h>
#include <math.h>
#include <float.h>
#include <omp.h>

#define SIZE 20000
#define CLUSTERS 20


int main() {
    float pts[SIZE][2];
    int label[SIZE];
    int min_label, chunk, tid;
    float centroid[CLUSTERS][2];
    float temp[THREADS][20][3];
    float min_dist, dist;

    chunk = CHUNKSIZE;

    for (int i = 0; i < SIZE; i++) {
        scanf("%f,%f", &pts[i][0], &pts[i][1]);
    }

    // Assign Initial centroid
    for (int i = 0; i < CLUSTERS; i++) {
        centroid[i][0] = pts[i * SIZE / CLUSTERS][0];
        centroid[i][1] = pts[i * SIZE / CLUSTERS][1];
    }

    // Run k-means clustering for 100 iterations
    
    // Parallel region
    #pragma omp parallel num_threads(THREADS) shared(pts, label, temp, centroid) private(min_dist, dist, tid, min_label)
    {

     for (int i = 0; i < ITER; i++) {
        
            tid = omp_get_thread_num();

            // Reset temp
            for (int k = 0; k < CLUSTERS; k++) {
                temp[tid][k][0] = 0;
                temp[tid][k][1] = 0;
                temp[tid][k][2] = 0;
            }

            // Assign Labels for all points
            #pragma omp for schedule(static, chunk)
            for (int j = 0; j < SIZE; j++) {
                min_dist = FLT_MAX;
                for (int k = 0; k < CLUSTERS; k++) {
                    dist = fabs(pts[j][0] - centroid[k][0]) * fabs(pts[j][0] - centroid[k][0]) +
                           fabs(pts[j][1] - centroid[k][1]) * fabs(pts[j][1] - centroid[k][1]);
                    if (dist < min_dist) {
                        min_dist = dist;
                        min_label = k;
                    }
                }
                label[j] = min_label;
                temp[tid][min_label][0] += pts[j][0];
                temp[tid][min_label][1] += pts[j][1];
                temp[tid][min_label][2] += 1;
            }
        // End of parallel region
        #pragma omp single
        {
        // Collect temp
        for(int j=1; j < THREADS; j++) {
            for(int k=0; k < CLUSTERS; k++) {
                temp[0][k][0] += temp[j][k][0];
                temp[0][k][1] += temp[j][k][1];
                temp[0][k][2] += temp[j][k][2];
            }
        }

        // Compute and update centroid
        for (int k = 0; k < CLUSTERS; k++) {
            if (temp[k][2] == 0)
                continue;
            centroid[k][0] = temp[0][k][0] / temp[0][k][2];
            centroid[k][1] = temp[0][k][1] / temp[0][k][2];
        }
    }
 }
}
 

    // Print labels

    for (int i = 0; i < CLUSTERS; i++) {
        printf("%d %d %f %f \n", i, (int)temp[0][i][2], centroid[i][0], centroid[i][1]);
    }

    return 0;
}


