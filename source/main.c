<<<<<<< HEAD
//
//产生LMF信号
//eagle-2017-4-9
//
#include <stdio.h>
#include <stdlib.h>

#include "dp.h"
#include "dplib.h"

int main(void)
{
	//获取LMF信号的相关信息
	double *rece;
	double *rhpc;
	double *ihpc;
	int rlen;
	int pclen;
	
	rece = lmf(&rlen);
	ihpc = gihpc(&pclen);
	rhpc = grhpc(&pclen);
	
	//数字下变频
	double *yi,*yq;
	yi = (double*)malloc(sizeof(double)*rlen/4);
	yq = (double*)malloc(sizeof(double)*rlen/4);
	
	int dlen = ddc(rece,rlen,yi,yq);

	FILE *fp,*fp2;
	fp = fopen("yddcq.out","w");
	fp2 = fopen("yddci.out","w");
	for(int i = 0; i<rlen/4; i++)
	{
		fprintf(fp,"%f\n",yq[i]);
		fprintf(fp2,"%f\n",yi[i]);
	}
	fclose(fp);
	fclose(fp2);
	
	//脉冲压缩
	pc(ihpc,rhpc,pclen,yi,yq,dlen);
	
	fp = fopen("ypcq.out","w");
	fp2 = fopen("ypci.out","w");
	for(int i = 0; i<dlen; i++)
	{
		fprintf(fp,"%f\n",yq[i]);
		fprintf(fp2,"%f\n",yi[i]);
	}
	fclose(fp);
	fclose(fp2);

	//数据重排
	int row = 16;
	int col = dlen / row;
	double **ryi = (double**)malloc(sizeof(double*)*row);
	for(int i=0; i<row; i++) ryi[i] = (double*)malloc(sizeof(double)*col);
	double **ryq = (double**)malloc(sizeof(double*)*row);
	for(int i=0; i<row; i++) ryq[i] = (double*)malloc(sizeof(double)*col);
	
	rerange(yi,yq,ryi,ryq,row,col);

	//MTI和MTD
	mti(ryi,ryq,row,col);

	fp = fopen("ymtii.out","w");
	fp2 = fopen("ymtiq.out","w");
	for(int i = 0; i<col; i++)
	{
		for(int j = 0; j<row; j++)
		{
			fprintf(fp,"%f ",ryi[j][i]);
			fprintf(fp2,"%f ",ryq[j][i]);
		}
		fprintf(fp,"\n");
		fprintf(fp2,"\n");
	}
	fclose(fp);
	fclose(fp2);

	mtd(ryi,ryq,row,col);
	
	double **ymtd = (double**)malloc(sizeof(double*)*row);
	for(int i=0; i<row; i++) ymtd[i] = (double*)malloc(sizeof(double)*col);
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			ymtd[i][j] = sqrt(ryi[i][j]*ryi[i][j]+ryq[i][j]*ryq[i][j]);
		}
	}
	
	
	fp = fopen("ymtd.out","w");
	for(int i = 0; i<col; i++)
	{
		for(int j = 0; j<row; j++)
		{
			fprintf(fp,"%f ",ymtd[j][i]);
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
	
	//CFAR
	struct cfarInf cf;
	cf.alphe = 17.6;
	cf.numPro = 3;
	cf.numRef = 8;
	cf.door = 200;
	char **target = (char**)malloc(sizeof(char*)*row);
	for(int i=0; i<row; i++){
		target[i] = cfar(&cf,ymtd[i],col);
	}
	
	fp = fopen("target.out","w");
	for(int i = 0; i<col; i++)
	{
		for(int j = 0; j<row; j++)
		{
			fprintf(fp,"%d ",target[j][i]);
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
	
	
	free(rece);
	free(rhpc);
	free(ihpc);
	free(yi);
	free(yq);
	for(int i=0; i<row; i++) { free(ryi[i]); free(ryq[i]);}
	free(ryi);
	free(ryq);
	for(int i=0; i<row; i++) free(ymtd[i]);
	free(ymtd);
	for(int i=0; i<row; i++) free(target[i]);
	free(target);
	
	return 0;
=======
//
//产生LMF信号
//eagle-2017-4-9
//
#include <stdio.h>
#include <stdlib.h>

#include "dp.h"
#include "dplib.h"

int main(void)
{
	//获取LMF信号的相关信息
	double *rece;
	double *rhpc;
	double *ihpc;
	int rlen;
	int pclen;
	
	rece = lmf(&rlen);
	ihpc = gihpc(&pclen);
	rhpc = grhpc(&pclen);
	
	//数字下变频
	double *yi,*yq;
	yi = (double*)malloc(sizeof(double)*rlen/4);
	yq = (double*)malloc(sizeof(double)*rlen/4);
	
	int dlen = ddc(rece,rlen,yi,yq);

	FILE *fp,*fp2;
	fp = fopen("yddcq.out","w");
	fp2 = fopen("yddci.out","w");
	for(int i = 0; i<rlen/4; i++)
	{
		fprintf(fp,"%f\n",yq[i]);
		fprintf(fp2,"%f\n",yi[i]);
	}
	fclose(fp);
	fclose(fp2);
	
	//脉冲压缩
	pc(ihpc,rhpc,pclen,yi,yq,dlen);
	
	fp = fopen("ypcq.out","w");
	fp2 = fopen("ypci.out","w");
	for(int i = 0; i<dlen; i++)
	{
		fprintf(fp,"%f\n",yq[i]);
		fprintf(fp2,"%f\n",yi[i]);
	}
	fclose(fp);
	fclose(fp2);

	//数据重排
	int row = 16;
	int col = dlen / row;
	double **ryi = (double**)malloc(sizeof(double*)*row);
	for(int i=0; i<row; i++) ryi[i] = (double*)malloc(sizeof(double)*col);
	double **ryq = (double**)malloc(sizeof(double*)*row);
	for(int i=0; i<row; i++) ryq[i] = (double*)malloc(sizeof(double)*col);
	
	rerange(yi,yq,ryi,ryq,row,col);

	//MTI和MTD
	mti(ryi,ryq,row,col);

	fp = fopen("ymtii.out","w");
	fp2 = fopen("ymtiq.out","w");
	for(int i = 0; i<col; i++)
	{
		for(int j = 0; j<row; j++)
		{
			fprintf(fp,"%f ",ryi[j][i]);
			fprintf(fp2,"%f ",ryq[j][i]);
		}
		fprintf(fp,"\n");
		fprintf(fp2,"\n");
	}
	fclose(fp);
	fclose(fp2);

	mtd(ryi,ryq,row,col);
	
	double **ymtd = (double**)malloc(sizeof(double*)*row);
	for(int i=0; i<row; i++) ymtd[i] = (double*)malloc(sizeof(double)*col);
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			ymtd[i][j] = sqrt(ryi[i][j]*ryi[i][j]+ryq[i][j]*ryq[i][j]);
		}
	}
	
	
	fp = fopen("ymtd.out","w");
	for(int i = 0; i<col; i++)
	{
		for(int j = 0; j<row; j++)
		{
			fprintf(fp,"%f ",ymtd[j][i]);
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
	
	//CFAR
	struct cfarInf cf;
	cf.alphe = 17.6;
	cf.numPro = 3;
	cf.numRef = 8;
	cf.door = 200;
	char **target = (char**)malloc(sizeof(char*)*row);
	for(int i=0; i<row; i++){
		target[i] = cfar(&cf,ymtd[i],col);
	}
	
	fp = fopen("target.out","w");
	for(int i = 0; i<col; i++)
	{
		for(int j = 0; j<row; j++)
		{
			fprintf(fp,"%d ",target[j][i]);
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
	
	
	free(rece);
	free(rhpc);
	free(ihpc);
	free(yi);
	free(yq);
	for(int i=0; i<row; i++) { free(ryi[i]); free(ryq[i]);}
	free(ryi);
	free(ryq);
	for(int i=0; i<row; i++) free(ymtd[i]);
	free(ymtd);
	for(int i=0; i<row; i++) free(target[i]);
	free(target);
	
	return 0;
>>>>>>> origin/master
}