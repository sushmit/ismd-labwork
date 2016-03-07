#include<stdio.h>
#include<malloc.h>

struct edge
{
		int i;
		int j;
		unsigned int cost;
};

void adjust(struct edge * a,int i,int n)
{
	struct edge item;
	int j;
	j=2*i;
	item=a[i];
	while(j<=n)
	{
		if((j<n) && (a[j].cost<a[j+1].cost))
			j++;
		if(item.cost>=a[j].cost)
			break;
		a[j/2]=a[j];
		j=2*j;
	
	}
	a[j/2]=item;
}

void heapify(struct edge * a,int n)
{
	int i;
	for(i=n/2;i>=1;i--)
		adjust(a,i,n);
}

void heapsort(struct edge * a,int n)
{
	
	int i;
	struct edge t;
	//printf("%d",n);
	heapify(a,n);
	
	for(i=n;i>=2;i--)
	{
		t=a[i];
		a[i]=a[1];
		a[1]=t;
		adjust(a,1,i-1);
	}
}



void Union(int * p,int i,int j)
{
	
	p[i]=j;
}

int find(int *p,int i)
{
	while(p[i]>=0)
		i=p[i];
	
	return i;
}

int main()
{
	int n,i,j,k,u,v,mincost=0;
	int *t,*p;
	struct edge *e;
	
	printf("\nEnter number of nodes ...\n");
	scanf("%d",&n);
	//allocating memory ....
	
	t=(int *)malloc(sizeof(int)*2*(n-1));					//for tree
	e=(struct edge *)malloc(sizeof(struct edge)*((n*(n-1))/2+1));	//for sorting edges
	p=(int *)malloc(sizeof(int)*(n+1));						//for forest
	
	
	
	printf("\nEnter the graph in the form of costs of edges ...\n");
	printf("Enter -1 for non existent edges.\n\n");
	
	//filling the e[] array
	for(i=0,k=0;i<n;i++)
		for(j=i+1;j<n;j++)
		{	
				k++;
				//printf("%d",k);
				e[k].i=i+1;
				e[k].j=j+1;
				printf("Enter cost of edge (%d,%d) ...",i+1,j+1);
				scanf("%u",&(e[k].cost));
			
		}
		
	//initializing p
	for(i=1;i<n+1;i++)
		p[i]=-1;
	
	//sorting edges....
	heapsort(e,((n*(n-1))/2));
	
	i=0;
	j=0;
	
	while((i<n-1) && (j<((n*(n-1))/2)))
	{
		j++;
		u=find(p,e[j].i);
		v=find(p,e[j].j);
		//printf("\nu=%d\nv=%d",u,v);
		
		if(u!=v)
		{	
			t[i*n]=e[j].i;
			t[i*n+1]=e[j].j;
			mincost+=e[j].cost;
			Union(p,u,v);
			//printf("\nHello");
			i++;
			
		}
		//printf("%d",j);
	}
	
	if(i!=n-1)
		printf("\nNo Spanning Tree !");
	else
		printf("\nMincost = %d",mincost);
	
	return 0;
	
	
	
}
