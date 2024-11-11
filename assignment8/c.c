#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

const int N = 1000;
int *arr;
int temp[1000];

int main(int argc, char **argv){
    arr = (int*)malloc(N * sizeof(int));
    for(int i = 0; i < N; ++i){
        arr[i] = i + 1;
    }

    int rank, num_procs;
    int elements_per_process, n_elements_received;

    MPI_Status status;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    if(rank == 0){
        elements_per_process = N / num_procs;
        for(int i = 1; i < num_procs - 1; ++i){
            int index = i * elements_per_process;

            MPI_Send(&elements_per_process, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&arr[index], elements_per_process, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        int i = num_procs - 1;
        int index = i * elements_per_process;
        int elements_left = N - index;

        MPI_Send(&elements_left, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        MPI_Send(&arr[index], elements_left, MPI_INT, i, 0, MPI_COMM_WORLD);

        int sum = 0;
        for(int i = 0; i < elements_per_process; ++i){
            sum += arr[i];
        }

        for(int i = 1; i < num_procs; ++i){
            int tmp;
            MPI_Recv(&tmp, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            sum += tmp;
        }

        printf("Sum of array is : %d\n", sum);
    }
    else{
        MPI_Recv(&n_elements_received, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&temp, n_elements_received, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        printf("Process %d: %d elements received\n", rank, n_elements_received);

        int partial_sum = 0;
        for(int i = 0; i < n_elements_received; ++i){
            partial_sum += temp[i];
        }

        printf("Process %d: partial sum %d\n", rank, partial_sum);

        MPI_Send(&partial_sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
