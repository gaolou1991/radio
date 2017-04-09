<<<<<<< HEAD
//
//数据处理 头文件
//eagle-2017-4-9
//
#ifndef _DPLIB_H
#define _DPLIB_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int conv(int *h,int nh,int *x,int nx,int *r);
int corr(int *h,int nh,int *x,int nx,int *r);
void fft(double *rex, double *imx, int n);

#ifdef __cplusplus
}
#endif

#endif
=======
//
//数据处理 头文件
//eagle-2017-4-9
//
#ifndef _DPLIB_H
#define _DPLIB_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int conv(int *h,int nh,int *x,int nx,int *r);
int corr(int *h,int nh,int *x,int nx,int *r);
void fft(double *rex, double *imx, int n);

#ifdef __cplusplus
}
#endif

#endif
>>>>>>> origin/master
