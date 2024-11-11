#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    const int N = 4;

    MPI_Init(&argc, &argv);

    int rank, num_procs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    int rows_per_proc = N / num_procs;

    int *matrix_A = NULL;
    int *matrix_C = NULL;

    int *local_matrix_A = (int*)malloc(rows_per_proc * N * sizeof(int));

    int matrix_B[N * N];
    int local_result[rows_per_proc * N];

    if(rank == 0){
        matrix_A = (int*)malloc(N * N * sizeof(int));
        matrix_C = (int*)malloc(N * N * sizeof(int));

        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                matrix_A[i * N + j] = i + j;
                matrix_B[i * N + j] = i * j;
            }
        }

        printf("Rows per process: %d\n", rows_per_proc);
        printf("Matrix A:\n");
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                printf("%d ", matrix_A[i * N + j]);
            }
            printf("\n");
        }
        printf("Matrix B:\n");
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                printf("%d ", matrix_B[i * N + j]);
            }
            printf("\n");
        }
    }

    MPI_Bcast(matrix_B, N * N, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(
        matrix_A, rows_per_proc * N, MPI_INT,
        local_matrix_A, rows_per_proc * N, MPI_INT,
        0, MPI_COMM_WORLD
    );

    for(int i = 0; i < rows_per_proc; ++i){
        for(int j = 0; j < N; ++j){
            local_result[i * N + j] = 0;
            for(int k = 0; k < N; ++k){
                local_result[i * N + j] += local_matrix_A[i * N + k] * matrix_B[k * N + j];
            }
        }
    }

    MPI_Gather(
        local_result, rows_per_proc * N, MPI_INT,
        matrix_C, rows_per_proc * N, MPI_INT,
        0, MPI_COMM_WORLD
    );

    if(rank == 0){
        printf("Result Matrix: \n");
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                printf("%d ", matrix_C[i * N + j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
