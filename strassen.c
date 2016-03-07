#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int findorder(int i1,int j1,int i2,int j2);
float * matrixmul(float * mat1,float * mat2,int order);
float * matrixadd(float *mat1,float *mat2,int neworder);
float * matrixsub(float *mat1,float *mat2,int neworder);

int main()
{
	int i[2],j[2],order,k,l,m;
	float *mat1,*mat2,*temp;
	printf("strassen matrix multiplication\n");
	printf("enter the dimenstions of the first matrix\n");
	printf("r:- ");
	scanf("%d",&i[0]);
	printf("c:- ");
	scanf("%d",&j[0]);
	printf("enter the dimenstions of the second matrix\n");
	printf("r:- ");
	scanf("%d",&i[1]);
	if(j[0]!=i[1])
	{
		printf("matrix can't be multiplied\n");
		return 1;
	}
	printf("c:- ");
	scanf("%d",&j[1]);
	printf("%d  %d  %d  %d\n",i[0],j[0],i[1],j[1]);
	order=findorder(i[0],j[0],i[1],j[1]);
	printf("main--order %d\n",order);
	mat1=(float *)malloc(sizeof(float)*order*order);
	//memset();
	mat2=(float *)malloc(sizeof(float)*order*order);
	for(k=0;k<2;k++)
	{
		if(k==0)
			temp=mat1;
		else
			temp=mat2;
		printf("enter the values of matrix no %d :--\n",k);
		for(l=0;l<i[k];l++)
		{
			for(m=0;m<j[k];m++)
			{
				printf("a[%d][%d]:--",l,m);
				scanf("%f",temp);
				temp++;
			}
			temp=temp+(order-j[k]);
		}
	}
	temp=matrixmul(mat1,mat2,order);
	printf("\n\n\n\n");
	//temp=mat1;
	for(l=0;l<i[0];l++)
	{
		for(m=0;m<j[1];m++)
		{
			printf("%8.3f  ",*temp);
			//scanf("%f",temp);
			temp++;
		}
		temp=temp+(order-j[1]);
		printf("\n");
	}
	printf("\n\n\n\n");
	return 0;	
}

