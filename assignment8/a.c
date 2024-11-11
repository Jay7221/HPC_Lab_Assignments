#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv){
    MPI_Init(&argc, &argv);

    int rank, num_procs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    int N = 1000000;        // Large size of message to force blocking
    int *send_data = (int*)malloc(N * sizeof(int));
    int *recv_data = (int*)malloc(N * sizeof(int));

    for(int i = 0; i < N; ++i){
        send_data[i] = rank + i;
    }

    if(rank == 0){
        MPI_Send(send_data, N, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(recv_data, N, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    else if(rank == 1){
        MPI_Send(send_data, N, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Recv(recv_data, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    printf("Process %d: Received data: %d\n", rank, recv_data[0]);

    MPI_Finalize();
    return 0;
}
