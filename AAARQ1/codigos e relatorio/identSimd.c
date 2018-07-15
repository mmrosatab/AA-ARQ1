#include <immintrin.h>
#include <stdio.h>
#include <time.h>

// Lista informações da arquitetura do seu computador --> cat /proc/cpuinfo
// Para compilar --> gcc -mavx identSimd.c -o identSimd

int main(int argc, char* argv[]) 
{	
	clock_t t1, t2;

	int tam = 8; // dimensao matriz
	int tamReg = 8; // tamanho registrador
	int n = tam * tam; // numero de elementos para criacao vetor-matriz
	int sair = 0;
	__m256 tempA,tempB,res;

	float *A = (float*)aligned_alloc(32, n * sizeof(float)); // matriz de entrada
	float *B = (float*)aligned_alloc(32, n * sizeof(float)); // matriz de comparacao 

	// carregando elemento no vetor-matriz
	for (int i = 0; i < n; i++)
	{
		if(i%(tam+1) == 0) //gerar identidade em B 
		{
			B[i] = 1.0; // B[i] = 0.0;
			A[i] = 1.0;
		}else
		{
			B[i] = 0.0;
			A[i] = 0.0;
		}
	}

	
	printf("Imprimindo matriz A\n");
	for (int i = 0; i < n; i++)
	{

		if(i%tam == 0)
		{
			printf("\n");
		}
		printf("%1.f  ",A[i]);

	}

	printf("\n");
	printf("\n");

	// sempre vai na memoria e pega um conjuntos de 8 elementos(max que pode pegar 256 bits(__mm256))

	float* f;

	t1 = clock();
	for (int i=0; i<n; i+=tamReg) 
	{
		
		tempA = _mm256_load_ps(&A[i]); // carrega 8 elementos de A 

		tempB = _mm256_load_ps(&B[i]); // carrega 8 elementos da matriz de resposta B

		__m256 result = _mm256_xor_ps(tempA,tempB); 
  
		/* Display the elements of the result vector */
		float* res = (float*)&result;
		//printf("%1.f %1.f %1.f %1.f %1.f %1.f %1.f %1.f\n",res[0], res[1], res[2], res[3], res[4], res[5], res[6], res[7]);

		if(res[0] != 0||res[1] != 0||res[2]!= 0||res[3]!= 0||res[4]!= 0||res[5]!= 0||res[6]!= 0||res[7]!= 0)
		{
			sair = 1;
			break;
		}
	}

	if (sair == 1)
	{
		printf("Nao eh identidade\n");
	}else
	{
		printf("Eh identidade\n");
	}

	t2 = clock();

	float tempo = (((float)t2 - (float)t1) / CLOCKS_PER_SEC ) * 1000;
	printf("Tempo em ms: %f\n",tempo);

  	return 0;
}