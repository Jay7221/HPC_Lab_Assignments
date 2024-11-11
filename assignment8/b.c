#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv){
    MPI_Init(&argc, &argv);

    int rank, num_procs;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    int send_data = rank;
    int recv_data;

    int next_rank = (rank == num_procs - 1) ? 0: rank + 1;
    int prev_rank = (rank == 0) ? num_procs - 1: rank - 1;

    if(rank & 1){
        MPI_Send(&send_data, 1, MPI_INT, next_rank, 0, MPI_COMM_WORLD);
        MPI_Recv(&recv_data, 1, MPI_INT, prev_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    else{
        MPI_Recv(&recv_data, 1, MPI_INT, prev_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(&send_data, 1, MPI_INT, next_rank, 0, MPI_COMM_WORLD);
    }

    printf("%d: received data %d from process %d\n", rank, recv_data, prev_rank);

    MPI_Finalize();
    return 0;
}
