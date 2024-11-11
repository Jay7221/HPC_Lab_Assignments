#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){

    const int N = 4;    // size of matrix and vector

    MPI_Init(&argc, &argv);

    int rank, num_procs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    int *matrix = NULL;
    int vector[N];

    int rows_per_proc = N / num_procs;
    int *local_matrix = (int*)malloc(rows_per_proc * N * sizeof(int));
    int local_result[rows_per_proc];
    int final_result[N];

    if(rank == 0){
        matrix = (int*)malloc(N * N * sizeof(int));
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                matrix[i * N + j] = i + j;
            }
        }

        for(int i = 0; i < N; ++i){
            vector[i] = i + 1;
        }

        printf("Matrix:\n");
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                printf("%d ", matrix[i * N + j]);
            }
            printf("\n");
        }
        printf("\n");
        printf("Vector:\n");
        for(int i = 0; i < N; ++i){
            printf("%d ", vector[i]);
        }
        printf("\n");
    }

    MPI_Bcast(vector, N, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(
        matrix, rows_per_proc * N, MPI_INT, 
        local_matrix, rows_per_proc * N, MPI_INT, 
        0, MPI_COMM_WORLD
    );

    for(int i = 0; i < rows_per_proc; ++i){
        local_result[i] = 0;
        for(int j = 0; j < N; ++j){
            local_result[i] += local_matrix[i * N + j] * vector[j];
        }
    }

    MPI_Gather(
        local_result, rows_per_proc, MPI_INT,
        final_result, rows_per_proc, MPI_INT,
        0, MPI_COMM_WORLD
    );

    if(rank == 0){
        printf("Result of Matrix-Vector Multiplication:\n");
        for(int i = 0; i < N; ++i){
            printf("%d ", final_result[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
