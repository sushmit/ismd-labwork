#include<stdio.h>
#include<string.h>
#include<malloc.h>

//lcsLen

char * lcsLen(char * x,char * y)
{
  int m,n,i,j,*c;
  char *b;
  
  m=strlen(x);
  n=strlen(y);
  
  c=(int *)malloc(sizeof(int)*(n+1)*(m+1));
  b=(char *)malloc(sizeof(int)*(n*m+1));
  
  for(i=1;i<m+1;i++)
    c[i*(n+1)]=0;
  for(i=0;i<n+1;i++)
    c[i]=0;
  for(i=1;i<m+1;i++)
    for(j=1;j<n+1;j++)
	{
   	if(x[i-1]==y[j-1])
	  {
	    c[i*(n+1)+j]=c[(i-1)*(n+1)+j-1]+1;
	    b[(i-1)*n+j]='d';
	  }
	else if(c[(i-1)*(n+1)+j]>=c[i*(n+1)+j-1])
	  {
	    c[i*(n+1)+j]=c[(i-1)*(n+1)+j];
	    b[(i-1)*n+j]='u';
	   }
	else
	  {
	    c[i*(n+1)+j]=c[i*(n+1)+j-1];
	    b[(i-1)*n+j]='l';
	    }
	  }


    return b; 

}


void printLcs(char *b,char *x,int i,int j,int m,int n)
{
    
    if(i==0 || j==0)
      return;
    if(b[(i-1)*n+j]=='d')
      {
	printLcs(b,x,i-1,j-1,m,n);
	printf("\t%c",x[i-1]);
      }
    else if(b[(i-1)*n+j]=='u')
 	printLcs(b,x,i-1,j,m,n);
    else
	printLcs(b,x,i,j-1,m,n);

}


int main()
{
  char *x,*y,*b;
  int n,i,j;
  
  printf("\nEnter length of first sequence ...");
  scanf("%d",&n);
  
  x=(char *)malloc(sizeof(char)*(n+1));
  
  printf("\nEnter length of second sequence ...");
  scanf("%d",&n);
  
  y=(char *)malloc(sizeof(char)*(n+1));
  
  printf("\nEnter first sequence ...\n");
  scanf("%s",x);
  
  printf("\nEnter second sequence ...\n");
  scanf("%s",y);

  //calling lcsLen
  b=lcsLen(x,y);
  //calling printLcs
  printf("\nPrinting longest common sub-sequence ...\n\n");   
  printLcs(b,x,strlen(x),strlen(y),strlen(x),strlen(y));
  printf("\n\nProgrammed by: Sushmit Kumar \n\nHappy Programming to all !\n");
  
  return 0;



}