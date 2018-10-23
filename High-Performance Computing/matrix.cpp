#include <stdio.h>
#include <time.h>
int main() {
	int x;
	scanf("%d",&x);
	int m,n,p;
	m=x;n=x;p=x;
    int A[m+1][n+1], B[n+1][p+1], C[m+1][p+1];
    int i, j, k;

    
    for (i =1 ; i<=x; i++) {
        for(j=1;j<=x;j++) {
            scanf("%f",&A[i][j]);
        }
    }

    
    for (i=1;i<=x;i++) {
        for(j=1;j<=x;j++) {
            scanf("%f",&B[i][j]);
        }
    }

    for (i=1; i<=m; i++) {
        for (j=1; j<=p; j++) {
            C[i][j]=0; 
            for(k = 1; k <= n; k++) {
                C[i][j] = C[i][j] +A[i][k] * B[k][j]; 
            }
            printf("%f ", C[i][j]);
        }
        printf("\n");
    }
    
    time_t timeBegin, timeEnd;
	timeBegin = time(NULL);
	
	timeEnd = time(NULL);
	printf("%f\n", timeEnd - timeBegin);
    
}

