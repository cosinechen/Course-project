#include <mpi.h>
#include <stdio.h>
#define EXTRACT_BIT(n,i)((n&(1<<i))?1:0)

int main(int argc, char *argv[])
{
	int i;
	int id;
	int p;
	int global_solutions;
	int solutions;
	int check_circuit(int, int);
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	
	solutions=0;
	for(i=id;i<65535;i+=p)
	{
		solutions+=check_circuit(id,i);
	}
	
	MPI_Reduce(&solutions,&global_solutions,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	printf("Process %d finish!\n", id);
	fflush(stdout);
	MPI_Finalize();
	if(id==0)
		printf("There are %d different solutions\n",global_solutions);
	return 0;
}	
	int check_circuit(int id, int z)
	{
		int A[16];
		int i;
		
		for(i=0;i<16;i++)
			A[i]=EXTRACT_BIT(z,i);
		if
		(
			(A[0]|A[1])&(!A[1]|!A[3])&(A[2]|A[3])&(!A[3]|!A[4])&(!A[5]|A[4])&(A[5]|A[6])&(!A[6]|A[5])&(A[7]|!A[8])&(A[8]|A[9])&(A[8]|!A[9])&(!A[9]|!A[10])&(A[10]|A[11])&(A[11]|A[9])&(A[12]|A[13])&(!A[7]|!A[13])&(A[13]|!A[14])&(A[14]|A[15])&(!A[15]|A[6])
		)
		{
			printf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",A[0],A[1],A[2],A[3],A[4],A[5],A[6],A[7],A[8],A[9],A[10],A[11],A[12],A[13],A[14],A[15]);
			fflush(stdout);
			return 1;
		}
		fflush(stdout);
		return 0;
	}
