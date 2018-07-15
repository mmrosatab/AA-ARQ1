#include <immintrin.h>
#include <stdio.h>
#include <time.h>

// Lista informações da arquitetura do seu computador --> cat /proc/cpuinfo
// Para compilar --> gcc -mavx multSimd.c -o multSimd

int main(int argc, char* argv[]) 
{	
	
	int tam = 8;
	int tamReg = 8;
	int n = tam * tam;
	__m256 tempA,tempB,res;

	
	float *A = (float*)aligned_alloc(32, n * sizeof(float));
	float *B = (float*)aligned_alloc(32, n * sizeof(float));
	float *C = (float*)aligned_alloc(32, n * sizeof(float));
	

	// carregando elemento no vetor-matriz
	for (int i = 0; i < n; i++)
	{
		if(i%(tam+1) == 0)
		{
			A[i] = 1;
		}else
		{
			A[i] = 0;
		}
		
		B[i] = 1;
	}

	clock_t t1, t2;
	t1 = clock();

	// sempre vai na memoria e pega um conjuntos de 8 elementos(max que pode pegar 256 bits(__mm256))
	
	for (int i=0; i<n; i+=tamReg) 
	{
		// sempre vai na memoria e pega um conjuntos de 8 elementos(max que pode pegar 256 bits(__mm256))
		tempA = _mm256_load_ps(A); // carrega 8 numeros da memoria(linha da matriz) para um registrador  

		tempB = _mm256_set1_ps(B[i]);  // pega um elemento de B e cria um vetor de 8 posicoes com o elemento de B

		res = _mm256_mul_ps(tempA, tempB); // aplica multiplicacao entre registradores
		
		for (int j=1; j<tamReg; j++) 
		{
			tempA = _mm256_load_ps(&A[j*tamReg]); 
			tempB = _mm256_set1_ps(B[i+j]);                       
			res = _mm256_add_ps(_mm256_mul_ps(tempA, tempB), res); // aplicação multicação e depois uma soma
		}
		_mm256_store_ps(&C[i], res);     // r[i] = r_line
	}

	t2 = clock();

	printf("Imprimindo Resultado\n");

	for (int i = 0; i < n; i++)
	{

		if(i%tam == 0)
		{
			printf("\n");
		}
		printf("%1.f  ",C[i]);

	}

	printf("\n");
	printf("\n");

	float tempo = (((float)t2 - (float)t1) / CLOCKS_PER_SEC ) * 1000;
	printf("Tempo em ms: %f\n",tempo);

  	return 0;
}