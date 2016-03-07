#include<stdio.h>
#include<malloc.h>

int * allPaths(int * cost,int n)
{
  int i,j,k,*a;
  a=(int *)malloc(sizeof(int)*n*n);
  for(i=0;i<n;i++)
    for(j=0;j<n;j++)
	a[i*n+j]=cost[i*n+j];
  for(k=0;k<n;k++)
    for(i=0;i<n;i++)
      for(j=0;j<n;j++)
	  a[i*n+j]=(a[i*n+j]>a[i*n+k]+a[k*n+j])?(a[i*n+k]+a[k*n+j]):(a[i*n+j]);

  return a;

}

int main()
{
  int *cost,*a,i,j,n;
  
  printf("\nEnter number of nodes ...");
  scanf("%d",&n);//exit
  cost=(int *)malloc(sizeof(int)*n*n);
  
  printf("\nEnter the graph as its cost matrix ...\n");
  
  for(i=0;i<n;i++)
    for(j=0;j<n;j++)
      {
	if(i==j)
	{
	  cost[i*n+j]=0;
	  continue;
	}
	printf("\nEnter cost of edge[%d,%d][999 for non existent edge]...",i+1,j+1);
	scanf("%d",&cost[i*n+j]);
      }

  //calling floyd
  a=allPaths(cost,n);

  printf("\nPrinting Shortest path lengths in the form of matrix ...\n\n");
  
  for(i=0;i<n;i++)
   {
      for(j=0;j<n;j++)
	  printf("%d\t",a[i*n+j]);
      printf("\n");
  }
  return 0;
}