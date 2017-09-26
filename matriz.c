#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

FILE *op;

double **gera(int dim)
{
	int i, j, k;
	double **M;

	srand((unsigned)time(NULL));
	M = malloc(dim*sizeof(double *));
	for(i=0; i<dim; i++)
	{
		M[i] = (double *)malloc((dim+1)*sizeof(double));
		for(i=0; i<dim; i++)
		{
			for(j=0; j<=dim; j++)
				M[i][j] = rand()%20 - 10;
		}
	}

	return(M);
}

void imprimi(double **M, int dim)
{
	int i, j;

	for(i=0; i<dim; i++)
	{
		for(j=0; j<dim+1; j++)
			printf("%lf\t", M[i][j]);
		printf("\n");
	}
	printf("\n");
}

int troca(double **M, int dim, int v)
{
	int i, j, cont=0, k;
	double aux;

	for(i=v; i<dim; i++)
	{
		if(M[i][v] != 0)
		{
			for(j=0; j<dim+1; j++)
			{
				aux = M[v][j];
				M[v][j] = M[i][j];
				M[i][j] = aux;
			}
			i = dim;
		}
	}
	cont++;

	return(cont);
}

double escalonamento(double **M, int dim, int v)
{
	int i, j;
	double pivo;

	//Fazendo o escalonamento
	for(i=v+1; i<dim; i++)
	{
		pivo = -1 * (M[i][v] / M[v][v]);

		for(j=v; j<dim+1; j++)
			M[i][j] = M[i][j] + (pivo * M[v][j]);
	}

}

void Reversa(double **M, int dim)
{
	double b, x[dim+1], aux;
	int i, j;

	b = M[dim-1][dim];
	x[3] = b / M[dim-1][dim-2];

	for(i=dim-1; i>=0; i--)
	{
		b = M[i][dim];
		for(j=i+1; j<dim; j++)
			aux += M[i][j]*x[j];
		x[i] = (b - aux) / M[i][i];

		aux=0;
	}

	printf("\n--------Solução da Equação--------\n");
	for(i=0; i<dim; i++)
		printf("X%d = %lf \t", i+1, x[i]);
	printf("\n\n");
}

void determinante(double **M, int dim, int cont)
{
	double det=1;
	int i;

	for(i=0; i<dim; i++)
		det *= M[i][i];
	printf("\n--------Determinante--------\n");

	if(cont%2 == 0)
		printf("%.2lf\n", det);
	else
		printf("%.2lf\n", -1.0*det);
}

double **LU(double **M, int dim)
{
	int i, j, k;
	double **L, **U, pivo, r;
	
	L = malloc(dim*sizeof(double *));
	U = malloc(dim*sizeof(double *));
	
	for(k=0; k<dim; k++)
	{
		L[k][1] = M[k][1];
		U[k][k] = 1;
		for(j=1; j<dim; j++)
			U[1][j] = M[1][j] / L[1][1];
	}
	
	for(k=0; k<dim; k++)
	{
		for(i=1; i<dim; i++)
			r += L[i][k]*U[i][k];	
	}
	
	for(i=1; i<dim; i++)
	{
		for(j=1; j<dim; j++)
				L[i][j] = M[i][j] - r;
	}

	imprimi(L, dim);
}

//Método de Jacobi
double jacobi(double **M, int dim)
{
	double er=1e-5, x0[dim], soma=0, b[dim], x[dim], dis;
	int i, j, k;
	
	
	for(i=0;i<dim;i++)
	{
		//Preenchendo vetor com zeros
		x[i]=0;
		//Preencher vetor b 
		b[i] = M[i][4];
	}
	
	do{
		
		for(i=0; i<dim; i++)
			x0[i]=x[i];
			
			
		dis=0;
		
		for(i=0; i<dim; i++)
		{
		
			soma=0;
			for(j=0; j<dim; j++)
			{
				if(j!=i)
					soma+=M[i][j]*x0[j];
			}
			x[i] = (1/M[i][i])*(b[i]-soma);
			dis += fabs(x0[i]-x[i]);	
		}
		
			
	}while(dis > er);
	
	printf("%.2g\t", dis);
	printf("\n");
	printf("%.2g\t", er);
	for(i=0; i<dim; i++)
		printf("%.2lf\t", x[i]);
		
	printf("\n\n");
	
}


main(int argc, char *argv[] )
{
	double **M, a, aux, pivo, b;
	int i, j, k, dim, cont;

	op=fopen(argv[1],"r");
	i=fscanf(op, "%d", &dim);

	double x[dim+1];

	M = malloc( dim*sizeof(double *) );
	
	for(i=0; i<dim; i++)
		M[i] = malloc((dim+1)*sizeof(double));
	i=j=0;

	while(fscanf(op, "%lf", &a) != EOF)
	{
		M[i][j] = a;
		j++;

		if(j == dim+1)
		{
			j=0;
			i++;
		}
	}

	printf("\t\n--------Matriz Aumentada--------\n");
	imprimi(M, dim);

	//fazendo o pivotamento da Matriz
	/*for(i=0; i<dim; i++)
	{
		if(M[i][i] == 0)
		{
			k = troca(M, dim, i);
			printf("\nNúmero de troca: %d\n", k);
		}	
		
		if(M[i][i] != 0)
			escalonamento(M, dim, i);
	}
	
	//Fazendo o escalonamento
	printf("\n--------Matriz Escalonada--------\n");
	imprimi(M, dim);

	//Substituição Reversa
	Reversa(M, dim);

	//Resolvendo o determinante
	determinante(M, dim, k);
	
	//Decomposição LU
	//LU(M, dim);
	//imprimi(LU, dim);*/
	
	//Método de Jacobi
	jacobi(M,dim);

	fclose(op);
}

