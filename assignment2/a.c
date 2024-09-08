#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void vector_scalar_addition(float *vector, float scalar, int size, int num_threads) {
    // Set the number of threads
    omp_set_num_threads(num_threads);

    // Parallel vector scalar addition
    #pragma omp parallel for private(scalar)
    for (int i = 0; i < size; i++) {
        vector[i] += scalar;
    }
}

int main() {
    int sizes[] = {1000, 10000, 100000, 1000000, 10000000}; // Different vector sizes to test
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    int num_threads[] = {1, 2, 4, 8}; // Different thread counts to test
    int num_threads_count = sizeof(num_threads) / sizeof(num_threads[0]);

    float scalar = 5.0;

    for (int t = 0; t < num_threads_count; t++) {
        printf("\nPerformance with %d threads:\n", num_threads[t]);

        for (int s = 0; s < num_sizes; s++) {
            int size = sizes[s];
            float *vector = (float *)malloc(size * sizeof(float));

            // Initialize the vector with some values
            for (int i = 0; i < size; i++) {
                vector[i] = (float)i;
            }

            // Measure the start time
            clock_t start = clock();

            // Perform vector scalar addition
            vector_scalar_addition(vector, scalar, size, num_threads[t]);

            // Measure the end time
            clock_t end = clock();

            // Calculate the time taken
            double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

            printf("Vector size: %d, Time taken: %f seconds\n", size, time_taken);

            // Clean up
            free(vector);
        }
    }

    return 0;
}
