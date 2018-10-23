#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<mpi.h>

char a[100000000];
int main(){
  int i,j,total=0,NUM,smallest,count=0;
  double I_start,I_end;
  MPI_Init(NULL,NULL);
  int W_size;
  MPI_Comm_size(MPI_COMM_WORLD,&W_size);
  int W_rank;
  MPI_Comm_rank(MPI_COMM_WORLD,&W_rank);
  if(W_rank==0){
    scanf("%d",&NUM);
  }
  I_start=MPI_Wtime();
  MPI_Bcast(&NUM,1,MPI_INT,0,MPI_COMM_WORLD);
  int begin=(NUM*W_rank/W_size)+1;
  int end=(NUM*(W_rank+1)/W_size);
  if(begin==1)
    begin++;
  for(i=begin;i<=end;i++){
    a[i]=1;
  }
  if(W_rank==0){
    for(i=2;i<NUM;i++){
      if(a[i]==1){
        if(i*i>=NUM){
          //printf("done,i=%d\n",i);
          break;
        }
        for(j=begin;j*i<=end;j++){
          a[j*i]=0;
        }
        MPI_Bcast(&i,1,MPI_INT,0,MPI_COMM_WORLD);
      }
    }
    i=0;
    MPI_Bcast(&i,1,MPI_INT,0,MPI_COMM_WORLD);
  }
  else{
    while(1){
      MPI_Bcast(&i,1,MPI_INT,0,MPI_COMM_WORLD);
      if(i==0) break;
      if(begin%i==0){
        smallest=begin;
      }
      else{
        smallest=(begin/i+1)*i;
      }
      for(j=smallest;j<=end;j+=i){
        a[j]=0;
      }
    }
  }
  for(i=begin;i<=end;i++){
    if(a[i]==1){
      count++;
    }
  }
  printf("process %d find : %d\n",W_rank,count);
  MPI_Reduce(&count,&total,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
  I_end=MPI_Wtime();
  MPI_Barrier(MPI_COMM_WORLD);
  if(W_rank==0){
    printf("total = %d\ntime = %f\n",total,I_end-I_start);
  }

  MPI_Finalize();

  return 0;
}