// g.c
#include <stdio.h>
#include <omp.h>

int main() {
    int n = 1000000; // Increased size for better timing comparison
    int arr[n];
    int total_sum = 0;
    double start_time, end_time;

    // Initialize the array
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    // Unsychronized version
    total_sum = 0;
    start_time = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        total_sum += arr[i];
    }
    end_time = omp_get_wtime();
    printf("Total Sum (without synchronization): %d\n", total_sum);
    printf("Time taken (without synchronization): %f seconds\n", end_time - start_time);

    // Using critical
    total_sum = 0;
    start_time = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        #pragma omp critical
        {
            total_sum += arr[i];
        }
    }
    end_time = omp_get_wtime();
    printf("Total Sum (with critical): %d\n", total_sum);
    printf("Time taken (with critical): %f seconds\n", end_time - start_time);

    // Using atomic
    total_sum = 0;
    start_time = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        #pragma omp atomic
        total_sum += arr[i];
    }
    end_time = omp_get_wtime();
    printf("Total Sum (with atomic): %d\n", total_sum);
    printf("Time taken (with atomic): %f seconds\n", end_time - start_time);

    return 0;
}
