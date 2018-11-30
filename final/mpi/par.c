#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <unistd.h>
#include <sys/time.h>


void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int *arr, int l, int h) {
    // Median-of-3 logic for pivot
    int m = (l + h) / 2;
    if (arr[m] < arr[l]) {
        swap(&arr[m], &arr[l]);
    }
    if (arr[h] < arr[l]) {
        swap(&arr[l], &arr[h]);
    }
    if (arr[m] < arr[h]) {
        swap(&arr[m], &arr[h]);
    }
    int pivot = arr[h];

    // Partition logic
    int i = (l - 1);

    for (int j = l; j < h; j++) {
        if (arr[j] < pivot && i != j) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[h]);
    return i + 1;
}

void qusort(int *arr, int l, int h) {
    if (l < h) {
        int p = partition(arr, l, h);
        qusort(arr, l, p);
        qusort(arr, p + 1, h);
    }
}

void merge(int* arr, int len, int* arr2, int len2, int* temp) {
    int p1, p2;
    p1 = p2 = 0;
    for(int i=0; i<len+len2; i++) {
        if(p1<len && p2<len2) {
            if (arr[p1] < arr2[p2])
                temp[i] = arr[p1++];
            else
                temp[i] = arr2[p2++];
        }
        else if(p1<len)
            temp[i] = arr[p1++];
        else
            temp[i] = arr2[p2++];
    }

}

int main(int argc, char **argv) {

    int *arr, *arr2, *temp, *p;
    int rank, procs, len, len2, step;
    long start, end;
    struct timeval timecheck;
    FILE *fptr;

    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Status status;

    arr = (int*) malloc(SIZE * sizeof(int));
    arr2 = (int*) malloc(SIZE * sizeof(int));
    temp = (int*) malloc(SIZE * sizeof(int));

    // MPI Initialization
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &procs);
    MPI_Barrier(comm);

    // Read Input
    if (rank == 0) {
        fptr = fopen(argv[1], "r");
        for (int i = 0; i < SIZE; i++) {
            fscanf(fptr, "%d", &arr[i]);
        }
        fclose(fptr);
    }
   
    gettimeofday(&timecheck, NULL);
    start = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;

    // Send and Receive Input
    if (rank == 0) {
        for (int i = 1; i < procs; i++) {
            if (i < procs - 1)
                MPI_Send(arr + i * (SIZE / procs), SIZE / procs, MPI_INT, i, 0, comm);
            else
                MPI_Send(arr + i * (SIZE / procs), SIZE - i * (SIZE / procs), MPI_INT, i, 0, comm);
        }
        len = SIZE / procs;
    } else {
        MPI_Recv(arr, SIZE, MPI_INT, 0, 0, comm, &status);
        MPI_Get_count(&status, MPI_INT, &len);
    }

    // Perform local quick sort
    qusort(arr, 0, len - 1);


    // Perform Merge
    step = 0;
    while (1 << step < procs) {
        if ((rank + 1) % (2 << step) == 1 && rank + (1 << step) < procs) {
            // printf("Receive %d %d \n", step, rank);
            MPI_Recv(arr2, SIZE, MPI_INT, rank + (1 << step), step, comm, &status);
            MPI_Get_count(&status, MPI_INT, &len2);
            merge(arr, len, arr2, len2, temp);
            p = arr;
            arr = temp;
            temp = p;
            len += len2;
        } else if ((rank + 1) % (2 << step) != 1) {
            // printf("Send %d %d \n", step, rank);
            MPI_Send(arr, len, MPI_INT, rank - (1 << step), step, comm);
            break;
        }
        step++;
    }

    MPI_Barrier(comm);

    gettimeofday(&timecheck, NULL);
    end = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;
 
    
    // Print sorted list
    if (rank == 0) {
        for (int i = 0; i < SIZE; i++) {
            printf("%d\n", arr[i]);
        }
        printf("%f\n", (end - start)/1000.0);
    }
    

    MPI_Finalize();

    return 0;

}


