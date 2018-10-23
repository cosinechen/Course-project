#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc,char *argv[]){
        int n,p;
    int block=n/(p+1);
        scanf("%d",&n);
    scanf("%d",&p);
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
                        a[i][j]=strtod(argv[cnt],NULL);
                        a[i][j]=1.1;
                }
        }

        for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                        b[i][j]=strtod(argv[cnt],NULL);
                        b[i][j]=1.1;
                }
        }

        double t1,t2;
        t1=clock();

        for(int m=0;m<n;m+block){
            for(int l=0;l<n;l+block){

                for(int i=0;i<block;i++){
                    for(int j=0;j<block;j++){
                        double total=0;
                        for(int k=0;k<n;k++){
                            total+=a[i+m][k]*b[k][j+l];
                        }
                        c[i][j]=total;
                    }
                }

            }
                }

        t2=clock();

        for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                        printf("%lf ",c[i][j]);
                }
                printf("\n");
}

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
                         