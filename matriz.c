#include <stdio.h>

#define L 3
#define C 4

FILE *op;

void imprimi(float m[L][C])
{
	int i, j;

	for(i=0; i<L; i++)
	{
		for(j=0; j<C; j++)
			printf("%.1f\t", m[i][j]);
		printf("\n");
	}
	printf("\n");
}
main()
{
	float m[L][C], pivo, x[L], b, aux=0.0, maux[L][C];
	int i, j, k;
	
	op=fopen("dados.dat","r");

	for(i=0; i<L; i++)
	{
		for(j=0; j<C; j++)
			fscanf(op,"%f\t", &m[i][j]);
	}

	printf("\t\n--------Matriz Aumentada--------\n");
	imprimi(m);
	
	//Vericando o maior elemento da 1ºcoluna
	for(k=0; k<L; k++)
	{
		if(m[k][k]!=0.0 )
		{
			if(m[k][k] < m[k+1][k])
			{
				//printf("ola\n");
				for(i=0; i<C; i++)
				{
					//printf("ola\n");
					maux[k+1][i]=m[k][i];
					m[k][i] = m[k+1][i];
					m[k+1][i] = maux[k+1][i];
				}
				
				//Imprimindo a troca de linha
				printf("\nTrocando as linhas\n");
				imprimi(m);
			}
		}
		else
		{
		
		}
		
	}
	
	//Imprimindo a troca de linha
	printf("\nTrocando as linhas\n");
	imprimi(m);

	for(i=1; i<L; i++)
	{
		pivo = m[i][0] / m[0][0];
		printf("%.1f", pivo);
		for(j=0; j<C; j++)
			m[i][j] = m[i][j] - (pivo * m[0][j]);
	}
        
	printf("\n--------Zerando a primeira coluna--------\n");
	imprimi(m);

	/*for(i=2; i<L; i++)
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
		printf("X%d = %.1f \t", i+1, x[i]);
	printf("\n\n");*/

	fclose(op);
}

