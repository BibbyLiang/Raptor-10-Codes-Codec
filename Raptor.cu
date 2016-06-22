#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "device_launch_parameters.h"
#include <cuda_runtime_api.h>
#include <cufft.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include "time.h"
#include <helper_math.h>
//#include <iostream>
//#include <string>

unsigned int K, S, H, L;
unsigned int **GLDPC;
char ss[17];
char **s;
unsigned int *snumone;
unsigned int countdfs = 0;

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
	for(i = 0; i < x; i++)
	{
		//printf("%d\n", halfH);
		if(halfH == snumone[i])
		{
			for(j = 0; j < H; j++)
			{
				printf("%d ", s[i][j]);
			}
			printf("\n");
		}
	}
	
}


void GParameters()
{
	unsigned int i;
	long long Ha, Hb, Hc, Hd, He, Hf;
	
	printf("Please Input the K: ");
	scanf("%d", &K);

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
}

void init()
{
	unsigned int i, j;
	
	GLDPC = (unsigned int**)malloc(sizeof(unsigned int*) * S);
	for (i = 0; i < S; i++)
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
}

int main()
{
	GParameters();
	printf("S: %d\n", S);
	printf("H: %d\n", H);
	printf("L: %d\n", L);
	init();
	GMatrix();
	gen_graycode();

	Exit();
}
