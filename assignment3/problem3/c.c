#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define VECTOR_SIZE 100000

void vector_scalar_add_nowait(int *vector, int scalar) {
    int i;
    #pragma omp parallel shared(vector)
    {
        #pragma omp for schedule(static)
        for (i = 0; i < VECTOR_SIZE / 2; i++) {
            vector[i] += scalar;
        }

        #pragma omp for schedule(static) nowait
        for (i = VECTOR_SIZE / 2; i < VECTOR_SIZE; i++) {
            vector[i] += scalar;
        }
    }
}

int main() {
    int vector[VECTOR_SIZE];
    int scalar = 5;

    // Initialize vector with some values
    for (int i = 0; i < VECTOR_SIZE; i++) {
        vector[i] = i;
    }

    double start_time = omp_get_wtime();
    vector_scalar_add_nowait(vector, scalar);
    double end_time = omp_get_wtime();

    printf("NOWAIT Clause - Time taken: %f seconds\n", end_time - start_time);

    return 0;
}

