#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv){

    MPI_Init(&argc, &argv);

    int rank, num_procs;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    printf("Rank: %d, number processes: %d\n", rank, num_procs);

    MPI_Finalize();
    return 0;
}
