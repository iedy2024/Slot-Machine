#include <stdio.h>
#include <stdlib.h>

#define INF 1000000

int min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}
void eliberarea_memoriei(int **a, int N)
{
	int i;
	for (i = 0; i < N; i++)
	{
		free(a[i]);
		a[i] = NULL;
	}
	free(a);
	a = NULL;
}

int afis_mat(int **a, int N, int M)
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
			printf("%d ", a[i][j]);
		printf("\n");
	}
	return 0;
}

void rotire_matrice(int **matrice, int N, int M, int coloana, int nr_rotiri)
{
	int i, j, nr_pierdut;
	for (j = 0; j < nr_rotiri; j++)
	{
		nr_pierdut = matrice[N - 1][coloana];
		for (i = N - 1; i > 0; i--)
		{
			matrice[i][coloana] = matrice[i - 1][coloana];
		}
		matrice[0][coloana] = nr_pierdut;
	}
}

void calcul_scor(int **a, int N, int M, int *nr_combinatii_castigatoare, int *scor)
{
	int i, j;
	int lungime_max_linie = 1, caracter_linie, lungime_linie = 1, nr_tip_caractere = 0;
	int diag_princip = 0, diag_secund = 0;
	*nr_combinatii_castigatoare = 0;
	*scor = 0;
	int *tip_caractere;
	tip_caractere = calloc(10, sizeof(int));
	if (tip_caractere == NULL)
	{
		printf("Eroare la alocarea memoriei!\n");
	}
	for (i = 0; i < 3; i++)
	{
		for (j = 1; j < M; j++)
		{
			tip_caractere[a[i][0]] = 1;
			if (a[i][j] == a[i][j - 1])
			{
				lungime_linie++;
			}
			else
			{
				if (lungime_linie >= 3 && lungime_linie > lungime_max_linie)
				{
					lungime_max_linie = lungime_linie;
					caracter_linie = a[i][j - 1];
				}
				lungime_linie = 1;
				tip_caractere[a[i][j]] = 1;
			}
			if (i == 1 && j < M - 1)
			{
				if (a[i][j] == a[i - 1][j - 1] && a[i][j] == a[i + 1][j + 1])
				{
					diag_princip++;
				}
				if (a[i][j] == a[i - 1][j + 1] && a[i][j] == a[i + 1][j - 1])
				{
					diag_secund++;
				}
				if (diag_princip && diag_secund)
				{
					if (a[i][j] == 7)
					{
						*scor = *scor + 42;
					}
					else
						*scor = *scor + 21;
					*nr_combinatii_castigatoare += 1;
				}
				else if (diag_princip || diag_secund)
				{
					if (a[i][j] == 7)
					{
						*scor = *scor + 14;
					}
					else
						*scor = *scor + 7;
					*nr_combinatii_castigatoare += 1;
				}
				diag_princip = 0;
				diag_secund = 0;
			}
		}
		if (lungime_linie >= 3 && lungime_linie > lungime_max_linie)
		{
			lungime_max_linie = lungime_linie;
			caracter_linie = a[i][j - 1];
		}
		tip_caractere[a[i][j - 1]] = 1;
		if (lungime_max_linie != 1)
		{
			*nr_combinatii_castigatoare += 1;
			if (caracter_linie == 7)
			{
				*scor = *scor + lungime_max_linie * 2;
			}
			else
				*scor = *scor + lungime_max_linie;
		}
		lungime_linie = 1;
		lungime_max_linie = 1;
		caracter_linie = a[i][0];
	}
	if (lungime_linie >= 3 && lungime_linie > lungime_max_linie)
	{
		tip_caractere[a[i][j]] = 1;
		*nr_combinatii_castigatoare += 1;
		if (a[i][j - 1] == 7)
		{
			*scor = *scor + lungime_linie * 2;
		}
		else
			*scor = *scor + lungime_linie;
	}
	for (i = 0; i <= 9; i++)
	{
		if (tip_caractere[i])
		{
			nr_tip_caractere++;
		}
	}
	if (nr_tip_caractere <= 2)
	{
		*scor = *scor + 100;
	}
	else if (nr_tip_caractere <= 4)
	{
		*scor = *scor + 15;
	}
}

void verif_vecini(int *vecin, int val_init, int val_vecin, int dist_init)
{
	if (*vecin)
	{
		if (val_vecin > val_init)
		{
			*vecin = min(dist_init + val_vecin - val_init, *vecin);
		}
		else
		{
			*vecin = min(dist_init + val_init - val_vecin, *vecin);
		}
	}
}
void verif_SEW(int **distanta, int M, int i, int j, int **a)
{
	if (j < M - 1)
	{
		verif_vecini(&distanta[i][j + 1], a[0][0], a[i][j + 1], distanta[i][j]);
	}
	if (j > 0)
	{
		verif_vecini(&distanta[i][j - 1], a[0][0], a[i][j - 1], distanta[i][j]);
	}
	if (i < 2)
	{
		verif_vecini(&distanta[i + 1][j], a[0][0], a[i + 1][j], distanta[i][j]);
	}
}
void verif_N(int **distanta, int M, int **a, int i, int j)
{
	if (i > 0)
	{
		int dist_sus_ant = distanta[i - 1][j];
		verif_vecini(&distanta[i - 1][j], a[0][0], a[i - 1][j], distanta[i][j]);
		if (dist_sus_ant != INF && distanta[i - 1][j] < dist_sus_ant)
		{
			for (int k = i - 1; k >= 0; k--)
			{
				for (int l = j; l < M; l++)
				{
					verif_SEW(distanta, M, k, l, a);
					if ((i - 1) == 1)
						verif_N(distanta, M, a, i - 1, j);
				}
			}
		}
	}
}

