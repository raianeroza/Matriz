#include <stdio.h>

#define L 4
#define C 5

FILE *op;

void imprimi(int m[L][C])
{
	int i, j;

	for(i=0; i<L; i++)
	{
		for(j=0; j<C; j++)
			printf("%d\t", m[i][j]);
		printf("\n");
	}
	printf("\n");
}
main()
{
	int m[L][C], pivo, x[L], b, aux=0, i, j;
	op=fopen("Arquivo.dat","r");

	for(i=0; i<L; i++)
	{
		for(j=0; j<C; j++)
			fscanf(op,"%d\t", &m[i][j]);
	}

	printf("\t\n--------Matriz Aumentada--------\n");
	imprimi(m);

	for(i=1; i<L; i++)
	{
		pivo = m[i][0] / m[0][0];
		for(j=0; j<C; j++)
			m[i][j] = m[i][j] - (pivo * m[0][j]);
	}
	printf("\n--------Zerando a primeira coluna--------\n");
	imprimi(m);

	for(i=2; i<L; i++)
	{
		pivo = m[i][1] / m[1][1];
		for(j=0; j<C; j++)
			m[i][j] = m[i][j] - (pivo * m[1][j]);
	}
	printf("\n--------Matriz na forma Triangular--------\n");
	imprimi(m);

	b = m[L-1][C-1];
	x[3] = b / m[L-1][C-2];

	for(i=L-1; i>=0; i--)
	{
		b = m[i][C-1];
		for(j=i+1; j<L; j++)
			aux += m[i][j]*x[j];
		x[i] = (b - aux) / m[i][i];

		aux=0;
	}

	printf("\n--------Solução da Equação--------\n");
	for(i=0; i<L; i++)
		printf("X%d = %d \t", i+1, x[i]);
	printf("\n\n");

	fclose(op);
}

