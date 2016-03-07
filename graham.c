#include<stdio.h>
#include<malloc.h>
#define PI 3.14
#define N 25
struct node{
	int x,y;
	float ang;
	struct node * next,*prev;
};

void adjust(struct node *a,int i,int n)
{
	struct node item;
	int j;
	j=2*i;
	item=a[i];
	
	while(j<=n)
	{
		if((j<n) && (a[j].ang<a[j+1].ang))
			j++;
		if(item.ang>=a[j].ang)
			break;
		a[j/2]=a[j];
		j=2*j;
	}
	a[j/2]=item;
}

void heapify(struct node *a,int n)
{
	int i;
	for(i=n/2;i>=1;i--)
		adjust(a,i,n);
	
}

void heapsort(struct node *a,int n)
{
	int i;
	struct node temp;
		
	heapify(a,n);
	
	for(i=n;i>=2;i--)
	{
		temp=a[i];
		a[i]=a[1];
		a[1]=temp;
		adjust(a,1,i-1);
	}
}


float ar(int x1,int y1,int x2,int y2,int x3,int y3)
{
	return (x1*(y2-y3)+x2*(y3-y1)+x3*(y1-y2));
}

void scan(struct node * list)
{
	struct node * p,*p1,*p2,*p3;
	p=list;
	p1=list;
	while(1)
	{
		
		p2=p1->next;
		if(p2->next!=NULL)
			p3=p2->next;
		else
			return;
		if(ar(p1->x,p1->y,p2->x,p2->y,p3->x,p3->y)>=0.0)
			p1=p1->next;
		else
		{
			p1->next=p3;
			p3->prev=p1;
			p1=p1->prev;
		}
	
	}
}

void printList(struct node * list)
{
	int i;
	struct node *p;
	p=list;
	i=0;
	do
	{
		i++;
		printf("\n[%d] X=%d\tY=%d",i,p->x,p->y);
		p=p->next;
	}while(p!=NULL);
}

//l is the pointer to thebase of the  ARRAY of points
void setGraham(struct node * l,int n)
{
	 int i;
	 int j;
	 int x,y;
	 x=l[1].x;
	 y=l[1].y;
	 j=1;
	 for(i=2;i<=n;i++)
	 {
		if((y>l[i].y) || (y==l[i].y && x>l[i].x))
		{
			j=i;
			y=l[i].y;
			x=l[i].x;
		}
	}
	//j has index of p
	l[0].x=x;
	l[0].y=y;
	
	// p has been moved to 0 position
	for(i=j;i<n;i++)
	{
		l[i]=l[i+1];
	}
	// other points after p are moved one position ahead
	
	//now the array's "ang" fileds are filled
	for(i=1;i<n;i++)
	{
		l[i].ang=atan(((float)y-l[i].y)/((float)x-l[i].x));
		if(l[i].ang<0.0)
			l[i].ang+=PI;
		
	}
	// PI was added to make change the range of atan to 0 to PI

	// the array is sorted using heapsort
	heapsort(l,n-1);
	
	for(i=1;i<n;i++)
	{
		l[i].next=&l[i+1];
		l[i].prev=&l[i-1];
	}
	
	l[0].next=&l[1];
	l[0].prev=NULL;
	l[n-1].next=NULL;
}


int main()
{
	struct node lis[N];
	int i,n;
	
	printf("\nEnter the number of points ....");
	scanf("%d",&n);
	
	for(i=1;i<=n;i++)
	{
		printf("\n%d X=",i);
		scanf("%d",&(lis[i].x));
		printf("\n%d Y=",i);
		scanf("%d",&(lis[i].y));
	}
	//setting the list for scan
	setGraham(lis,n);
	//scanning
	scan(lis);
	//printing
	printf("\nPoints in the convex hull are ...");
	printList(lis);

	printf("\nProgrammed by:Sushmit Kumar\n!\tHappy Programming to all\t!");
	return 0;
}
