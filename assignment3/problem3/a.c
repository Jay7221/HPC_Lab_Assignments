#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define VECTOR_SIZE 100000

void vector_scalar_add_static(int *vector, int scalar, int chunk_size) {
    int i;
    #pragma omp parallel shared(vector) private(i)
    {
        #pragma omp for schedule(static, chunk_size)
        for (i = 0; i < VECTOR_SIZE; i++) {
            vector[i] += scalar;
        }
    }
}

int main() {
    int vector[VECTOR_SIZE];
    int scalar = 5;
    int chunk_sizes[] = {1, 10, 20, 50, 100};
    int num_chunk_sizes = sizeof(chunk_sizes) / sizeof(chunk_sizes[0]);

    // Initialize vector with some values
    for (int i = 0; i < VECTOR_SIZE; i++) {
        vector[i] = i;
    }

    for (int j = 0; j < num_chunk_sizes; j++) {
        int chunk_size = chunk_sizes[j];
        double start_time = omp_get_wtime();
        vector_scalar_add_static(vector, scalar, chunk_size);
        double end_time = omp_get_wtime();
        printf("STATIC Schedule - Chunk size: %d, Time taken: %f seconds\n", chunk_size, end_time - start_time);
    }

    return 0;
}

