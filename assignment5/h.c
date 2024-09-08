// h.c
#include <stdio.h>
#include <omp.h>

int main() {
    int n = 1000000; 
    int arr[n];
    long long total_sum = 0;
    double start_time, end_time;

    // Initialize the array with values
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    // Measure time for sequential sum
    total_sum = 0;
    start_time = omp_get_wtime();
    for (int i = 0; i < n; i++) {
        total_sum += arr[i];
    }
    end_time = omp_get_wtime();
    printf("Total Sum (Sequential): %lld\n", total_sum);
    printf("Time taken (Sequential): %f seconds\n", end_time - start_time);

    double sequential_time = end_time - start_time;

    // Measure time for parallel sum with reduction
    total_sum = 0;
    start_time = omp_get_wtime();
    #pragma omp parallel for reduction(+:total_sum)
    for (int i = 0; i < n; i++) {
        total_sum += arr[i];
    }
    end_time = omp_get_wtime();
    printf("Total Sum (Parallel with reduction): %lld\n", total_sum);
    printf("Time taken (Parallel with reduction): %f seconds\n", end_time - start_time);
    
    double parallel_time = end_time - start_time;

    printf("Speedup: %f\n", sequential_time / parallel_time);

    return 0;
}
