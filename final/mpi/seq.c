#include <stdio.h>
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


void qsort(int *arr, int l, int h) {
    if (l < h) {
        int p = partition(arr, l, h);
        qsort(arr, l, p);
        qsort(arr, p + 1, h);
    }
}

int main() {

    int arr[SIZE];
    long start, end;
    struct timeval timecheck;


    // Read Input
    for (int i = 0; i < SIZE; i++) {
        scanf("%d", &arr[i]);
    }
    
    gettimeofday(&timecheck, NULL);
    start = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;


    // Perform quick sort
    qsort(arr, 0, SIZE - 1);

    gettimeofday(&timecheck, NULL);
    end = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;
 
    // Print sorted list
    for (int i = 0; i < SIZE; i++) {
        printf("%d\n", arr[i]);
    }

    printf("%f\n", (end - start)/1000.0);
    
    return 0;

}


