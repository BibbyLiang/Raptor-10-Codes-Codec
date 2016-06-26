#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "time.h"
#include "Eigen\Eigen"
#include <iostream>
#include <string>
#include "Eigen\Lu"
#include "Eigen\Dense"

using namespace Eigen;
using namespace std;

unsigned int K, S, H, L, L1, N, m;
unsigned int **GLDPC;
char ss[17];
char **s;
unsigned int *snumone;
unsigned int countdfs = 0;
unsigned int **A;
float **B;
unsigned int **LT;

void dfs(unsigned int i)
{
	unsigned int j;
	//int x = pow(2., (int)H);
    if(i == H) 
    {
    	for(j = 0; j < H; j++)
    	{
    		s[countdfs][j] = ss[j];
    		if(48 == s[countdfs][j])s[countdfs][j] = 0;
    		if(49 == s[countdfs][j])s[countdfs][j] = 1;
    	}
    	//printf("%s\n", ss); //到达底部就输出
    	//s[i] = ss;
    	countdfs++;
    }
    else
    {
        dfs(i + 1); //深度优先搜索
        if(ss[i] == '0') ss[i] = '1';
        else ss[i] = '0'; //把当前位逆转
        dfs(i + 1); //继续向下搜索
    }

    return;
}


void gen_graycode()
{
	/*
	int i, j;
	int x = pow(2., n);
	//string* s=new string[x];
	char **s;
	s = (char**)malloc(sizeof(char*) * x);
	for(i = 0; i < x; i++)
	{
		s[i] = (char*)malloc(sizeof(char) * n);
	}
	unsigned int *snumone;
	snumone = (unsigned int*)malloc(sizeof(unsigned int) * x);
       for(i = 0; i < x; i++)
    	{
    		for(j = 0; j < n; j++)
    		{
    			s[i][j] = 0;
    		}
    	}
    	for(i = 0; i < x; i++)
    	{
    		snumone[i] = 0;
    	}

	int a = 0, b = 1;
    	for(i = 1; i < x; i++)
    	{
    		for(j = 0; j < n; j++)s[i][j] = s[i - 1][j];
    		if(0 != (i % 2))
    		{
    			printf("b = 0\n");
    			s[i][n - 1] = (s[i - 1][n - 1] + 1) % 2;
    		}
    		else
    		{
    		if(1 == b)
    		{
    			a++;
    			b = a;
    			printf("b = %d\n", b);
    			s[i][n - 1 - b] = (s[i - 1][n - 1 - b] + 1) % 2;
    		}
    		else
    		{
    			b--;
    			printf("b = %d\n", b);
    			s[i][n - 1 - b] = (s[i - 1][n - 1 - b] + 1) % 2;
    		}
    	}
    	for(j = 0; j < n; j++)
		{
			printf("%d ", s[i][j]);
		}
		printf("\n");
    	}

	for(i = 0; i < x; i++)
	{
		for(j = 0; j < n; j++)
		{
			if(1 == s[i][j])snumone[i]++;
		}
	}

	printf("-----------------------------\n");
	unsigned int halfH = H / 2;
	for(i = 0; i < x; i++)
	{
		if(halfH == snumone[i])
		{
			for(j = 0; j < n; j++)
			{
				printf("%d ", s[i][j]);
			}
			printf("\n");
		}
	}

    	free(s);
    	s = NULL;
    	free(snumone);
    	snumone = NULL;
       */

	unsigned int i, j;
	
	unsigned int x = (unsigned int)pow(2., (int)H);
	
	s = (char**)malloc(sizeof(char*) * x);
	for(i = 0; i < x; i++)
	{
		s[i] = (char*)malloc(sizeof(char) * H);
	}
	
	snumone = (unsigned int*)malloc(sizeof(unsigned int) * x);
    for(i = 0; i < x; i++)
    {
   		for(j = 0; j < H; j++)
   		{
   			s[i][j] = 0;
   		}
    }
    for(i = 0; i < x; i++)
    {
   		snumone[i] = 0;
   	}
	//scanf("%d",&n);
    //if(!H) break;
    for(i = 0; i < 17; i++) ss[i] = '0';
    ss[H] = '\0';
    dfs(0);
    //printf("\n");

    //printf("-----------------------------\n");
    for(i = 0; i < x; i++)
	{
		for(j = 0; j < H; j++)
		{
			if(1 == s[i][j])snumone[i]++;
			//printf("%d", s[i][j]);
		}
		//printf("\n");
	}
	
	unsigned int halfH = H / 2;
	//printf("%d\n", halfH);
	unsigned int sH = 0;
	for(i = 0; i < x; i++)
	{
		//printf("%d\n", halfH);
		if(halfH == snumone[i])
		{
			for(j = 0; j < H; j++)
			{
				printf("%d ", s[i][j]);
				A[S + H - 1 - j][sH] = s[i][j];
				
			}
			sH++;
			printf("\n");
		}
	}

	return;
}

