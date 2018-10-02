#include<stdio.h>
#include<stdlib.h>
//adding two matrices of dimension
int** sumofmatrices(int n,int **a,int **b)
{
	int **c = (int**)malloc(n*sizeof(int*));
	int i,j;
	for(i=0;i<n;i++)
	{
		c[i]=(int*)malloc(n*sizeof(int));
	}
	for(i=1;i<n;i++)
		for(j=1;j<n;j++)
			c[i][j] = a[i][j] + b[i][j];
	return c;
}
int	**SquareMatrixMultiplications(int n,int a[][n], int b[][n])
{
	int p,q,r,s,t,u,v;
	int **c=(int**)malloc(n*sizeof(int*));
	int i,an = n;
	for(i=0;i<n;i++){
		c[i]=(int*)malloc(n*sizeof(int));
	}
	if(n == 3)
	{
		p = (a[1][1] + a[2][2]) * (b[1][1] + b[2][2]);
		q = b[1][1] * (a[2][1] + a[2][2]);
		r = a[1][1] * (b[1][2] - b[2][2]);
		s = a[2][2] * (b[2][1]-b[1][1]);
		t = b[2][2] * (a[1][1] + a[1][2]);
		u = (a[2][1] - a[1][1]) * (b[1][1] + b[1][2]);
		v = (a[1][2] - a[2][2]) * (b[2][2] + b[2][1]);

		c[1][1] = p + s - t + v;
		c[1][2] = r + t;
		c[2][1] = q + s;
		c[2][2] = p + r - q + u;
	}
	//partition A,B and C 
	else
	{
		int i,j,k,l,temp = n/2 + 1;
		int a11[temp][temp],a12[temp][temp],a21[temp][temp],a22[temp][temp],b11[temp][temp],b12[temp][temp],b21[temp][temp],b22[temp][temp];
		int c11[temp][temp],c12[temp][temp],c21[temp][temp],c22[temp][temp];
		temp -= 1;
		for(i=1;i<=temp;i++)
		{
			for(j=1;j<=temp;j++)
			{
				a11[i][j] = a[i][j];
				b11[i][j] = b[i][j];
			}
			for(j=temp+1,k=1;j<n;j++,k++)
			{
				a12[i][k] = a[i][j];
				b12[i][k] = b[i][j];
			}
		}
		for(i=temp+1,k=1;i<n;i++,k++)
		{
			for(j=1;j<=temp;j++)
			{
				a21[k][j] = a[i][j];
				b21[k][j] = b[i][j];
			}
			for(j=temp+1,l=1;j<n;j++,l++)
			{
				a22[k][l] = a[i][j];
				b22[k][l] = b[i][j];
			}
		}
		temp += 1;
		int **s11 = sumofmatrices(temp,SquareMatrixMultiplications(temp,a11,b11),SquareMatrixMultiplications(temp,a12,b21));
		int **s12 = sumofmatrices(temp,SquareMatrixMultiplications(temp,a11,b12),SquareMatrixMultiplications(temp,a12,b22));
		int **s21 = sumofmatrices(temp,SquareMatrixMultiplications(temp,a21,b11),SquareMatrixMultiplications(temp,a22,b21));
		int **s22 = sumofmatrices(temp,SquareMatrixMultiplications(temp,a21,b12),SquareMatrixMultiplications(temp,a22,b22));
		temp -= 1;
		for(i=1;i<=temp;i++)
		{
			for(j=1;j<=temp;j++)
				c[i][j] = s11[i][j];
			for(j=temp+1,k=1;j<n;j++,k++)
				c[i][j] = s12[i][k];
		}
		for(i=temp+1,k=1;i<n;i++,k++)
		{
			for(j=1;j<=temp;j++)
				c[i][j] = s21[k][j];
			for(j=temp+1,l=1;j<n;j++,l++)
				c[i][j] = s22[k][l];
		}
	}
	return c;
}


int main()
{
	int i,j,n;
	printf("enter the dimension of matrices  :");
	scanf("%d",&n);
	int a[n+1][n+1],b[n+1][n+1];
	printf("enter the elements of array A[%d][%d] \n",n,n);
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			scanf("%d",&a[i][j]);
	printf("enter the elements of array B[%d][%d] \n",n,n);
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			scanf("%d",&b[i][j]);
	printf("\n");
	int **p = SquareMatrixMultiplications(n+1,a,b);
	printf("elements of A[%d][%d] * B[%d][%d]\n",n,n,n,n);
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
			printf("%d ",p[i][j]);
		printf("\n");
	}
	return 0;
}