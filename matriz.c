#include <stdio.h>

#define L 4
#define C 5

FILE *op;

main()
{
	int m[L][C], pivo, x[L], b, aux=0, i, j;
	op=fopen("Arquivo.dat","r");

	for(i=0; i<L; i++)
	{
		for(j=0; j<C; j++)
			fscanf(op,"%d\t", &m[i][j]);
	}
}