void G_LT(unsigned int X)
{
	unsigned int i;
	FILE *fp;
	
	unsigned int *JK;
	unsigned long *V0, *V1;
	JK = (unsigned int*)malloc(sizeof(unsigned int) * 8189);
	V0 = (unsigned long*)malloc(sizeof(unsigned long) * 256);
	V1 = (unsigned long*)malloc(sizeof(unsigned long) * 256);

	fp = _fsopen("JK.txt", "r", _SH_DENYWR);
	for(i = 0; i < 8189; i++)
	{
		fscanf_s(fp, "%d ", &JK[i]);
	}
	/*
	for(i = 0; i < 8189; i++)
	{
		printf("%d \n", JK[i]);
	}
	*/
	fclose(fp);
	fp = NULL;
	
	fp = _fsopen("V0.txt", "r", _SH_DENYWR);
	for(i = 0; i < 256; i++)
	{
		fscanf_s(fp, "%lu ", &V0[i]);
	}
	
	/*
	for(i = 0; i < 256; i++)
	{
		printf("%lu \n", V0[i]);
	}
	*/
	fclose(fp);
	fp = NULL;
	
	fp = _fsopen("V1.txt", "r", _SH_DENYWR);
	for(i = 0; i < 256; i++)
	{
		fscanf_s(fp, "%lu ", &V1[i]);
	}
	
	/*
	for(i = 0; i < 256; i++)
	{
		printf("%lu \n", V1[i]);
	}
	*/
	fclose(fp);
	fp = NULL;
	
	unsigned int Q = 65521;
	unsigned int AA = (53591 + JK[K - 4] * 997) % Q;
	unsigned int B = 10267 * (JK[K - 4] + 1) % Q;
	unsigned int Y = (B + X * AA) % Q;
	
	//printf("%d\n", Y);
	unsigned long v = (V0[(Y + 0) % 256] ^ V1[((unsigned int)(floor((float)(Y / 256)) + 0) % 256)]) % (1048576);
	//printf("%lu\n", v);
	unsigned int d;
	if((1 <= v) && (10241 > v))
	{
		d = 1;
	}
	else if((10241 <= v) && (491582 > v))
	{
		d = 2;
	}
	else if((491582 <= v) && (712794 > v))
	{
		d = 3;
	}
	else if((712794 <= v) && (831695 > v))
	{
		d = 4;
	}
	else if((831695 <= v) && (948446 > v))
	{
		d = 5;
	}
	else if((948446 <= v) && (1032189 > v))
	{
		d = 6;
	}
	else
	{
		d = 7;
	}
	printf("Degree: %d\n", d);
	unsigned int a = 1 + (V0[(Y + 1) % 256] ^ V1[((unsigned int)(floor((float)(Y / 256)) + 1) % 256)]) % (L1 - 1);
	unsigned int b = (V0[(Y + 2) % 256] ^ V1[((unsigned int)(floor((float)(Y / 256)) + 2) % 256)]) % (L1);
	printf("a: %d\n", a);
	printf("b: %d\n", b);
	unsigned int index;
	for(i = 0; i < d; i++)
	{
		index = (i * a + b) % L1;
		printf("Index%d: %d\n", i, index);
		if(K > X)
		{
			A[S + H + X][index] = 1;
			LT[X][index] = 1;
		}
		if(K <= X)LT[X][index] = 1;
	}
	
	printf("-----------------------------\n");

	free(JK);
	JK = NULL;

	return;
}

