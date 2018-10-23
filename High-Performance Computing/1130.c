#include<stdio.h>

int main()
{
	int A[16]={0};
	int sum=0;
	
	for(int i=0;i<65536;i++)
	{
		int temp=i;
		while(temp)
		{
			for(int j=15;j>=0;j--)
			{
				A[j]=temp%2;
				temp/=2;
			}			
		}
	
		int ans=(A[0]|A[1])&(A[1]|!A[3])&(A[2]|A[3])&(!A[3]|!A[4])&(!A[5]|A[4])&(A[5]|A[6])&(!A[6]|A[5])&(A[7]|!A[8])&(A[8]|A[9])&(A[8]|!A[9])&(!A[9]|!A[10])&(A[10]|A[11])&(A[11]|A[9])&(A[12]|A[13])&(!A[7]|!A[13])&(A[13]|!A[14])&(A[14]|A[15])&(!A[15]|A[6]);
		if(ans==1){
			sum++;
			//printf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",A[0],A[1],A[2],A[3],A[4],A[5],A[6],A[7],A[8],A[9],A[10],A[11],A[12],A[13],A[14],A[15]);
		}			
	}
	
	printf("%d",sum);
	
	return 0;
}
