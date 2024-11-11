#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
    MPI_Init(&argc, &argv);

    int rank, num_procs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    const int MESSAGE_SIZE = atoi(argv[1]);
    int message[MESSAGE_SIZE];
    int result[MESSAGE_SIZE];

    if(rank == 0){
        for(int i = 0; i < MESSAGE_SIZE; ++i){
            message[i] = i + 1;
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);

    double start_time = MPI_Wtime();

    MPI_Reduce(message, result, MESSAGE_SIZE, MPI_INT, MPI_BOR, 0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime();
    double total_time = end_time - start_time;

    if(rank == 0){
        printf("Reduce Time with message size %d and %d processes: %f seconds\n", MESSAGE_SIZE, num_procs, total_time);
    }

    MPI_Finalize();
    return 0;
}
