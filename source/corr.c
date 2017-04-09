<<<<<<< HEAD
//
//相关
//esgle-2017-4-7
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dplib.h"

//#define debug_main

//input: 
//a,b: 数据数据 h x
//na,nb: 数据长度
//r: 计算结果
//output: 数据长度
int corr(double *h,int nh,double *x,int nx,double *r)
{
	int len = nh+nx-1;

	int n,m;
	for( n = 0; n<len; n++)
	{
		r[n] = 0;
		for( m = (n-nh+1<0?0:n-nh+1); m<=(n<nx-1?n:nx-1); m++) r[n] += h[n-m]*x[nx-1-m];
	}

	return len;
}


#ifdef debug_main
int main(void)
{
	int a[4] = {0,1,2,3};
	int b[12] = {0,2,0,0,1,2,3,0,3,2,1,0};
	int r[20];

	int len = corr(a,4,b,12,r);
	
	for(int n=0; n<len; n++)
	{
		printf("%d ",r[n]);
	}
	//0 0 1 4 10 12 12 8 14 8 3 2 4 6 0
}
=======
//
//相关
//esgle-2017-4-7
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dplib.h"

//#define debug_main

//input: 
//a,b: 数据数据 h x
//na,nb: 数据长度
//r: 计算结果
//output: 数据长度
int corr(double *h,int nh,double *x,int nx,double *r)
{
	int len = nh+nx-1;

	int n,m;
	for( n = 0; n<len; n++)
	{
		r[n] = 0;
		for( m = (n-nh+1<0?0:n-nh+1); m<=(n<nx-1?n:nx-1); m++) r[n] += h[n-m]*x[nx-1-m];
	}

	return len;
}


#ifdef debug_main
int main(void)
{
	int a[4] = {0,1,2,3};
	int b[12] = {0,2,0,0,1,2,3,0,3,2,1,0};
	int r[20];

	int len = corr(a,4,b,12,r);
	
	for(int n=0; n<len; n++)
	{
		printf("%d ",r[n]);
	}
	//0 0 1 4 10 12 12 8 14 8 3 2 4 6 0
}
>>>>>>> origin/master
#endif