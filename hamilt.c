#include<stdio.h>
#include<malloc.h>

void nextValue(int *g,int *x,int k,int n)
{  int j;

	while(1)
	{

	 x[k]=(x[k]+1)%(n+1);
	 if(x[k]==0)
		return;
	 if(g[(x[k-1]-1)*n+x[k]])
	 {
		for(j=1;j<=k-1;j++)
			if(x[k]==x[j])
				break;

		if(j==k)
			if((k<n) || ((k==n) && g[(x[n]-1)*n+x[1]]))
				return;

	 }
	}
}


void hamilt(int *g,int *x,int k,int n)
{  static int N=0;
	int i;
	while(1)
	{
		nextValue(g,x,k,n);
		if(x[k]==0)
			return;

		if(k==n)
			{
				N++;
            printf("\nSolution #%d\n",N);
				for(i=1;i<=n;i++)
					printf("%d\t",x[i]);

				printf("\n\n");
			}
		else
		hamilt(g,x,k+1,n);

	}
}

void main()
{
 int *g,*x,n,i,j;

 printf("\nEnter number of nodes ...\n");
 scanf("%d",&n);



 g=(int *)malloc((n*n+1)*sizeof(int));
 x=(int *)malloc((n+1)*sizeof(int));

 printf("\n\nEnter graph ...\n[enter 1 if vertices are connected, otherwise 0]\n\n");
 for(i=1;i<=n;i++)
	for(j=1;j<=n;j++)
		if(j>i)
		{
			printf("\nVertex %d and %d ?",i,j);
			scanf("%d",&(g[(i-1)*n+j]));
		}
		else if(j==i)
			g[(i-1)*n+j]=1;
		else
			g[(i-1)*n+j]=g[(j-1)*n+i];

 //for(i=1;i<=n;i++){printf("\n");for(j=1;j<=n;j++)printf("%d\t",g[(i-1)*n+j]);}


x[1]=1;
for(i=2;i<=n;i++)
	x[i]=0;
hamilt(g,x,2,n);

printf("\n\nProgrammed by:Sushmit Kumar, 10437\n\n!\tHappy Programming to all\t!\n");


}

