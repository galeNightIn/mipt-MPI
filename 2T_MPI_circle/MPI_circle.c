// Written by Solovev Alexandr 2017
// Here we use MPI to show  
// circle sending of buffer
// from 0 rank to Nth to 0 and so on
// using point-to-point functions

// includes 

#include <stdio.h>
#include <mpi.h>

// code

int main(int argc, char const *argv[])
{	
	const int MAX_ITERATIONS = 2;
	// Initialize MPI enviroment
	MPI_Init(NULL, NULL);

	// Get the number of processes
	int world_comm_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_comm_size);

	// Get the rank of processes
	int world_comm_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_comm_rank);

	int msg = 2017;

	int circle_count = 0;
	while(circle_count < MAX_ITERATIONS)
	{
		if(world_comm_rank == 0){
			MPI_Send(&msg, 1, MPI_INT, (world_comm_rank + 1), 0, MPI_COMM_WORLD);
			MPI_Recv(&msg, 1, MPI_INT, (world_comm_size - 1), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("Process %d received message %d from process %d\n", world_comm_rank, msg, world_comm_size - 1);
		} else {
			MPI_Recv(&msg, 1, MPI_INT, (world_comm_rank - 1), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Send(&msg, 1, MPI_INT, (world_comm_rank + 1) % world_comm_size, 0, MPI_COMM_WORLD);
			printf("Process %d received message %d from process %d\n", world_comm_rank, msg, world_comm_rank - 1);
		}

		circle_count ++;
	}

	MPI_Finalize();

	return 0;
}