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
}

