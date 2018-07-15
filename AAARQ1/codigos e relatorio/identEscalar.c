#include <stdio.h>
#include <time.h>
#define TAM 8

int main(int argc, char *argv[])
{

	float A[TAM][TAM];
	int sair = 0;

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
			if (i == j)
			{
				if(A[i][j] != 1)
				{
					sair = 1;
				}

			}else
			{
				if(A[i][j] != 0)
				{
					sair = 1;
				}
			}

			if(sair == 1)
			{
				t2 = clock();
				float tempo = (((float)t2 - (float)t1) / CLOCKS_PER_SEC ) * 1000;
				printf("Nao eh identidade\n");
				printf("Tempo em ms: %f\n",tempo);
				return 0;
			}

		}

	}

	t2 = clock();

	printf("Eh identidade\n");
	float tempo = (((float)t2 - (float)t1) / CLOCKS_PER_SEC ) * 1000;
	printf("Tempo em ms: %f\n",tempo);

	return 0;
}