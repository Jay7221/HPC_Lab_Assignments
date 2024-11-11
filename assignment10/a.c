#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    MPI_Init(&argc, &argv);

    int rank, num_procs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    const int MESSAGE_SIZE = 1024;
    char message[MESSAGE_SIZE];

    if(rank == 0){
        for(int i = 0; i < MESSAGE_SIZE; ++i){
            message[i] = 'A';
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);

    double start_time = MPI_Wtime();

    MPI_Bcast(message, MESSAGE_SIZE, MPI_CHAR, 0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime();
    double total_time = end_time - start_time;

    if(rank == 0){
        printf("Broadcast Time with %d processes: %f seconds\n", num_procs, total_time);
    }

    MPI_Finalize();
    return 0;
}
