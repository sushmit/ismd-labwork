#include<stdio.h>

int ABS(int n)
{
	if(n>=0)
		return n;
	else
		return -1*n;
}
int place(int * x,int   k,int i)
{
	int j;
	for(j=1;j<k;j++)
		if((x[j]==i) || (ABS(x[j]-i)==ABS(j-k)))
			return 0;

	return 1;
}

int nQueen(int * x,int k,int n)
{
	int i,j;
	static int N=0;

	for(i=1;i<n+1;i++)
		if(place(x,k,i))
		{
			x[k]=i;
			if(k==n)
			{
				N++;
				printf("\nSolution #%d\n\n",N);
				for(j=1;j<n+1;j++)
					printf("Position of Queen #%d=[ %d , %d ]\n",j,j,x[j]);
				printf("\n=======================================\n");

			}
			else
				nQueen(x,k+1,n);
		}
}

int CallNQueen(int n)
{
	int x[n+1];
	nQueen(x,1,n);
}

int main()
{
	int n;
	printf("\nEnter number of Queens ...\n");
	scanf("%d",&n);
	if(n>0)	
		CallNQueen(n);
	else
		printf("\nEnter positive number for Queens SILLY !\n");
	printf("\nProgrammed by:Sushmit Kumar\n\n!\tHappy Programming to All\t!\n");

	return 0;
}
					

