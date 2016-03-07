#include<stdio.h>
#include<malloc.h>

struct job
{
		int p;
		int index;
		int d;
};
// heap sort for preprocessing
void adjust(struct job * a,int i,int n)
{
	struct job item;
	int j;
	j=2*i;
	item=a[i];
	while(j<=n)
	{
		if((j<n) && (a[j].p>a[j+1].p))
			j++;
		if(item.p<=a[j].p)
			break;
		a[j/2]=a[j];
		j=2*j;

	}
	a[j/2]=item;
}

void heapify(struct job * a,int n)
{
	int i;
	for(i=n/2;i>=1;i--)
		adjust(a,i,n);
}

void heapsort(struct job * a,int n)
{
	int i;
	struct job t;
	heapify(a,n);

	for(i=n;i>=2;i--)
	{
		t=a[i];
		a[i]=a[1];
		a[1]=t;
		adjust(a,1,i-1);
	}
}

// function job sequencing

int js(struct job *d,int *j,int n)
{
	int i,k,q,r;

	d[0].d=0;
	j[0]=0;
	j[1]=1;
	k=1;
	for(i=2;i<=n;i++)
	{
		r=k;
		while((d[j[r]].d>d[i].d) && (d[j[r]].d!=r))
			r--;

		if((d[j[r]].d<=d[i].d) && (d[i].d>r))
		{
			for(q=k;q>=r+1;q--)
				j[q+1]=j[q];

			j[r+1]=i;
			k++;
		}
	}
	return k;
}

int main()
{
	struct job *p;
	int *j;
	int i,k,n,np;

	printf("\nEnter number of jobs ...");
	scanf("%d",&n);

	p=(struct job *)malloc(sizeof(struct job)*(n+1));
	//d=(int *)malloc(sizeof(int)*(n+1));
	j=(int *)malloc(sizeof(int)*(n+1));

	printf("\nEnter profits and deadlines of jobs...\n");

	for(i=0;i<n;i++)
	{
		printf("%d. Profit = ",i+1);
		scanf("%d",&(p[i+1].p));

		printf("%d. Deadline = ",i+1);
		scanf("%d",&(p[i+1].d));
		p[i+1].index=i+1;

	}
	 //sorting jobs in non-increasing order
	 heapsort(p,n);

	//calling js
	k=js(p,j,n);

	//summing net profit
	np=0;
	for(i=0;i<k;i++)
		np+=p[j[i+1]].p;

	printf("\n\nPrinting results ...\n");
	
	for(i=0;i<k;i++)
		printf("\nJob %d (profit= %d, deadline= %d) will be done.",p[j[i+1]].index,p[j[i+1]].p,p[j[i+1]].d);

	printf("\n\nMaximum Profit= %d",np);

	return 0;
}
