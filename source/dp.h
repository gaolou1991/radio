<<<<<<< HEAD
//
//雷达信号仿真
//eagle-2017-4-9
//
#ifndef _DP_H
#define _DP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "dplib.h"

struct cfarInf {
	double alphe;
	int numPro, numRef;
	double door;
};

//LMF信号的获取
double *lmf(int len);
double *gihpc(int len);
double *grhpc(int len);

//DDC
int ddc(double *y,int ylen,double *yi,double *yq);

//PC
void pc(double *ihpc,double *rhpc,int hlen,double *yi,double *yq,int ylen);

//数据重排
void rerange(double *yi,double *yq,double **ryi,double **ryq,int row,int col);

//MTI和MTD
void mti(double **ryi,double **ryq,int row,int col);
void mtd(double **ryi,double **ryq,int row,int col);

//CFAR
char *cfar(struct cfarInf *cf,double *ymtd,int ylen);

#ifdef __cplusplus
}
#endif

#endif
=======
//
//雷达信号仿真
//eagle-2017-4-9
//
#ifndef _DP_H
#define _DP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "dplib.h"

struct cfarInf {
	double alphe;
	int numPro, numRef;
	double door;
};

//LMF信号的获取
double *lmf(int len);
double *gihpc(int len);
double *grhpc(int len);

//DDC
int ddc(double *y,int ylen,double *yi,double *yq);

//PC
void pc(double *ihpc,double *rhpc,int hlen,double *yi,double *yq,int ylen);

//数据重排
void rerange(double *yi,double *yq,double **ryi,double **ryq,int row,int col);

//MTI和MTD
void mti(double **ryi,double **ryq,int row,int col);
void mtd(double **ryi,double **ryq,int row,int col);

//CFAR
char *cfar(struct cfarInf *cf,double *ymtd,int ylen);

#ifdef __cplusplus
}
#endif

#endif
>>>>>>> origin/master
