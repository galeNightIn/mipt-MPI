// Written by Solovev Alexandr 2017
// Here we use MPI to show how 
// created processes display information
// by number of processes

// includes 
#include <stdio.h>
#include <mpi.h>

// code

int main(int argc, char const *argv[])
{	
	// Initialize MPI enviroment
	MPI_Init(NULL, NULL);

	// Get the number of processes
	int world_comm_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_comm_size);

	// Get the rank of processes
	int world_comm_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_comm_rank);

	// Every process with his unique rank call this function independantly and at the same time
	// But you never knows wich process start to run this func first
	printf("Hello world with RANK %d, size of communicator is %d\n", world_comm_rank, world_comm_size);

	// We are done and shoud say to finalize all created processes
	MPI_Finalize();

	return 0;
}