void GParameters()
{
	unsigned int i;
	long long Ha, Hb, Hc, Hd, He, Hf;

	printf("Please Input the m: ");
	scanf_s("%d", &m);
	printf("Please Input the K: ");
	scanf_s("%d", &K);
	printf("Please Input the N: ");
	scanf_s("%d", &N);

	unsigned int F = 1;
	while(1)
	{
		if(F * (F - 1) > (2 * K))break;
		F++;
	}
	S = (unsigned int)ceil(0.01 * K) + F;
	printf("S0: %d\n", S);
	while(1)
	{
		for(i = 2; i < (S - 1); i++)
		{
			if(0 == (S % i))i = S + 1;
		}
		printf("i: %d\n", i);
		if((S - 1) == i)break;
		S++;
		printf("S: %d\n", S);
	}

	H = 2;
	while(1)
	{
		Ha = (unsigned int)ceil(float(H / 2));
		Hb = H - Ha;
		Hc = 1;
		Hd = 1;
		He = 1;
		Hf = 0;
		
		for(i = 1; i <= H;i++)
		{
			Hc = i * Hc;
		}
		for(i = 1; i <= Ha;i++)
		{
			Hd = i * Hd;
		}
		for(i = 1; i <= Hb;i++)
		{
			He = i * He;
		}
		/*
		printf("Hc: %d\n", Hc);
		printf("Hd: %d\n", Hd);
		printf("He: %d\n", He);
		*/

		Hf = Hc / (Hd * He);
		if(Hf > (K + S))break;
		H++;
	}

	L = K + S + H;

	L1 = L;
	while(1)
	{
		for(i = 2; i < (L1 - 1); i++)
		{
			if(0 == (L1 % i))i = L1 + 1;
		}
		printf("i: %d\n", i);
		if((L1 - 1) == i)break;
		L1++;
		printf("L1: %d\n", L1);
	}
	printf("L1: %d\n", L1);

	return;
}

void GMatrix()
{
	unsigned int i, j, k;

	unsigned int mod = K % S;
	unsigned int numblockldpc = (K - mod) / S + 1;
	printf("numblockldpc: %d\n", numblockldpc);
	unsigned int Indexa, Indexb, Indexc;
	for(k = 0; k < (numblockldpc - 1); k++)
	{
		Indexa = 0;
		Indexb = k + 1;
		Indexc = 2 * k + 2;
		GLDPC[Indexa][k * S] = 1;
		GLDPC[Indexb][k * S] = 1;
		GLDPC[Indexc][k * S] = 1;
		/*
		printf("!!!\n");
		printf("a: %d\n", Indexa);
		printf("b: %d\n", Indexb);
		printf("c: %d\n", Indexc);
		*/
		for(j = 1; j < S; j++)
		{
			Indexa = (Indexa + 1) % S;
			Indexb = (Indexb + 1) % S;
			Indexc = (Indexc + 1) % S;
			/*
			printf("a: %d\n", Indexa);
			printf("b: %d\n", Indexb);
			printf("c: %d\n", Indexc);
			*/
			GLDPC[Indexa][k * S + j] = 1;
			GLDPC[Indexb][k * S + j] = 1;
			GLDPC[Indexc][k * S + j] = 1;
		}
	}
	k = (numblockldpc - 1);
	Indexa = 0;
	Indexb = k + 1;
	Indexc = 2 * k + 2;
	GLDPC[Indexa][k * S] = 1;
	GLDPC[Indexb][k * S] = 1;
	GLDPC[Indexc][k * S] = 1;
	for(j = 1; j < mod; j++)
	{
		Indexa = (Indexa + 1) % S;
		Indexb = (Indexb + 1) % S;
		Indexc = (Indexc + 1) % S;
		GLDPC[Indexa][k * S + j] = 1;
		GLDPC[Indexb][k * S + j] = 1;
		GLDPC[Indexc][k * S + j] = 1;
	}
	for(i = 0; i < S; i++)
	{
		for(j = 0; j < K; j++)
		{
			printf("%d ", GLDPC[i][j]);
		}
		printf("\n");
	}

	return;
}

