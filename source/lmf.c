<<<<<<< HEAD
//
//产生LMF信号
//eagle-2017-4-9
//
#include <stdio.h>

#include "dp.h"
#include "dplib.h"

double *lmf(int *len)
{
	//读取LMF回波文件
	FILE *fp;
	
	fp = fopen("glmf.in","r");
	if(fp == NULL){
		perror("open file glme.in failed\n");
		return NULL;
	}
	
	fscanf(fp,"%d",len);
	double *dlmf = (double*)malloc(sizeof(double)*(*len));
	for(int i=0; i<*len; i++){
		fscanf(fp,"%lf",&dlmf[i]);
	}
	
	fclose(fp);
	
	return dlmf;
}

double *grhpc(int *len)
{
	//读取脉冲压缩滤波器信息
	FILE *fp;
	
	fp = fopen("rhpc.in","r");
	if(fp == NULL){
		perror("open file rhpc.in failed\n");
		return NULL;
	}
	
	fscanf(fp,"%d",len);
	double *rhpc = (double*)malloc(sizeof(double)*(*len));

	for(int i=0; i<*len; i++) {
		fscanf(fp,"%lf",&rhpc[i]);
	}

	fclose(fp);
	
	return rhpc;
}

double *gihpc(int *len)
{
	//读取脉冲压缩滤波器信息
	FILE *fp;
	
	fp = fopen("ihpc.in","r");
	if(fp == NULL){
		perror("open file ihpc.in failed\n");
		return NULL;
	}
	
	fscanf(fp,"%d",len);
	double *ihpc = (double*)malloc(sizeof(double)*(*len));

	for(int i=0; i<*len; i++) {
		fscanf(fp,"%lf",&ihpc[i]);
	}

	fclose(fp);
	
	return  ihpc;
}

int ddc(double *y,int ylen,double *yi,double *yq)
{
	//读取NCO的LPF系数
	FILE *fp;
	fp = fopen("hnco.in","r");
	
	int len;
	fscanf(fp,"%d",&len);
	
	double *hnco = (double*)malloc(sizeof(double)*len);
	for(int i=0; i<len; i++){
		fscanf(fp,"%lf",&hnco[i]);
	}
	
	fclose(fp);
	
	//抽取和滤波
	double *hnco0 = (double*)malloc(sizeof(double)*len/4);
	double *hnco2 = (double*)malloc(sizeof(double)*len/4);
	double *y0 = (double*)malloc(sizeof(double)*ylen/4);
	double *y2 = (double*)malloc(sizeof(double)*ylen/4);
	double *ynco0 = (double*)malloc(sizeof(double)*((len+ylen)/4-1));
	double *ynco2 = (double*)malloc(sizeof(double)*((len+ylen)/4-1));
	double *yncoi = (double*)malloc(sizeof(double)*((len+ylen)/4-1));
	double *yncoq = (double*)malloc(sizeof(double)*((len+ylen)/4-1));
	
	//对输入信号进行抽取 nco i路
	for(int i=0; i<ylen/4; i++){
		y0[i] = y[3+4*i];
		y2[i] = y[1+4*i];
	}
	for(int i=0; i<len/4; i++){
		hnco0[i] = hnco[0+4*i];
		hnco2[i] = hnco[2+4*i];
	}
	
	conv(hnco0,len/4,y0,ylen/4,ynco0);
	conv(hnco2,len/4,y2,ylen/4,ynco2);
	
	for(int i=0; i<(len+ylen)/4-1; i++){
		yncoi[i] = ynco0[i] - ynco2[i];
	}
	memcpy(yi,&yncoi[7],sizeof(double)*ylen/4);
	
	//对输入信号进行抽取 nco q路
	for(int i=0; i<ylen/4; i++){
		y0[i] = y[2+4*i];
		y2[i] = y[0+4*i];
	}
	for(int i=0; i<len/4; i++){
		hnco0[i] = hnco[1+4*i];
		hnco2[i] = hnco[3+4*i];
	}
	
	conv(hnco0,len/4,y0,ylen/4,ynco0);
	conv(hnco2,len/4,y2,ylen/4,ynco2);
	
	for(int i=0; i<(len+ylen)/4-1; i++){
		yncoq[i] = ynco2[i] - ynco0[i];
	}
	memcpy(yq,&yncoq[7],sizeof(double)*ylen/4);
	
	free(hnco);
	free(hnco0);
	free(hnco2);
	free(ynco0);
	free(ynco2);
	free(yncoi);
	free(yncoq);
	
	return ylen/4;
}

