#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//prime
int main()
{
	int k,m,n,count=0,i,j;
	scanf("%d",&n);
	int *arr=malloc(n*sizeof(int));
	for(j=0;j<n;j++){
		arr[j]=0;
	}
	arr[0]=1;arr[1]=1;
	//int *arr=calloc(n, sizeof(int));
	for(k=2;k*k<=n;k++){
		for(m=k;m*k<=n;m++){
			arr[m*k]=1;
			//printf("%d %d\n",m*k,arr[m*k]);
		}
	}
	
	for(i=0;i<=n;i++){
		if(arr[i]==0){
		count++;
		}
	}
	printf("%d",count);
	
	free(arr);
	return 0;
}
