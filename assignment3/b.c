#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void matrix_addition(int n, int m, int** A, int** B, int** C) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

int main() {
    int sizes[] = {250, 500, 750, 1000, 2000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    int num_threads[] = {1, 2, 4, 8};
    int num_thread_counts = sizeof(num_threads) / sizeof(num_threads[0]);

    for (int k = 0; k < num_sizes; k++) {
        int size = sizes[k];
        
        // Allocate matrices
        int** A = (int**)malloc(size * sizeof(int*));
        int** B = (int**)malloc(size * sizeof(int*));
        int** C = (int**)malloc(size * sizeof(int*));
        for (int i = 0; i < size; i++) {
            A[i] = (int*)malloc(size * sizeof(int));
            B[i] = (int*)malloc(size * sizeof(int));
            C[i] = (int*)malloc(size * sizeof(int));
        }

        // Initialize matrices
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                A[i][j] = i + j;
                B[i][j] = i - j;
            }
        }

        for (int t = 0; t < num_thread_counts; t++) {
            int thread_count = num_threads[t];
            omp_set_num_threads(thread_count);
            
            double start_time = omp_get_wtime();
            matrix_addition(size, size, A, B, C);
            double end_time = omp_get_wtime();
            
            printf("Matrix Size: %d, Threads: %d, Time: %f seconds\n", size, thread_count, end_time - start_time);
        }

        // Free matrices
        for (int i = 0; i < size; i++) {
            free(A[i]);
            free(B[i]);
            free(C[i]);
        }
        free(A);
        free(B);
        free(C);
    }

    return 0;
}
