#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4

// Function to calculate Pi
double calculate_pi_seq(long num_steps) {
    double step = 1.0 / (double)num_steps;
    double pi = 0.0;

    double start = omp_get_wtime();

    for (long i = 0; i < num_steps; ++i) {
        double x = (i + 0.5) * step;
        double y = 4.0 / (1 + x * x);
        pi += y * step;
    }

    double end = omp_get_wtime();
    
    printf("Sequential, Num_steps: %ld, Pi: %f, Time taken: %f\n",num_steps, pi, end - start);
    return end - start;
}

// Function to calculate Pi
double calculate_pi(long num_steps, int threads) {
    double step = 1.0 / (double)num_steps;
    double pi = 0.0;

    double start = omp_get_wtime();

    // Parallel region with reduction
    #pragma omp parallel for reduction(+:pi) num_threads(threads)
    for (long i = 0; i < num_steps; ++i) {
        double x = (i + 0.5) * step;
        double y = 4.0 / (1 + x * x);
        pi += y * step;
    }

    double end = omp_get_wtime();
    
    printf("Threads: %d, Num_steps: %ld, Pi: %f, Time taken: %f\n", threads, num_steps, pi, end - start);
    return end - start;
}

int main() {
    long num_steps_list[] = {1000000, 10000000, 100000000}; // Different data sizes
    int num_threads_list[] = {1, 2, 4, 8}; // Different thread counts
    int num_steps_count = sizeof(num_steps_list) / sizeof(num_steps_list[0]);
    int num_threads_count = sizeof(num_threads_list) / sizeof(num_threads_list[0]);

    for (int i = 0; i < num_steps_count; i++) {
        double seq = calculate_pi_seq(num_steps_list[i]);
        for (int j = 0; j < num_threads_count; j++) {
            double parallel = calculate_pi(num_steps_list[i], num_threads_list[j]);
            printf("Speedup: %f\n", seq / parallel);
            printf("\n");
        }
        printf("-----------\n");
    }

    return 0;
}

