#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv){

    MPI_Init(&argc, &argv);

    int rank, num_procs;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    printf("%d: Hello world from %d of %d\n", rank, rank, num_procs);

    MPI_Finalize();
    return 0;
}
