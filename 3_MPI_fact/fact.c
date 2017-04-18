#include <stdio.h>
#include <mpi.h>
#include <math.h>


int Tree(int l, int r)
{
	    if (l > r)
	        return 1;
	    if (l == r)
	         return l;
	    if (r - l == 1)
	        return 	l * r;
	    int m = (l + r) / 2;
	    return Tree(l, m) * Tree(m + 1, r);
}


int main(int argc, char const *argv[])
{	
	
	int N = 11;

	
	MPI_Init(NULL, NULL);

	
	int msg = 1;
	
	int world_comm_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_comm_size);

	int mass[world_comm_size];
	int count = N / world_comm_size;
	//printf("COUNT = %d\n", count);
	int count1 = N / (world_comm_size - 1);
	int div = N % world_comm_size;
	//printf("DIV = %d\n", div);

	int world_comm_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_comm_rank);
	

	if (div == 0){

		mass[world_comm_rank] = Tree((world_comm_rank * count + 1), ((world_comm_rank + 1) * count));
		//printf("RANK  = %d  \n", world_comm_rank);
		
	
	
		if(world_comm_rank == 0){
				msg = mass[world_comm_rank];
				MPI_Send(&msg, 1, MPI_INT, (world_comm_rank + 1), 0, MPI_COMM_WORLD);
				MPI_Recv(&msg, 1, MPI_INT, (world_comm_size - 1), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				printf("message %d \n", msg);
		} else {
				MPI_Recv(&msg, 1, MPI_INT, (world_comm_rank - 1), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				msg = msg * mass[world_comm_rank];
				MPI_Send(&msg, 1, MPI_INT, (world_comm_rank + 1) % world_comm_size, 0, MPI_COMM_WORLD);
				// printf("Process %d received message %d from process %d\n", world_comm_rank, msg, world_comm_rank - 1);
		}
	}	
	
	else {

		if (((world_comm_rank + 1) * count1) < N){
		mass[world_comm_rank] = Tree((world_comm_rank * count1 + 1), ((world_comm_rank + 1) * count1));
		//printf("RANK  = %d  \n", world_comm_rank);
		}
		else{
			mass[world_comm_rank] = Tree((world_comm_rank * count1 + 1), N);
		}
	
	
		if(world_comm_rank == 0){
				msg = mass[world_comm_rank];
				MPI_Send(&msg, 1, MPI_INT, (world_comm_rank + 1), 0, MPI_COMM_WORLD);
				MPI_Recv(&msg, 1, MPI_INT, (world_comm_size - 1), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				printf("message %d \n", msg);
		} else {
				MPI_Recv(&msg, 1, MPI_INT, (world_comm_rank - 1), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				msg = msg * mass[world_comm_rank];
				MPI_Send(&msg, 1, MPI_INT, (world_comm_rank + 1) % world_comm_size, 0, MPI_COMM_WORLD);
				// printf("Process %d received message %d from process %d\n", world_comm_rank, msg, world_comm_rank - 1);
		}

	}
	



	MPI_Finalize();

	return 0;
}


