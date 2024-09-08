#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void matrixVectorMultiplication(int **matrix, int *vector, int *result, int N) {
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        result[i] = 0;
        for (int j = 0; j < N; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}

int main() {
    int N = 100000;  // Size of the NxN matrix and the vector

    // Allocate memory for the matrix and vectors
    int **matrix = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        matrix[i] = (int *)malloc(N * sizeof(int));
    }
    int *vector = (int *)malloc(N * sizeof(int));
    int *result = (int *)malloc(N * sizeof(int));

    double start_time = omp_get_wtime();  // Start time measurement

    matrixVectorMultiplication(matrix, vector, result, N);

    double end_time = omp_get_wtime();  // End time measurement

    printf("Time taken for matrix-vector multiplication with OpenMP: %f seconds\n", end_time - start_time);

    // Free allocated memory
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(vector);
    free(result);

    return 0;
}

