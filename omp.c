#include<stdio.h>
#include<malloc.h>

struct node
{
	struct node * right;
	struct node * left;
	int weight;
};

struct list
{
	struct node * item;
	struct list * next;
};

struct node * least(struct list ** l)
{
	
	struct node * t;
	struct list * ptr,*bp,*p,*lptr;
	if(*l==NULL)
		return NULL;
	ptr=*l;
	p=*l;
	bp=NULL;
	lptr=NULL;
	do
	{
		if(((ptr->item)->weight)<((p->item)->weight))
		{
			bp=lptr;;
			p=ptr;
		}
		lptr=ptr;
		ptr=ptr->next;	
	}while(ptr!=NULL);
	if(bp!=NULL)
		bp->next=p->next;
	else
		*l=p->next;
		
	t=p->item;
	free(p);
	return t;
}

void insert(struct list ** l,struct node * p)
{
	struct list *n;
	n=(struct list *)malloc(sizeof(struct list));
	
	n->item=p;
	if(*l!=NULL)
		n->next=*l;
	else
		n->next=NULL;
	
	*l=n;
	
	return ;
}

struct node * tree(struct list **l,int n)
{
	struct node *pt;
	int i;
	for(i=1;i<n;i++)
	{
		pt=(struct node *)malloc(sizeof(struct node));
		pt->left=least(l);
		pt->right=least(l);
		pt->weight=(pt->left)->weight + (pt->right)->weight;
		insert(l,pt);
	}
	
	return least(l);
}

void inOrder(struct node * root)
{
	if(root->left!=NULL)
		inOrder(root->left);
	printf("%d\t",root->weight);
	if(root->right!=NULL)
		inOrder(root->right);
	
}

int main()
{
	int i,n;
	struct list *l,*lptr;
	struct node * tr;
	
	printf("\nEnter number of files ...");
	scanf("%d",&n);
	l=NULL;
	
	for(i=1;i<=n;i++)
	{
		lptr=(struct list *)malloc(sizeof(struct list));
		tr=(struct node *)malloc(sizeof(struct node));
		
		printf("\n%d. Enter length ..",i);
		scanf("%d",&(tr->weight));
		
		tr->left=NULL;
		tr->right=NULL;
		
		lptr->item=tr;
		if(l==NULL)
			lptr->next=NULL;
		else
			lptr->next=l;
		l=lptr;
		
	}	

	//calling tree
	tr=tree(&l,n);
	
	//printing result
	printf("\nPrinting tree in order ....\n\n");
	inOrder(tr);
	
	return 0;
}