void GA()
{
	unsigned int i, j;
	
	for(i = 0; i < S; i++)
	{
		for(j = 0; j < K; j++)
		{
			A[i][j] = GLDPC[i][j];
		}
	}
	for(i = 0; i < S; i++)
	{
		for(j = 0; j < S; j++)
		{
			if(i == j)A[i][K + j] = 1;
		}
	}
	for(i = 0; i < H; i++)
	{
		for(j = 0; j < H; j++)
		{
			A[S + i][K + S + j] = 0;
			if(i == j)A[S + i][K + S + j] = 1;
		}
	}

	for(i = 0; i < L; i++)
	{
		for(j = 0; j < L; j++)
		{
			printf("%d ", A[i][j]);
		}
		printf("\n");
	}

	printf("-----------------------------\n");
	MatrixXf A1(L, L);
	MatrixXf B1(L, L);
	for(i = 0; i < L; i++)
	{
		for(j = 0; j < L; j++)
		{
			if(0 == A[i][j])A1(i, j) = 0.;
			if(1 == A[i][j])A1(i, j) = 1.;
		}
	}
	B1 = A1.inverse();
	//cout << B1 << endl;
	for(i = 0; i < L; i++)
	{
		for(j = 0; j < L; j++)
		{
			B[i][j] = B1(i, j);
		}
	}
	for(i = 0; i < L; i++)
	{
		for(j = 0; j < L; j++)
		{
			//printf("%d ", A[i][j]);
			//printf("%f ", A1(i, j));
			printf("%f ", B[i][j]);
		}
		printf("\n");
	}

	/*
	FILE *frc;
	frc = fopen("A.txt", "a+");
	for(i = 0; i < L; i++)
	{
		for(j = 0; j < L; j++)
		{
			fprintf(frc, "%d ", A[i][j]);
		}
		fprintf(frc, "\n");
	}
	fclose(frc);
	*/
	printf("-----------------------------\n");

	for(i = 0; i < N; i++)
	{
		for(j = 0; j < L; j++)
		{
			printf("%d ", LT[i][j]);
		}
		printf("\n");
	}
	printf("-----------------------------\n");

	MatrixXf Seq(L, m);
	Seq = MatrixXf::Random(L, m);
	cout << Seq << endl;
	for(i = 0; i < L; i++)
	{
		if(i < (S + H))
		{
			for(j = 0; j < m; j++)Seq(i, j) = 0.;
		}
		else
		{
			for(j = 0; j < m; j++)
			{
				Seq(i, j) = ceil(Seq(i, j));
			}
		}
	}
	cout << Seq << endl;
	printf("-----------------------------\n");

	MatrixXf C1(L, m);
	C1 = MatrixXf::Zero(L, m);
	C1 = B1 * Seq;
	cout << C1 << endl;
	printf("-----------------------------\n");

	MatrixXf E1(N, m);
	E1 = MatrixXf::Zero(N, m);
	MatrixXf LT1(L, L);
	LT1 = MatrixXf::Zero(N, L);
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < L; j++)
		{
			if(0 == LT[i][j])LT1(i, j) = 0.;
			if(1 == LT[i][j])LT1(i, j) = 1.;
		}
	}
	E1 = LT1 * C1;
	cout << E1 << endl;
	
	return;
}

void init()
{
	unsigned int i, j;
	
	GLDPC = (unsigned int**)malloc(sizeof(unsigned int*) * S);
	for(i = 0; i < S; i++)
	{
  		GLDPC[i] = (unsigned int*)malloc(sizeof(unsigned int) * K);
  	}
  	for(i = 0; i < S; i++)
	{
		for(j = 0; j < K; j++)
		{
			GLDPC[i][j] = 0;
		}
	}
	
	A = (unsigned int**)malloc(sizeof(unsigned int*) * L);
	for(i = 0; i < L; i++)
	{
  		A[i] = (unsigned int*)malloc(sizeof(unsigned int) * L);
  	}
  	for(i = 0; i < L; i++)
	{
		for(j = 0; j < L; j++)
		{
			A[i][j] = 0;
		}
	}
	B = (float**)malloc(sizeof(float*) * L);
	for(i = 0; i < L; i++)
	{
  		B[i] = (float*)malloc(sizeof(float) * L);
  	}
  	for(i = 0; i < L; i++)
	{
		for(j = 0; j < L; j++)
		{
			B[i][j] = 0;
		}
	}

	LT = (unsigned int**)malloc(sizeof(unsigned int*) * N);
	for(i = 0; i < L; i++)
	{
  		LT[i] = (unsigned int*)malloc(sizeof(unsigned int) * L);
  	}
  	for(i = 0; i < N; i++)
	{
		for(j = 0; j < L; j++)
		{
			LT[i][j] = 0;
		}
	}

	return;
}

void Exit()
{
	unsigned int i;
	unsigned int x = (unsigned int)pow(2., (int)H);
	
	for (i = 0; i < S; i++)
	{
  		free(GLDPC[i]);
		GLDPC[i] = NULL;
  	}
	free(GLDPC);
	GLDPC = NULL;
	for(i = 0; i < x; i++)
	{
		free(s[i]);
		s[i] = NULL;
	}
	free(s);
    s = NULL;
    free(snumone);
    snumone = NULL;

    /*
	for(i = 0; i < L; i++)
	{
		free(A[i]);
		A[i] = NULL;
	}
	free(A);
	A = NULL;
	
	for(i = 0; i < L; i++)
	{
		free(B[i]);
		B[i] = NULL;
	}
	free(B);
	B = NULL;

	for(i = 0; i < L; i++)
	{
		free(LT[i]);
		LT[i] = NULL;
	}
	free(LT);
	LT = NULL;
	*/

	return;
}

int main()
{
	unsigned int i;
	
	GParameters();
	printf("S: %d\n", S);
	printf("H: %d\n", H);
	printf("L: %d\n", L);
	init();
	GMatrix();
	gen_graycode();
	printf("-----------------------------\n");
	for(i = 0; i < N; i++)
	{
		printf("ROW: %d\n", i);
		G_LT(i);
	}
	GA();

	Exit();

	return 0;
}

