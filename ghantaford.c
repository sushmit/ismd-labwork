#include<stdio.h>
#include<malloc.h>

int * ghanta(int v,int *cost,int n)
{
  int i,k,u,*d;
  
  d=(int *)malloc(sizeof(int)*n);
  
  for(i=0;i<n;i++)
    d[i]=cost[v*n+i];
  for(k=0;k<n-2;k++)
    for(u=0;u<n;u++)
      if(u!=v)
	  for(i=0;i<n;i++)
	      if(d[u]>d[i]+cost[i*n+u])
		  d[u]=d[i]+cost[i*n+u];
  return d;
}

int main()
{
  int *d,*cost,n,i,j,v;
  
  printf("\nEnter number of vertices ..");
  scanf("%d",&n);
  
  cost=(int *)malloc(sizeof(int)*n*n);
  
  for(i=0;i<n;i++)
    for(j=0;j<n;j++)
      cost[i*n+j]=999; //999 is taken to be infinty
  for(i=0;i<n;i++)
    cost[i*n+i]=0;

  printf("\nEnter the graph ...");
  printf("\nEnter 0 for start and destination to finish entering process ...\n");
  while(1)
  {
    printf("\nStart =");
    scanf("%d",&i);
    printf("\nDestination = ");
    scanf("%d",&j);
    if(i==0 && j==0)
	break;
    printf("\nCost = ");
    scanf("%d",&v);
    cost[(i-1)*n+j-1]=v;
  }
  printf("\n\nEnter Source vertex ...");
  scanf("%d",&v);
  
  //calling ghanta
  d=ghanta(v-1,cost,n);

  printf("\nPrinting results ...\n");
  for(i=0;i<n;i++)
    printf("\nPath Length to %d = %d",i+1,d[i]);
  
printf("\nProgrammed by:Sushmit Kumar\n\nHappy Programming to all !\n");
  return 0;
 
}