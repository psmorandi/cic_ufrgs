#include <stdlib.h>
#include <stdio.h>
#include <conio.h>


struct Nodo
{
	int chave;
	struct Nodo *prox;
};

/* algiritmo de insercao direta */
void Ordena(struct Nodo **lista)
{
	struct Nodo *tmp, *ant, *cur, *prox, *ordenada;

/* remove 1o elemento de lista e insere em ordenada */
	ordenada = *lista;
	*lista = (*lista)->prox;
	ordenada->prox = NULL;

	while (*lista != NULL)
	{
		cur = *lista;
		prox = cur->prox;

		/* pesquisa posicao p/ elemento *lista em ordenada */
		tmp = ordenada;
		ant = NULL;
		while ((tmp->prox != NULL) && (tmp->prox->chave < cur->chave))
		{
			ant = tmp;
			tmp = tmp->prox;
		}

		/* insere elemeno na lista ordenada */
		cur->prox = tmp;
		tmp = cur;
		if (ant == NULL)
			ordenada = tmp;
		else
			ant->prox = tmp;
		/* remove elemento da lista *lista */
		*lista = prox;
	}
	*lista = ordenada;

}

void main(int argc, char *argv[])
{
	FILE *arq;
	struct Nodo *lista = NULL, *tmp;
	int num_elem,i;

	if ( argc < 2 )
	{
	   printf("\nUso: ordena <nome do arquivo>\n");
	   exit(-1);
	}

	num_elem = 0;
	arq = fopen(argv[1],"r" );

	if (arq == NULL)
	{ 
		perror ("Error");
		exit(-1);
	}

        while ( !feof(arq) )
	{       
		tmp = (struct Nodo *)calloc(1, sizeof(struct Nodo));
		fscanf(arq, "%d",&(tmp->chave));
		tmp->prox = lista;
		lista = tmp;
		num_elem++;
	}

	tmp = lista;
	for (i=0;i<num_elem-1;i++)
	{
		printf("%d\n", tmp->chave);
		tmp = tmp->prox;
	}

	Ordena(&lista);
	printf("\nOrdenado!!!\n");
	tmp = lista;
	for (i=0;i<num_elem-1;i++)
	{
		printf("%d\n", tmp->chave);
		tmp = tmp->prox;
	}
}