void pc(double *ihpc,double *rhpc,int hlen,double *yi,double *yq,int ylen)
{
	double *ihpcd = (double*)malloc(sizeof(double)*hlen/4);
	double *rhpcd = (double*)malloc(sizeof(double)*hlen/4);
	double *ypc0 = (double*)malloc(sizeof(double)*(ylen+hlen/4-1));
	double *ypc2 = (double*)malloc(sizeof(double)*(ylen+hlen/4-1));
	double *ypct0 = (double*)malloc(sizeof(double)*(ylen+hlen/4-1));
	double *ypct2 = (double*)malloc(sizeof(double)*(ylen+hlen/4-1));
	
	for(int i=0; i<hlen/4; i++){
		ihpcd[i] = ihpc[0+4*i];
		rhpcd[i] = rhpc[0+4*i];
	}
	
	conv(rhpcd,hlen/4,yi,ylen,ypc0);
	conv(ihpcd,hlen/4,yq,ylen,ypc2);
	for(int i=0; i<ylen+hlen/4-1;i++){
		ypct0[i] = ypc0[i] - ypc2[i];
	}
	
	conv(ihpcd,hlen/4,yi,ylen,ypc0);
	conv(rhpcd,hlen/4,yq,ylen,ypc2);
	for(int i=0; i<ylen+hlen/4-1;i++){
		ypct2[i] = ypc0[i] + ypc2[i];
	}
	
	memcpy(yi,&ypct0[7],sizeof(double)*ylen);
	memcpy(yq,&ypct2[7],sizeof(double)*ylen);
	
	free(ihpcd);
	free(rhpcd);
	free(ypc0);
	free(ypc2);
	free(ypct0);
	free(ypct2);
}

void rerange(double *yi,double *yq,double **ryi,double **ryq,int row,int col)
{
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			ryi[i][j] = yi[i*col+j];
			ryq[i][j] = yq[i*col+j];
		}
	}
}

void mti(double **ryi,double **ryq,int row,int col)
{
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			if(i == row-1) { ryi[i][j] = 0.0; ryq[i][j] = 0.0;}
			else {
				ryi[i][j] = ryi[i+1][j] - ryi[i][j];
				ryq[i][j] = ryq[i+1][j] - ryq[i][j];
			}
		}
	}
}

void mtd(double **ryi,double **ryq,int row,int col)
{
	double *temp = (double*)malloc(sizeof(double)*row);
	double *temp2 = (double*)calloc(sizeof(double),row);
	
	for(int i=0; i<col; i++){
		//计算I路
		for(int j=0; j<row; j++){
			temp[j] = ryi[j][i];
			temp2[j] = 0.0;
		}
		
		fft(temp,temp2,row);
		for(int j=0; j<row; j++){
			ryi[j][i] = sqrt(temp[j]*temp[j] + temp2[j]*temp2[j]);
		}
		
		//计算Q路
		for(int j=0; j<row; j++){
			temp[j] = ryq[j][i];
			temp2[j] = 0.0;
		}
		fft(temp,temp2,row);
		for(int j=0; j<row; j++){
			ryq[j][i] = sqrt(temp[j]*temp[j] + temp2[j]*temp2[j]);
		}
	}

	free(temp);
	free(temp2);
}
double sum(double *d,int len)
{
	double sum = 0.0;
	for(int i=0; i<len; i++) sum += d[i];
	
	return sum;
}
char *cfar(struct cfarInf *cf,double *ymtd,int ylen)
{
	double alphe = cf->alphe;
	int numPro = cf->numPro;
	int numRef = cf->numRef;
	int numCfar = ylen + 2*(numPro+numRef);
	
	char *target = (char*)calloc(sizeof(char),ylen);
	double *ycfar = (double*)calloc(sizeof(double),numCfar);
	memcpy(&ycfar[numPro+numRef],ymtd,sizeof(double)*ylen);

	for(int n=numPro+numRef; n<numCfar-(numPro+numRef); n++){
		double left = sum(&ycfar[n-numPro-numRef],numRef)/numRef;
		double right = sum(&ycfar[n+numPro],numRef)/numRef;
		//判断准则
		double mean = (left+right)/2;
		double jusity = mean * alphe;
		//判决
		if( ycfar[n] > jusity && ycfar[n] > cf->door){
			int pos = n - numPro - numRef;
			target[pos] = 1;
		}
	}

	free(ycfar);
	return target;
}
=======
//
//产生LMF信号
//eagle-2017-4-9
//
#include <stdio.h>

