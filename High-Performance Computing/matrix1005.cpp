#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc,char *argv[]){
	int n=strtol(argv[1],NULL,10);
	double **a=NULL,**b=NULL,**c=NULL;
	a=(double **)malloc(sizeof(double*)*n);
	b=(double **)malloc(sizeof(double*)*n);
	c=(double **)malloc(sizeof(double*)*n);
	for(int i=0;i<n;i++){
		a[i]=(double*)malloc(sizeof(double)*n);
		b[i]=(double*)malloc(sizeof(double)*n);
		c[i]=(double*)malloc(sizeof(double)*n);
	}
	
	for(int i=0;i<argc;i++)
	{
		printf("%s\n",argv[i]);
	}
	
	int cnt=2;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			a[i][j]=strtod(argv[cnt],NULL);
			printf("%lf ",a[i][j]);
		}
		printf("\n");
	}
		printf("\n");
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			b[i][j]=strtod(argv[cnt],NULL);
			printf("%lf ",a[i][j]);
		}
		printf("\n");
	}
		printf("\n");
		
	time_t t1=time(NULL);
	
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			double total=0;
			for(int k=0;k<n;k++){
				total+=a[i][k]*b[k][j];
			}
			c[i][j]=total;
		}
	}
	time_t t2=time(NULL);
	
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			printf("%lf ",c[i][j]);
		}
		printf("\n");
	}
	
	printf("calculation time: %d s\n",(t2-t1));
	for(int i=0;i<n;i++){
		free(a[i]);
		free(b[i]);
		free(c[i]);
	}
	free(a);
	free(b);
	free(c);
	return 0;
}