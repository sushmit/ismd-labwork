#include<stdio.h>
#include<malloc.h>
#include<math.h>

struct tree
{
	int tr,weight,d;
};

void tvs(struct tree * t,int i,int del,int n)
{
	if(t[i].tr)
	{
		if(2*i>n)
			t[i].d=0;
		else
		{
			tvs(t,2*i,del,n);
			t[i].d=(t[i].d > t[2*i].d+t[2*i].weight)?(t[i].d):(t[2*i].d+t[2*i].weight);
			if(2*i+1<=n)
			{
				tvs(t,2*i+1,del,n);
				t[i].d=(t[i].d > t[2*i+1].d+t[2*i+1].weight)?(t[i].d):(t[2*i+1].d+t[2*i+1].weight);
			}
		}
		if((t[i].tr!=1) && (t[i].d+t[i].weight>del))
		{
			printf("\nTree will be split at %d.",t[i].tr);
			t[i].d=0;
		}
	}
}

int main()
{
	struct tree *t;
	int m,n,i,del;
	
	
	printf("\nEnter height of tree ....");
	scanf("%d",&m);
	
	n=pow(2,m)-1;
	
	t=(struct tree *)malloc(sizeof(struct tree)*(n+1));
	
	printf("\nEnter tree ...");
	for(i=1;i<n+1;i++)
	{
		t[i].d=0;
		printf("\n%d.Enter node number (0 for non existent node)...",i);
		scanf("%d",&(t[i].tr));
		if(t[i].tr)
		{
			printf("\n%d.Enter weight of incoming edge ...",i);
			scanf("%d",&(t[i].weight));
		}
		else
			t[i].weight=0;
	}
	
	printf("\nEnter maximum delay allowed ...");
	scanf("%d",&del);
	
	//calling tvs
	tvs(t,1,del,n);
	
	return 0;
	
		
}