#include "dp.h"
#include "dplib.h"

double *lmf(int *len)
{
	//读取LMF回波文件
	FILE *fp;
	
	fp = fopen("glmf.in","r");
	if(fp == NULL){
		perror("open file glme.in failed\n");
		return NULL;
	}
	
	fscanf(fp,"%d",len);
	double *dlmf = (double*)malloc(sizeof(double)*(*len));
	for(int i=0; i<*len; i++){
		fscanf(fp,"%lf",&dlmf[i]);
	}
	
	fclose(fp);
	
	return dlmf;
}

double *grhpc(int *len)
{
	//读取脉冲压缩滤波器信息
	FILE *fp;
	
	fp = fopen("rhpc.in","r");
	if(fp == NULL){
		perror("open file rhpc.in failed\n");
		return NULL;
	}
	
	fscanf(fp,"%d",len);
	double *rhpc = (double*)malloc(sizeof(double)*(*len));

	for(int i=0; i<*len; i++) {
		fscanf(fp,"%lf",&rhpc[i]);
	}

	fclose(fp);
	
	return rhpc;
}

double *gihpc(int *len)
{
	//读取脉冲压缩滤波器信息
	FILE *fp;
	
	fp = fopen("ihpc.in","r");
	if(fp == NULL){
		perror("open file ihpc.in failed\n");
		return NULL;
	}
	
	fscanf(fp,"%d",len);
	double *ihpc = (double*)malloc(sizeof(double)*(*len));

	for(int i=0; i<*len; i++) {
		fscanf(fp,"%lf",&ihpc[i]);
	}

	fclose(fp);
	
	return  ihpc;
}

int ddc(double *y,int ylen,double *yi,double *yq)
{
	//读取NCO的LPF系数
	FILE *fp;
	fp = fopen("hnco.in","r");
	
	int len;
	fscanf(fp,"%d",&len);
	
	double *hnco = (double*)malloc(sizeof(double)*len);
	for(int i=0; i<len; i++){
		fscanf(fp,"%lf",&hnco[i]);
	}
	
	fclose(fp);
	
	//抽取和滤波
	double *hnco0 = (double*)malloc(sizeof(double)*len/4);
	double *hnco2 = (double*)malloc(sizeof(double)*len/4);
	double *y0 = (double*)malloc(sizeof(double)*ylen/4);
	double *y2 = (double*)malloc(sizeof(double)*ylen/4);
	double *ynco0 = (double*)malloc(sizeof(double)*((len+ylen)/4-1));
	double *ynco2 = (double*)malloc(sizeof(double)*((len+ylen)/4-1));
	double *yncoi = (double*)malloc(sizeof(double)*((len+ylen)/4-1));
	double *yncoq = (double*)malloc(sizeof(double)*((len+ylen)/4-1));
	
	//对输入信号进行抽取 nco i路
	for(int i=0; i<ylen/4; i++){
		y0[i] = y[3+4*i];
		y2[i] = y[1+4*i];
	}
	for(int i=0; i<len/4; i++){
		hnco0[i] = hnco[0+4*i];
		hnco2[i] = hnco[2+4*i];
	}
	
	conv(hnco0,len/4,y0,ylen/4,ynco0);
	conv(hnco2,len/4,y2,ylen/4,ynco2);
	
	for(int i=0; i<(len+ylen)/4-1; i++){
		yncoi[i] = ynco0[i] - ynco2[i];
	}
	memcpy(yi,&yncoi[7],sizeof(double)*ylen/4);
	
	//对输入信号进行抽取 nco q路
	for(int i=0; i<ylen/4; i++){
		y0[i] = y[2+4*i];
		y2[i] = y[0+4*i];
	}
	for(int i=0; i<len/4; i++){
		hnco0[i] = hnco[1+4*i];
		hnco2[i] = hnco[3+4*i];
	}
	
	conv(hnco0,len/4,y0,ylen/4,ynco0);
	conv(hnco2,len/4,y2,ylen/4,ynco2);
	
	for(int i=0; i<(len+ylen)/4-1; i++){
		yncoq[i] = ynco2[i] - ynco0[i];
	}
	memcpy(yq,&yncoq[7],sizeof(double)*ylen/4);
	
	free(hnco);
	free(hnco0);
	free(hnco2);
	free(ynco0);
	free(ynco2);
	free(yncoi);
	free(yncoq);
	
	return ylen/4;
}

