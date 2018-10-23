#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<mpi.h>

#define BLOCK_LOW(id,p,n)(id*n/p)
#define BLOCK_HIGH(id,p,n)(BLOCK_LOW((id)+1,p,n)-1)
#define BLOCK_SIZE(id,p,n)(BLOCK_LOW((id)+1,p,n)-BLOCK_LOW(id,p,n))
#define BLOCK_OWNER(index,p,n)(p*((index+1)-1)/n)

int main(int argc,char *argv[]){
	FILE *fp;
	int id,p,n;
	if((fp=fopen(argv[1],"r"))==NULL){
		printf("fopen error\n");
		exit(EXIT_FAILURE);
	}
	fscanf(fp,"%d",&n);
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&id);
	MPI_Comm_size(MPI_COMM_WORLD,&p);
	int size=BLOCK_SIZE(id,p,n),min=BLOCK_LOW(id,p,n),max=BLOCK_HIGH(id,p,n),tmp;
	int **B=(int **)malloc(sizeof(int *)*size);
	for(int i=0;i<min*n;i++)
		fscanf(fp,"%d",&tmp);
	for(int i=min;i<=max;i++){
		B[i-min]=(int *)malloc(sizeof(int)*n);
		for(int j=0;j<n;j++){
			fscanf(fp,"%d",&tmp);
			B[i-min][j]=tmp;
		}
	}
	fclose(fp);

	if(id!=0)
		MPI_Recv(&tmp,1,MPI_INT,id-1,0,MPI_COMM_WORLD,NULL);
	else
		printf("Original:\n");
	for(int i=0;i<size;i++){
		for(int j=0;j<n;j++){
			printf("%d ", B[i][j]);
		}
		printf("\n");
	}

	if(id-1!=p)
		MPI_Send(&tmp,1,MPI_INT,id+1,0,MPI_COMM_WORLD);
	else
		printf("\n");
	MPI_Barrier(MPI_COMM_WORLD);

	double t=MPI_Wtime(),time;
	for(int k=0;k<n;k++){
		for(int i=0;i<n;i++){
			if(BLOCK_OWNER(i,p,n)!=id)
				continue;
			for(int j=0;j<n;j++){
				int val=B[i-min][j],tid;
				if(i!=k&&j!=k){
					tid=BLOCK_OWNER(k,p,n);
					if(tid==id)
						tmp=B[k-min][j];
					else{
						MPI_Recv(&tmp,1,MPI_INT,tid,k*n+j+1,MPI_COMM_WORLD,NULL);
					}

					if(tmp==-1||B[i-min][k]==-1)
						tmp=-1;
					else
						tmp+=B[i-min][k];

					if(tmp!=-1&&(tmp<val||val==-1))
						val=tmp;
				}
				B[i-min][j]=val;
				for(int l=0;l<n;l++){
					tid=BLOCK_OWNER(l,p,n);
					if(tid!=id){
						MPI_Send(&val,1,MPI_INT,tid,i*n+j+1,MPI_COMM_WORLD);
					}
				}
			}
		}
	}
	t=MPI_Wtime()-t;

	if(id!=0)
		MPI_Recv(&tmp,1,MPI_INT,id-1,n*n+1,MPI_COMM_WORLD,NULL);
	else
		printf("Result:\n");
	for(int i=0;i<size;i++){
		for(int j=0;j<=n;j++){
			printf("%d ",B[i][j]);
		}
		free(B[i]);
		printf("\n");
	}
	free(B);
	if(id+1!=p)
		MPI_Send(&tmp,1,MPI_INT,id+1,n*n+1,MPI_COMM_WORLD);

	MPI_Reduce(&t,&time,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	printf("Process %d is done. Time :%lf s\n",id,t);
	MPI_Finalize();
	if(id==0)
		printf("Average Time: %lf s\n", time/p);
	return 0;
}