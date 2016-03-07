#include<stdio.h>
#include<malloc.h>


struct node
{
	struct node * next;
	struct node * par;
	int g;
	int cost;
	int state[17];

};
int CCost(struct node * n)
{
	int i,c=0;
	for(i=1;i<16;i++)
		if((n->state[i])!=i)
			c++;

	return (c + n->g);

}

// returns 1 for same state, 0 for diff

int match(struct node * n1,struct node * n2)
{

 int i;
 if(n1==NULL || n2==NULL)
    return 0;
 for(i=1;i<16;i++)
	if((n1->state[i])!=(n2->state[i]))
		return 0;

 return 1;
}

int blankPos(struct node * n)
{
 int i;
 for(i=1;i<16;i++)
	if((n->state[i])==16)
		return i;

 return 16;
}


struct node * copyNode(struct node * n)
{

	 int i;
	 struct node * m;
	 m=(struct node *)malloc(sizeof(struct node));

	 m->next=n->next;
	 m->par=n->par;
	 m->g=n->g;
	 m->cost=n->cost;

	 for(i=1;i<17;i++)
		m->state[i]=n->state[i];

	 return m;
}

struct node * topChild(struct node *n)
{
	int bp;
	struct node *tc;

	bp=blankPos(n);

	if(bp<=4)
		return NULL;
	tc=copyNode(n);
	
	tc->state[bp]=tc->state[bp-4];
	tc->state[bp-4]=16;
	tc->par=n;
	if(!match(tc,n->par))
		return tc;
	else
		return NULL;
}

struct node * botChild(struct node * n)
{
	int bp;
	struct node *tc;

	bp=blankPos(n);

	if(bp>12)
		return NULL;
	tc=copyNode(n);
	tc->state[bp]=tc->state[bp+4];
	tc->state[bp+4]=16;
	tc->par=n;
	if(!match(tc,n->par))
		return tc;
	else
		return NULL;
}
struct node * rigChild(struct node * n)
{
	int bp;
	struct node *tc;

	bp=blankPos(n);

	if(!(bp%4))
		return NULL;
	tc=copyNode(n);
	tc->state[bp]=tc->state[bp+1];
	tc->state[bp+1]=16;
	tc->par=n;
	if(!match(tc,n->par))
		return tc;
	else
		return NULL;
}

struct node * lefChild(struct node * n)
{
	int bp;
	struct node *tc;

	bp=blankPos(n);

	if(!((bp-1)%4))
		return NULL;
	tc=copyNode(n);
	tc->state[bp]=tc->state[bp-1];
	tc->state[bp-1]=16;
	tc->par=n;

		if(!match(tc,n->par))
		return tc;
	else
		return NULL;
}

//addList adds cn to the set of active nodes
//n=starting node in active nodes list
//cn=node to be added
void addList(struct node **n,struct node *cn)
{
	struct node *ptr;
	if(*n==NULL)
	{
  
		*n=cn;
		cn->next=NULL;
		return;
	}
	ptr=*n;
	while(ptr->next!=NULL)
		ptr=ptr->next;

	ptr->next=cn;
	cn->next=NULL;


}


//least : finds least node from active list ,
//        returns it, and deletes it from the list
//        but does not frees memory

struct node * least(struct node ** n)
{
 int c;
 struct node * ptr,* par, * cur;

 ptr=*n;
 c=ptr->cost;
 while(ptr->next!=NULL)
 {
    ptr=ptr->next;
	if(c>ptr->cost)
		c=ptr->cost;
 }
 ptr=*n;
 par=NULL;
 cur=ptr;
 while(ptr->next!=NULL)
 {
	par=ptr;
	ptr=ptr->next;
	cur=ptr;
	if(c==ptr->cost)
		break;
 }
 
 if(par==NULL)
 {
	*n=cur->next;
	return cur;
 }
 else
 {
	par->next=cur->next;
	return cur;
 }


}

int chkAns(struct node * n)
{
  int i,c=0;
	for(i=1;i<16;i++)
		if((n->state[i])!=i)
		{
			c++;

			break;
		}
	if(c)
		return 0;
	else
		return 1;
}

void printN(struct node *n)
{
	int i;
	printf("\n");
	for(i=1;i<17;i++)
	{
		if((i%4)==1)
			printf("\n");

		if((n->state[i])==16)
			printf(" \t");
		else
			printf("%d\t",n->state[i]);

	}
	printf("\n");
}
void printAll(struct node *n)
{
	struct node * ptr;
	if(n==NULL)
		return;

	ptr=n;
	printf("\nPrinting Solution (in reverse order) ...\n\n");
	while(ptr!=NULL)
	{
		printN(ptr);
		ptr=ptr->par;
	}


}

void LCsearch(struct node * t)
{
  struct node *E;
  struct node *AN;
  struct node *ch[4];
  int i;

  if(chkAns(t))
  {
 		printN(t);
		return;
  }

  E=t;
  AN=NULL;

  while(1)
  {
	for(i=0;i<4;i++)
		ch[i]=NULL;
	ch[0]=topChild(E);
	ch[2]=botChild(E);
	ch[1]=rigChild(E);
	ch[3]=lefChild(E);
	
	for(i=0;i<4;i++)
	{
       
		if((ch[i])!=NULL)
		{ 
			if(chkAns(ch[i]))
			{
				printAll(ch[i]);
				return;
			}
			 
			addList(&AN,ch[i]);
			 
			(ch[i])->par=E;
			(ch[i])->next=NULL;
			(ch[i])->g=((ch[i])->par)->g + 1;
			(ch[i])->cost=CCost(ch[i]);
		}
	}
	
	if(AN==NULL)
	{
		printf("\nNo Answer Node !\n");
		return;
	}
	E=least(&AN);


  }

}

int main()
{
	struct node *t;
	int ii,i,j;
	t=(struct node *)malloc(sizeof(struct node));
	ii=0;
	printf("\nEnter the 15 puzzle ...\n[Enter 16 for blank spot]\n\n");
	for(i=1;i<=4;i++)
		for(j=1;j<=4;j++)
		{
			printf("\nEnter value for position (%d,%d)...",i,j);
			ii++;
			scanf("%d",&(t->state[ii]));
		}
	t->next=NULL;
	t->par=NULL;
	t->g=0;
	t->cost=CCost(t);
	LCsearch(t);
	printf("\nProgrammed by:Sushmit Kumar\n!\tHappy rogramming to all\t!\n");
    getch();
    return 0;

}