void pc(double *ihpc,double *rhpc,int hlen,double *yi,double *yq,int ylen)
{
	double *ihpcd = (double*)malloc(sizeof(double)*hlen/4);
	double *rhpcd = (double*)malloc(sizeof(double)*hlen/4);
	double *ypc0 = (double*)malloc(sizeof(double)*(ylen+hlen/4-1));
	double *ypc2 = (double*)malloc(sizeof(double)*(ylen+hlen/4-1));
	double *ypct0 = (double*)malloc(sizeof(double)*(ylen+hlen/4-1));
	double *ypct2 = (double*)malloc(sizeof(double)*(ylen+hlen/4-1));
	
	for(int i=0; i<hlen/4; i++){
		ihpcd[i] = ihpc[0+4*i];
		rhpcd[i] = rhpc[0+4*i];
	}
	
	conv(rhpcd,hlen/4,yi,ylen,ypc0);
	conv(ihpcd,hlen/4,yq,ylen,ypc2);
	for(int i=0; i<ylen+hlen/4-1;i++){
		ypct0[i] = ypc0[i] - ypc2[i];
	}
	
	conv(ihpcd,hlen/4,yi,ylen,ypc0);
	conv(rhpcd,hlen/4,yq,ylen,ypc2);
	for(int i=0; i<ylen+hlen/4-1;i++){
		ypct2[i] = ypc0[i] + ypc2[i];
	}
	
	memcpy(yi,&ypct0[7],sizeof(double)*ylen);
	memcpy(yq,&ypct2[7],sizeof(double)*ylen);
	
	free(ihpcd);
	free(rhpcd);
	free(ypc0);
	free(ypc2);
	free(ypct0);
	free(ypct2);
}

void rerange(double *yi,double *yq,double **ryi,double **ryq,int row,int col)
{
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			ryi[i][j] = yi[i*col+j];
			ryq[i][j] = yq[i*col+j];
		}
	}
}

void mti(double **ryi,double **ryq,int row,int col)
{
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			if(i == row-1) { ryi[i][j] = 0.0; ryq[i][j] = 0.0;}
			else {
				ryi[i][j] = ryi[i+1][j] - ryi[i][j];
				ryq[i][j] = ryq[i+1][j] - ryq[i][j];
			}
		}
	}
}

void mtd(double **ryi,double **ryq,int row,int col)
{
	double *temp = (double*)malloc(sizeof(double)*row);
	double *temp2 = (double*)calloc(sizeof(double),row);
	
	for(int i=0; i<col; i++){
		//计算I路
		for(int j=0; j<row; j++){
			temp[j] = ryi[j][i];
			temp2[j] = 0.0;
		}
		
		fft(temp,temp2,row);
		for(int j=0; j<row; j++){
			ryi[j][i] = sqrt(temp[j]*temp[j] + temp2[j]*temp2[j]);
		}
		
		//计算Q路
		for(int j=0; j<row; j++){
			temp[j] = ryq[j][i];
			temp2[j] = 0.0;
		}
		fft(temp,temp2,row);
		for(int j=0; j<row; j++){
			ryq[j][i] = sqrt(temp[j]*temp[j] + temp2[j]*temp2[j]);
		}
	}

	free(temp);
	free(temp2);
}
double sum(double *d,int len)
{
	double sum = 0.0;
	for(int i=0; i<len; i++) sum += d[i];
	
	return sum;
}
char *cfar(struct cfarInf *cf,double *ymtd,int ylen)
{
	double alphe = cf->alphe;
	int numPro = cf->numPro;
	int numRef = cf->numRef;
	int numCfar = ylen + 2*(numPro+numRef);
	
	char *target = (char*)calloc(sizeof(char),ylen);
	double *ycfar = (double*)calloc(sizeof(double),numCfar);
	memcpy(&ycfar[numPro+numRef],ymtd,sizeof(double)*ylen);

	for(int n=numPro+numRef; n<numCfar-(numPro+numRef); n++){
		double left = sum(&ycfar[n-numPro-numRef],numRef)/numRef;
		double right = sum(&ycfar[n+numPro],numRef)/numRef;
		//判断准则
		double mean = (left+right)/2;
		double jusity = mean * alphe;
		//判决
		if( ycfar[n] > jusity && ycfar[n] > cf->door){
			int pos = n - numPro - numRef;
			target[pos] = 1;
		}
	}

	free(ycfar);
	return target;
}
>>>>>>> origin/master
