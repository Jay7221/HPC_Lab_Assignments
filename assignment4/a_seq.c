#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 40  // Define a reasonable upper bound for n

// Function to compute Fibonacci number using OpenMP
int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }

    int x, y;
    
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            x = fibonacci(n - 1);
        }

        #pragma omp section
        {
            y = fibonacci(n - 2);
        }
    }

    return x + y;
}

int main() {
    int test_values[] = {10, 15, 20, 25, 30, 35};  // Values of n to test
    int num_tests = sizeof(test_values) / sizeof(test_values[0]);
    int i, n;
    double start_time, end_time;
    int result;

    for (i = 0; i < num_tests; i++) {
        n = test_values[i];
        printf("Testing Fibonacci(%d)\n", n);
        
        // Measure time for different numbers of threads
        for (int num_threads = 1; num_threads <= 8; num_threads *= 2) {
            omp_set_num_threads(num_threads);
            start_time = omp_get_wtime();
            result = fibonacci(n);
            end_time = omp_get_wtime();
            
            printf("Threads: %d, Result: %d, Time taken: %f seconds\n", num_threads, result, end_time - start_time);
        }
        printf("\n");
    }

    return 0;
}

