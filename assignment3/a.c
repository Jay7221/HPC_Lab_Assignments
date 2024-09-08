#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_SIZES 3
#define NUM_THREADS 16

// Array sizes for testing
const int sizes[NUM_SIZES] = {1000000, 10000000, 100000000};

// Function to compute dot product
void compute_dot_product(int size, int num_threads) {
    double *vector1, *vector2;
    double dot_product = 0.0;
    double start, end;

    // Allocate memory for vectors
    vector1 = (double *)malloc(size * sizeof(double));
    vector2 = (double *)malloc(size * sizeof(double));

    // Initialize vectors with some values
    for (int i = 0; i < size; i++) {
        vector1[i] = i + 1;      // Example values
        vector2[i] = (size - i); // Example values
    }

    // Set number of threads
    omp_set_num_threads(num_threads);

    // Measure the start time
    start = omp_get_wtime();

    // Parallel computation of the dot product
    #pragma omp parallel for reduction(+:dot_product)
    for (int i = 0; i < size; i++) {
        dot_product += vector1[i] * vector2[i];
    }

    // Measure the end time
    end = omp_get_wtime();

    // Print the result
    printf("Threads: %d, Array Size: %d, Time taken: %f seconds\n", num_threads, size, end - start);

    // Free allocated memory
    free(vector1);
    free(vector2);
}

int main() {
    // Run tests for each array size
    for (int i = 0; i < NUM_SIZES; i++) {
        int size = sizes[i];
        printf("Testing for array size: %d\n", size);

        // Run tests for different numbers of threads
        for (int num_threads = 1; num_threads <= NUM_THREADS; num_threads *= 2) {
            compute_dot_product(size, num_threads);
        }
    }

    return 0;
}
