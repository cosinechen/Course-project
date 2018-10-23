#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<mpi.h>

int main()
{
	MPI_Init(NULL,NULL);
	int A[16]={0};
	int sum=0,myid;
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	for(int i=myid;i<65536;i+=3)
	{
		int temp=i;
		bool *ip=(bool *)malloc(sizeof(bool)*16);
		while(temp)
		{
			for(int j=15;j>=0;j--)
			{
				A[j]=temp%2;
				temp/=2;
			}			
		}
	
		int ans=(A[0]|A[1])&(A[1]|!A[3])&(A[2]|A[3])&(!A[3]|!A[4])&(!A[5]|A[4])&(A[5]|A[6])&(!A[6]|A[5])&(A[7]|!A[8])&(A[8]|A[9])&(A[8]|!A[9])&(!A[9]|!A[10])&(A[10]|A[11])&(A[11]|A[9])&(A[12]|A[13])&(!A[7]|!A[13])&(A[13]|!A[14])&(A[14]|A[15])&(!A[15]|A[6]);
		if(ans==1)
		{
			sum++;
			
			printf("%d",myid);
			for(int j=0;j<16;j++){
				printf("%d",ip[j]);
			}
			printf("\n");
		}						
	}
	
	printf("%d Process %d is done.\n",sum,myid);
	
	MPI_Finalize();
}
