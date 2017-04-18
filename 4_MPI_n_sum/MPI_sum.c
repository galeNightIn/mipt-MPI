#include <stdio.h>
#include <mpi.h>


#define N 1000000

int main(int argc, char const *argv[])
{	

	// Initialize MPI enviroment
	MPI_Init(NULL, NULL);

	double msg = 0;
	double sum_proc = 0;
	int i = 0;

	// Get the number of processes
	int world_comm_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_comm_size);
	double mass[world_comm_size];

	// Get the rank of processes
	int world_comm_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_comm_rank);

	mass[world_comm_rank] = 0.0;



	for( i = world_comm_rank + 1; i < N - (world_comm_size - world_comm_rank - 1); i += world_comm_size ){
		//printf(" i = %f rank %d\n" , mass[world_comm_rank], world_comm_rank );

		mass[world_comm_rank] += (1.0 / i);
		//printf("%f rank is %d\n", sum_proc, world_comm_rank );
	}

	if(world_comm_rank == 0){
			msg = mass[world_comm_rank];
			MPI_Send(&msg, 1, MPI_DOUBLE, (world_comm_rank + 1), 0, MPI_COMM_WORLD);
			MPI_Recv(&msg, 1, MPI_DOUBLE, (world_comm_size - 1), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			//printf("Process %d received message %d from process %d\n", world_comm_rank, msg, world_comm_size - 1);
			printf("SUUUUUMM   %f \n", msg);
	} else {
			MPI_Recv(&msg, 1, MPI_DOUBLE, (world_comm_rank - 1), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			msg = msg + mass[world_comm_rank];
			MPI_Send(&msg, 1, MPI_DOUBLE, (world_comm_rank + 1) % world_comm_size, 0, MPI_COMM_WORLD);
			//printf("Process %d received message %d from process %d\n", world_comm_rank, msg, world_comm_rank - 1);

	}
	
	
	
	MPI_Finalize();

	return 0;
}