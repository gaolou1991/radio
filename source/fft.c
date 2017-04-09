<<<<<<< HEAD
<<<<<<< HEAD
//
//FFT
//esgle-2017-4-7
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "dplib.h"

void swap(double *a, double *b)
{
	double tp = *a;
	*a = *b;
	*b = tp;
}

void fft(double *rex, double *imx, int n)
{
	double pi = 3.1415926;
	int nm = n - 1;
	int nd2 = n / 2;
	int m = (double)log((double)n) / log((double)2);

	//位反转排序算法
	int i, j, k;
	j = nd2;
	for (i = 1; i <= n - 2; i++)
	{
		if (i<j){
			swap(&rex[i], &rex[j]);
			swap(&imx[i], &imx[j]);
		}
		k = nd2;
		while (k <= j){
			j -= k;
			k /= 2;
		}
		j += k;
	}

	for (k = 1; k <= m; k++)
	{
		int le = pow((double)2, (double)k);
		int le2 = le / 2;
		double ur = 1.0;
		double ui = 0.0;
		double sr = cos(pi / le2);
		double si = -sin(pi / le2);
		double tr, ti;

		for (j = 1; j <= le2; j++)
		{
			int jm = j - 1;
			for (i = jm; i<nm; i += le)
			{
				int ip = i + le2;
				tr = rex[ip] * ur - imx[ip] * ui;
				ti = rex[ip] * ui + imx[ip] * ur;
				rex[ip] = rex[i] - tr;
				imx[ip] = imx[ip] - ti;
				rex[i] = rex[i] + tr;
				imx[i] = imx[i] + ti;
			}
			tr = ur;
			ur = tr*sr - ui*si;
			ui = tr*si + ui*sr;
		}
	}
}

#ifdef debug_main
int main(void)
{
	double rex[16] = { 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 };
	double imx[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	fft(rex, imx, 16);

	FILE *fp,*fp2;
	fp = fopen("realx.txt", "w+");
	fp2 = fopen("imagx.txt", "w+");
	for (int i = 0; i < 16; i++)
	{
		fprintf(fp, "%f\n", rex[i]);
		fprintf(fp2, "%f\n", imx[i]);
	}
	fclose(fp);
	fclose(fp2);
}
#endif
=======
#
>>>>>>> origin/master
=======
<<<<<<< HEAD
//
//FFT
//esgle-2017-4-7
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "dplib.h"

void swap(double *a, double *b)
{
	double tp = *a;
	*a = *b;
	*b = tp;
}

void fft(double *rex, double *imx, int n)
{
	double pi = 3.1415926;
	int nm = n - 1;
	int nd2 = n / 2;
	int m = (double)log((double)n) / log((double)2);

	//位反转排序算法
	int i, j, k;
	j = nd2;
	for (i = 1; i <= n - 2; i++)
	{
		if (i<j){
			swap(&rex[i], &rex[j]);
			swap(&imx[i], &imx[j]);
		}
		k = nd2;
		while (k <= j){
			j -= k;
			k /= 2;
		}
		j += k;
	}

	for (k = 1; k <= m; k++)
	{
		int le = pow((double)2, (double)k);
		int le2 = le / 2;
		double ur = 1.0;
		double ui = 0.0;
		double sr = cos(pi / le2);
		double si = -sin(pi / le2);
		double tr, ti;

		for (j = 1; j <= le2; j++)
		{
			int jm = j - 1;
			for (i = jm; i<nm; i += le)
			{
				int ip = i + le2;
				tr = rex[ip] * ur - imx[ip] * ui;
				ti = rex[ip] * ui + imx[ip] * ur;
				rex[ip] = rex[i] - tr;
				imx[ip] = imx[ip] - ti;
				rex[i] = rex[i] + tr;
				imx[i] = imx[i] + ti;
			}
			tr = ur;
			ur = tr*sr - ui*si;
			ui = tr*si + ui*sr;
		}
	}
}

#ifdef debug_main
int main(void)
{
	double rex[16] = { 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 };
	double imx[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	fft(rex, imx, 16);

	FILE *fp,*fp2;
	fp = fopen("realx.txt", "w+");
	fp2 = fopen("imagx.txt", "w+");
	for (int i = 0; i < 16; i++)
	{
		fprintf(fp, "%f\n", rex[i]);
		fprintf(fp2, "%f\n", imx[i]);
	}
	fclose(fp);
	fclose(fp2);
}
#endif
=======
#
>>>>>>> origin/master
>>>>>>> origin/master
