// e.c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void matrixMultiplicationStatic(int **A, int **B, int **C, int N) {
    #pragma omp parallel for schedule(static) collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matrixMultiplicationDynamic(int **A, int **B, int **C, int N) {
    #pragma omp parallel for schedule(dynamic) collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int sizes[] = {500, 1000, 2000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int s = 0; s < num_sizes; s++) {
        int N = sizes[s];

        // Allocate memory for matrices
        int **A = (int **)malloc(N * sizeof(int *));
        int **B = (int **)malloc(N * sizeof(int *));
        int **C = (int **)malloc(N * sizeof(int *));
        for (int i = 0; i < N; i++) {
            A[i] = (int *)malloc(N * sizeof(int));
            B[i] = (int *)malloc(N * sizeof(int));
            C[i] = (int *)malloc(N * sizeof(int));
        }

        // Initialize matrices with values
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i][j] = 1;
                B[i][j] = 1;
            }
        }

        printf("Matrix size: %d x %d\n", N, N);

        // Static scheduling
        double start_time = omp_get_wtime();
        matrixMultiplicationStatic(A, B, C, N);
        double end_time = omp_get_wtime();
        printf("Time taken with static scheduling: %f seconds\n", end_time - start_time);

        // Dynamic scheduling
        start_time = omp_get_wtime();
        matrixMultiplicationDynamic(A, B, C, N);
        end_time = omp_get_wtime();
        printf("Time taken with dynamic scheduling: %f seconds\n", end_time - start_time);

        printf("-----------------------------------\n");

        // Free allocated memory
        for (int i = 0; i < N; i++) {
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

