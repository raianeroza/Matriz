#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int troca(double **M, int dim)
{
	int i, j, cont=0, k;
	double aux;

	aux=M[0][0];
	for(i=0; i<dim; i++)
	{
		if(aux < M[i][0])
		{
			aux=M[i][0];
			k=i;
		}
	}

	for(j=0; j<dim+1; j++)
	{
		aux = M[0][j];
		M[0][j] = M[k][j];
		M[k][j] = aux;
		cont++;
	}

	printf("\n--------Pivotamento--------\n");
	imprimi(M, dim);

	return(aux);
}

void escalonamento(double **M, int dim)
{
	int i, j, v;
	double pivo;

	//Fazendo o escalonamento
	for(v=0; v<dim-1; v++)
	{
		for(i=v+1; i<dim; i++)
		{
			pivo = (M[i][v] / M[v][v]);

			for(j=v; j<dim+1; j++)
				M[i][j] = M[i][j] - (pivo * M[v][j]);
		}
	}

	imprimi(M, dim);
}

void Reversa(double **M, int dim)
{
	double b, x[dim+1], aux;
	int i, j;

	b = M[dim-1][(dim+1)-1];
	x[3] = b / M[dim-1][(dim+1)-2];

	for(i=dim-1; i>=0; i--)
	{
		b = M[i][(dim+1)-1];
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
	k=troca(M, dim);
	printf("Número de trocas: %d\n", k);

	//Fazendo o escalonamento
	escalonamento(M, dim);

	//Substituição Reversa
	Reversa(M, dim);

	//Resolvendo o determinante
	determinante(M, dim, k);

	fclose(op);
}

