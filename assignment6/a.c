#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void matrixMultiplication(int **A, int **B, int **C, int N) {
    #pragma omp parallel for collapse(2)
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
    int N = 1000;  // Matrix size (NxN)

    // Allocate memory for matrices
    int **A = (int **)malloc(N * sizeof(int *));
    int **B = (int **)malloc(N * sizeof(int *));
    int **C = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        A[i] = (int *)malloc(N * sizeof(int));
        B[i] = (int *)malloc(N * sizeof(int));
        C[i] = (int *)malloc(N * sizeof(int));
    }

    double start_time = omp_get_wtime();  // Start time measurement

    matrixMultiplication(A, B, C, N);

    double end_time = omp_get_wtime();  // End time measurement

    printf("Time taken for matrix multiplication with OpenMP: %f seconds\n", end_time - start_time);

    // Free allocated memory
    for (int i = 0; i < N; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}
