#include<stdio.h>
#include<malloc.h>

struct vert
{
	int sel;
	int dist;
};

//selMin:finds the vertex with minimum dist which is still not selected 
//v=pointer to the basee of array
//n=length of the array
//the array starts with index 0
int selMin(struct vert *v,int n)
{
	int i,si=-1;
	for(i=0;i<n;i++)
		if(((si==-1) || (v[si].dist>v[i].dist)) && !(v[i].sel))
				si=i;
	
	return si;	
}

//dijks:finds shortest paths
/*
	v=pointer to base3 of vertex array
	n=no. of nodes
	cost=cost matrix of the graph
	s=source vertex
*/
//the shortest paths get stored in the vertices till the end

void dijks(struct vert *v,int *cost,int s,int n)
{
	int i,j,k;
	for(i=0;i<n;i++)
	{	
		v[i].sel=0;
		v[i].dist=cost[s*n+i];
	}
	v[s].sel=1;
	v[s].dist=0;
	
	for(i=0;i<n-2;i++)
	{
		j=selMin(v,n);
		v[j].sel=1;
		for(k=0;k<n;k++)
			if(!(v[k].sel))
				if((cost[j*n+k]>=0) && (v[k].dist>v[j].dist+cost[j*n+k]))
					v[k].dist=v[j].dist+cost[j*n+k];
				
						
	}	
}



int main()
{
	struct vert *v;
	int *cost;
	int s,n,i,j;
	
	printf("\nEnter number of nodes ...\n");
	scanf("%d",&n);
	
	//alloctaing memory
	cost=(int *)malloc(sizeof(int)*n*n);
	v=(struct vert *)malloc(sizeof(struct vert)*n);
	
	//inputting graph
	printf("\nEnter the graph in the form of costs of edges ...\n");
	printf("Enter -1 for non existent edges.\n\n");
	
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			printf("Enter cost of edge (%d,%d) ...",i+1,j+1);
			scanf("%d",&cost[i*n+j]);
		}
	
	printf("\nEnter the source node ...");
	scanf("%d",&s);
	s--;
	//#################
	dijks(v,cost,s,n);
	//##################
	
	//printing shortest path lengths....
	printf("\n\nPrinting shortest path lengths ...\n");
	for(i=0;i<n;i++)
		printf("\nDistance of shortest path to % d = %d",i+1,v[i].dist);
	
	return 0;
	
		
}