float * matrixmul(float * mat1,float * mat2,int order)
{
	printf("i am in matrix mul ****************** %d\n",order);
	int i,j,neworder,k,l,m;
	float * mat[8],*temp,*newtemp,*p,*q,*r,*s,*t,*u,*v,*add1,*add2,*c[4],* retmat;
	neworder=order/2;
	if(order==2)
	{
		printf("in order of 2\n");
		retmat=(float *)malloc(sizeof(float)*order*order);
		*retmat=((*mat1)*(*mat2))+((*(mat1+1))*(*(mat2+2)));
		*(retmat+1)=((*mat1)*(*(mat2+1)))+((*(mat1+1))*(*(mat2+3)));
		*(retmat+2)=(((*(mat1+2))*(*(mat2+0)))+((*(mat1+3))*(*(mat2+2))));
		*(retmat+3)=(((*(mat1+2))*(*(mat2+1)))+((*(mat1+3))*(*(mat2+3))));
		printf("mat1 : %f %f %f %f\n",*mat1,*(mat1+1),*(mat1+2),*(mat1+3));
		printf("mat2 : %f %f %f %f\n",*mat2,*(mat2+1),*(mat2+2),*(mat2+3));
		printf("retmat : %f %f %f %f\n",*retmat,*(retmat+1),*(retmat+2),*(retmat+3));
		return retmat;
	}
	printf("in order of %d\n",order);
	for(i=0;i<8;i++)
	{
		mat[i]=(float *)malloc(sizeof(float)*neworder*neworder);
	}
	
	i=0;
	/////////////////////////
	for(k=0;k<2;k++)
	{
		for(j=0;j<4;j++)
		{
			if(k==0)
				temp=mat1;
			else
				temp=mat2;
			newtemp=mat[i];
			switch (j)
			{
				case 0:
					printf("in case 1\n");
					temp=temp;
					break;
				case 1:
					printf("in case 2\n");
					temp=temp+(neworder*1);
					break;
				case 2:
					printf("in case 3\n");
					temp=temp+(neworder*4);
					break;
				case 3:
					printf("in case 4\n");
					temp=temp+(neworder*5);
					break;
			}
			for(l=0;l<neworder;l++)
			{
				for(m=0;m<neworder;m++)
				{
					*newtemp=*temp;
					printf("k=%d j=%d l=%d i=%d transfered:  %f\n",k,j,l,i,*newtemp);
					newtemp++;
					temp++;
				}
				printf("\n");
				temp=temp+neworder;
			}
			i++;		
		}
	}
	/////////////////////
	add1=matrixadd(mat[0],mat[3],neworder);
	add2=matrixadd(mat[4],mat[7],neworder);
	p=matrixmul(add1,add2,neworder);

	add1=matrixadd(mat[2],mat[3],neworder);// add1=matrixadd(mat[],mat[],neworder);
	q=matrixmul(add1,mat[4],neworder);

	add1=matrixsub(mat[5],mat[7],neworder);
	r=matrixmul(mat[0],add1,neworder);

	add1=matrixsub(mat[6],mat[4],neworder);
	s=matrixmul(mat[3],add1,neworder);

	add1=matrixadd(mat[0],mat[1],neworder);
	t=matrixmul(add1,mat[7],neworder);
	
	add1=matrixsub(mat[2],mat[0],neworder);
	add2=matrixadd(mat[4],mat[5],neworder);
	u=matrixmul(add1,add2,neworder);

	add1=matrixsub(mat[1],mat[3],neworder);
	add2=matrixadd(mat[6],mat[7],neworder);
	printf("returned address is = %p %p\n ",add1,add2);
	v=matrixmul(add1,add2,neworder);
	
	add1=matrixadd(p,s,neworder);
	add2=matrixsub(v,t,neworder);
	c[0]=matrixadd(add1,add2,neworder);
	
	c[1]=matrixadd(r,t,neworder);
	printf("&&&&&&&&&&&&&&&&&&&&&&&&&&7bc1-- %f \n",*c[1]);
	
	c[2]=matrixadd(q,s,neworder);
	printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&bc2-- %f \n",*c[2]);
	
	add1=matrixadd(p,r,neworder);
	add2=matrixsub(u,q,neworder);
	c[3]=matrixadd(add1,add2,neworder);

	retmat=(float *)malloc(sizeof(float)*order*order);
	temp=retmat;
	i=0;
	for(k=0;k<4;k++)
	{
		temp=retmat;
		switch (k)
			{
				case 0:
					temp=temp;
					break;
				case 1:
					temp=temp+(neworder*1);
					break;
				case 2:
					temp=temp+(neworder*4);
					break;
				case 3:
					temp=temp+(neworder*5);
					break;
			}
			newtemp=c[i];
			for(l=0;l<neworder;l++)
			{
				for(m=0;m<neworder;m++)
				{
					*temp=*newtemp;
					printf("newtemp:-- %f\n",*temp);
					newtemp++;
					temp++;
				}
				temp=temp+neworder;
			}
			i++;
	}
	return retmat;
} 

float * matrixadd(float *mat1,float *mat2,int order)
{
	printf("i am in matrixadd +++++++++++++++++++ order -- %d\n",order);
	float * retmat,*temp;
	int i,j;
	retmat=(float *)malloc(sizeof(float)*order*order);
	temp=retmat;
	for(i=0;i<order;i++)
	{
		for(j=0;j<order;j++)
		{
			(*temp)=(*mat1)+(*mat2);
			printf("%f  %f\n",*mat1,*mat2);
			temp++;
			mat1++;
			mat2++;
		}
	}
	printf("retmat : %f %f %f %f\n",*retmat,*(retmat+1),*(retmat+2),*(retmat+3));
	printf("%p\n",retmat);
	return retmat;

}

float * matrixsub(float *mat1,float *mat2,int order)
{
	printf("i am in matrixsub --------------------- order -- %d\n",order);
	float * retmat,*temp;
	int i,j;
	retmat=(float *)malloc(sizeof(float)*order*order);
	temp=retmat;
	for(i=0;i<order;i++)
	{
		for(j=0;j<order;j++)
		{
			(*temp)=(*mat1)-(*mat2);
			printf("%f  %f\n",*mat1,*mat2);
			temp++;
			mat1++;
			mat2++;
		}
	}
	printf("retmat : %f %f %f %f\n",*retmat,*(retmat+1),*(retmat+2),*(retmat+3));
	printf("%p\n",retmat);
	
	return retmat;

}


int findorder(int i1,int j1,int i2,int j2)
{
	//printf("hello i am here \n");
	int temp,power;
	temp=i1;	
	if(j1>temp)
		temp=j1;
	if(j2>temp)
		temp=j2;
	for(power=1;temp>power;power=power*2);
	//printf("%d\n",power);
	return power;
}





