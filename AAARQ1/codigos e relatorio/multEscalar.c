#include <stdio.h>
#include <time.h>
#define TAM 8

int main(int argc, char *argv[])
{

	float A[TAM][TAM],B[TAM][TAM],C[TAM][TAM];

	for (int i = 0; i < TAM; i++)
	{
		for (int j = 0; j < TAM; j++)
		{
			if(i == j)
			{
				A[i][j] = 1;
			}else
			{
				A[i][j] = 0;
			}

			B[i][j] = 1;
		}
	}

	clock_t t1, t2;

	float* f;

	t1 = clock();

	printf("Resposta\n");
	for (int i = 0; i < TAM; i++)
	{
		for (int j = 0; j < TAM; j++)
		{
			C[i][j] = 0;

			for (int k = 0; k < TAM; k++)
			{
				C[i][j] = C[i][j] + A[i][k] * B[k][j];
			}

			printf("%1.f ", C[i][j]);
		}
		printf("\n");
	}

	t2 = clock();

	float tempo = (((float)t2 - (float)t1) / CLOCKS_PER_SEC ) * 1000;
	printf("Tempo em ms: %f\n",tempo);

	return 0;
}