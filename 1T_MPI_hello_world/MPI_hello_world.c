// Written by Solovev Alexandr 2017
// Here we use MPI to show how 
// created processes display information
// by number of processes

// includes 
#include <stdio.h>
#include <mpi.h>
// code

#define N 100000

int main(int argc, char const *argv[])
{	
	// Initialize MPI enviroment
	MPI_Init(NULL, NULL);
	double start;
	double finish;

	int msg[N]={};

	// Get the number of processes
	int world_comm_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_comm_size);

	// Get the rank of processes
	int world_comm_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_comm_rank);


	//int* msg =(int*)malloc(N*sizeof(int));

	
	start = MPI_Wtime();
	MPI_Send(&msg, N, MPI_INT, 1, 0, MPI_COMM_WORLD);
	MPI_Recv(&msg, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	finish = MPI_Wtime();

	// Every process with his unique rank call this function independantly and at the same time
	// But you never knows wich process start to run this func first
	printf("TIME IS %f\n", finish - start);

	// We are done and shoud say to finalize all created processes
	MPI_Finalize();

	return 0;
}
