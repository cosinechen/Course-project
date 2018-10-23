#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void printall(double ** c, int n){
	for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%lf ",c[i][j]);
        }
        printf("\n");
	}
}

int main(int argc,char *argv[]){
    int n;
    scanf("%d",&n);
    double **a=NULL,**b=NULL,**c=NULL;
    a=(double **)malloc(sizeof(double*)*n);
    b=(double **)malloc(sizeof(double*)*n);
    c=(double **)malloc(sizeof(double*)*n);
    for(int i=0;i<n;i++){
        a[i]=(double*)malloc(sizeof(double)*n);
        b[i]=(double*)malloc(sizeof(double)*n);
        c[i]=(double*)malloc(sizeof(double)*n);
    }

    int cnt=2;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            a[i][j]=1.1;
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            
            b[i][j]=1.1;
        }
        
    }
   
    double t1,t2;
    t1=clock();

    /*for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            double total=0;
            for(int k=0;k<n;k++){
                total+=a[i][k]*b[k][j];
            }
            c[i][j]=total;
        }
    }*/
	
	for(int i=0;i<n;i++){
		for(int k=0;k<n;k++){
			double total=a[i][k];
			for(int j=0;j<n;j++)
            c[i][j]+=total*b[k][j];
        }
    }
	
    t2=clock();

    //printall(c, n);

 printf("calculation time: %lf s \n",(t2-t1)/(CLOCKS_PER_SEC));
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
