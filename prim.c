#include<stdio.h>
#include<malloc.h>

int minCost(int *near,unsigned int *cost,int n)
{
	int minI,i;
	minI=-1;
	for(i=0;i<n;i++)
	{
		if(near[i]!=-1)
			if(minI==-1)
				minI=i;
			else
				if(cost[i*n+near[i]]<cost[minI*n+near[minI]])
					minI=i;
	}
	//printf("\nminI=%d",minI);
	return minI;				
}

int main()
{
	int i,j,k,n,mincost=0;
	int *t,*near;
	unsigned int *cost;
	printf("\nEnter number of nodes ...\n");
	scanf("%d",&n);
	
	//allocating memory ....
	
	cost=(unsigned int *)malloc(sizeof(unsigned int)*n*n);
	t=(int *)malloc(sizeof(int)*2*(n-1));
	near=(int *)malloc(sizeof(int)*n);
	
	
	printf("\nEnter the graph in the form of costs of edges ...\n");
	printf("Enter -1 for non existent edges.\n\n");
	
	//entering the graph in the form of cost matrix
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			printf("Enter cost of edge (%d,%d) ...",i+1,j+1);
			scanf("%u",&cost[i*n+j]);
		}
	
	//inititalzing near[] array
	for(i=1;i<n;i++)
		near[i]=0;
	
	near[0]=-1;
	
	//building the tree ....
	
	for(i=0;i<n-1;i++)
	{
		//printf("\nthe for loop\n\n");
		j=minCost(near,cost,n);
		t[i*(n-1)]=j;
		t[i*(n-1)+1]=near[j];
		mincost+=cost[j*n+near[j]];
		near[j]=-1;
		for(k=0;k<n;k++)
			if((near[k]!=-1) && (cost[k*n + near[k]]>cost[k*n+j]))
				{
				near[k]=j;
			//	printf("\n\nnear[%d]=%d",k,near[k]);
				}
		
	}
	
	printf("\nThe minimum cost is %d",mincost);
	
	return 0;

}