int main(void)
{
	int nr_task, N, M, i, j;
	int **a;
	scanf("%d", &nr_task);
	scanf("%d%d", &N, &M);
	a = malloc(sizeof(int *) * N);
	if (a == NULL)
	{
		printf("Eroare la alocarea memoriei!\n");
		return 1;
	}
	for (i = 0; i < N; i++)
	{
		a[i] = malloc(sizeof(int) * M);
		if (a[i] == NULL)
		{
			printf("Eroare la alocarea memoriei!\n");
			return 1;
		}
	}
	for (i = 0; i < N; i++)
		for (j = 0; j < M; j++)
		{
			scanf("%d", &a[i][j]);
		}
	switch (nr_task)
	{
	case 1:
	{
		int c, r;
		scanf("%d%d", &c, &r);
		rotire_matrice(a, N, M, c, r);
		afis_mat(a, N, M);
		break;
	}
	case 2:
	{
		int nr_combinatii_castigatoare, scor;
		calcul_scor(a, N, M, &nr_combinatii_castigatoare, &scor);
		printf("%d\n%d\n", nr_combinatii_castigatoare, scor);
		break;
	}
	case 3:
	{
		int i, nr_rotiri, c, r;
		int nr_combinatii_castigatoare = 0, scor = 0, scor_final = 0;
		scanf("%d", &nr_rotiri);
		for (i = 0; i < nr_rotiri; i++)
		{
			scanf("%d%d", &c, &r);
			rotire_matrice(a, N, M, c, r);
			calcul_scor(a, N, M, &nr_combinatii_castigatoare, &scor);
			scor_final += scor;
		}
		printf("%d\n", scor_final);
		break;
	}
	case 4:
	{
		int i, j, k, useless = 0, scor = 0, scor_max, nr_pierdut;
		calcul_scor(a, N, M, &useless, &scor);
		scor_max = scor;
		for (i = 0; i < 3; i++)
		{
			for (j = 1; j < M; j++)
			{
				nr_pierdut = a[i][j];
				for (k = 0; k <= 9; k++)
				{
					if (a[i][j] != k)
					{
						a[i][j] = k;
						calcul_scor(a, N, M, &useless, &scor);
						if (scor > scor_max)
						{
							scor_max = scor;
						}
					}
				}
				a[i][j] = nr_pierdut;
			}
		}
		printf("%d\n", scor_max);
		break;
	}
	case 5:
	{
		int i, j, rotiri_j = 0, useless = 0, scor = 0, scor_max = 0, rotiri_i = 0;
		calcul_scor(a, N, M, &useless, &scor);
		scor_max = scor;
		for (i = 0; i < M - 1; i++)
		{
			while (rotiri_i < N)
			{
				rotire_matrice(a, N, M, i, 1);
				calcul_scor(a, N, M, &useless, &scor);
				if (scor > scor_max)
				{
					scor_max = scor;
				}
				rotiri_i++;
				for (j = i + 1; j < M; j++)
				{
					while (rotiri_j < N)
					{
						rotire_matrice(a, N, M, j, 1);
						calcul_scor(a, N, M, &useless, &scor);
						if (scor > scor_max)
						{
							scor_max = scor;
						}
						rotiri_j++;
					}
					rotiri_j = 0;
				}
			}
			rotiri_i = 0;
		}
		printf("%d\n", scor_max);
		break;
	}
	case 6:
	{
		int i, j;
		int **distanta;
		distanta = malloc(sizeof(int *) * 3);
		if (distanta == NULL)
		{
			printf("Eroare la alocarea memoriei!\n");
			return 1;
		}
		for (i = 0; i < 3; i++)
		{
			distanta[i] = malloc(sizeof(int) * M);
			if (distanta[i] == NULL)
			{
				printf("Eroare la alocarea memoriei!\n");
				return 1;
			}
		}
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < M; j++)
			{
				distanta[i][j] = INF;
			}
		}
		distanta[0][0] = 0;
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < M; j++)
			{
				verif_SEW(distanta, M, i, j, a);
				verif_N(distanta, M, a, i, j);
			}
		}
		printf("%d\n", distanta[2][M - 1]);
		eliberarea_memoriei(distanta, 3);
	}
	}
	eliberarea_memoriei(a, N);
	return 0;
}