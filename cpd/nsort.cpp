//
//  TRABALHO DE CLASSIFICACAO E PESQUISA DE
//  DADOS
//
//  Arquivo: nsort.cpp
//  Objetivo: definir as funcoes da classe Sort, usadas
//                ordenar arquivos externos;
//  Aluno: Paulo Sergio Morandi Junior
//  Prof.: Manuel Menezes de Oliveira Neto
//------------------------------------------------------------------------------


#include <iostream>
#include <stdlib.h>   //Para funcao de alocacao dinamica
#include <fstream.h>  //Para manipulacao de arquivos
#include <string.h>

using std::cout;
using std::endl;

class Sort {

	public:
		int* Aloca( int );
		void HeapSort( int* );
		void BuildHeap( int* );
		void Heapify( int*, int );
		void MergeSort( int*, int, int );
	private:
		int length_A,heap_size_A;
		
		//Funcao que retorna filho da esquerda
		int Esquerda( int i ) { return (2*i+1);   }
		//Funcao que retorna filho da direita
		int Direita ( int i ) { return (2*i+2); }
		
		//Funcao que intercala dois vetores
		void Merge( int* c, int i, int m, int f )
		{
			int i1 = i, i2 = m+1, aux[i+f], k = 0;

			while (k < f-i+1)
			{
				if( (i1<=m) && ((i2 > f) || (c[i1] < c[i2])) )
				{
					aux[k] = c[i1];i1++;
				}
				else
				{
					aux[k] = c[i2];i2++;
				} 	
				k++;			
			}
			k = 0;
			for(i1=i;i1<=f;i1++)
			{
				c[i1] = aux[k]; k++;
			}
		}//Do merge
}; //Da classe Sort

//--------------------------------------------------------
// Funcao que aloca o vetor e atualiza o tamanho do mesmo
// inicializando a variavel private length_A
//--------------------------------------------------------
int* Sort::Aloca ( int n )
{
	length_A = n;
	return new int[n];
}

//-------------------------------------------------------
// METODO DO HEAPSORT
// c: ponteiro para o vetor de chaves
// Obs.: antes de executar o Heapsort a funcao "aloca" deve
//       ser executada. Nao tente alocar o vetor sem usar a
//       funcao "aloca" presente na classe, caso contrario 
//       nao respondo pelo que acontercer!
//-------------------------------------------------------
void Sort::HeapSort( int* c )
{
	int i,aux;

	BuildHeap( c );
	for(i=length_A-1;i>=1;i--)
	{
		aux = c[i];   c[i] = c[0];   c[0] = aux;
		heap_size_A--;
		Heapify( c, 0);
	}
}

//--------------------------------------------------------
// Funcao que constroi um heap a partir de um dado vetor
// "c"
//--------------------------------------------------------
void Sort::BuildHeap( int* c )
{
	int i;
	
	heap_size_A = length_A;
	for(i=(length_A/2)-1;i>=0;i--)
		Heapify( c, i ); 
	
}

//----------------------------------------------------------
// Funcao que reorganiza o vetor "c" a partir da posicao "i"
// a fim de manter a propriedade de um heap
//----------------------------------------------------------
void Sort::Heapify( int* c, int i )
{
	int e = Esquerda(i) , d = Direita(i), maior = i, aux;

	if( (e < heap_size_A) && (c[e] > c[maior]) )
		maior = e;  //filho da esquerda eh maior
	if( (d < heap_size_A) && (c[d] > c[maior]) )
		maior = d;  //filho da direita eh maior
	if( maior != i )
	{
		aux = c[i];   c[i] = c[maior];   c[maior] = aux;
		Heapify( c, maior );
	}
}

//---------------------------------------------------------
// METODO DO MERGESORT
// c: ponteiro para o vetor de chaves
// i: inicio do vetor de chaves
// f: fim do vetor de chaves
// --------------------------------------------------------
void Sort::MergeSort ( int* c, int i, int f )
{
	int m;
	
	if ( i < f )
	{
		m = (i + f)/2;
		MergeSort( c, i, m );
		MergeSort( c, m+1, f );
		Merge( c, i, m, f );
	}
}

int main(int argc, char *argv[])
{
	//---------
	// argc: numero de entradas digitadas na linha de comando
	// argv: apontador para as strings digitadas na linha de comando
	// dim: dimensao do vetor de chaves;
	// chaves: ponteiro para o vetor de chaves;
	// arq: aponta para o arquivo de entrada;
	// saida: aponta para o arquivo de saida;
	// --------
	int i, dim, *chaves;
	ifstream arq;
	ofstream saida;
	Sort funcoes; //Serah usado para chamar as funcoes da classe Sort

if (argc < 3)
{
	cout << "UFRGS - Universidade Federal do Rio Grande do sul" << endl;
	cout << "PSMJ FILE SORT - final version - JAN/2003" << endl;
	cout << "Autor: Paulo Sergio Morandi Junior" << endl;
	cout << "Uso: "<<argv[0]<<" <opcao_sort> <nome_arq>" << endl << endl;
	cout << "Opcoes de sort: " << endl;
	cout << "-h\t=> Heapsort" << endl;
	cout << "-m\t=> Mergesort" << endl << endl;
	cout << "Bugs e reclamacoes - psmj@ibest.com.br" << endl;
}
else
{
	 arq.open( argv[2] ); //Abre o arquivo somente para leitura
	 if ( !arq )          //Verifica se conseguiu abrir o arquivo
            cout << "Erro: " << argv[2] << " - Arquivo nao encontrado" << endl;
	 else
	 {
		if ( !(strcmp(argv[1],"-h")) )
		{
		//Selecionado a opcao de HeapSort
			arq >> dim;
			chaves = funcoes.Aloca(dim);
			i = 0;
			while( i < dim )
			{
			   arq >> chaves[i];
			   i++;
			}
			funcoes.HeapSort( chaves );
		}
		else
			if( !( strcmp(argv[1],"-m") ) )
		    	{
		    	//Selecionado a opcao de MergeSort
				arq >> dim;
				chaves = funcoes.Aloca(dim);
				i = 0;
				while( i < dim )
				{
					arq >> chaves[i];
					i++;
				}
			funcoes.MergeSort( chaves, 0, dim-1 );
			}
			else
			{
				cout << "Error: \"" << argv[1] << "\" eh uma opcao invalida" << endl;
				exit(-1);
			}
	cout << "Vetor final ordenado em \"ordenado.txt\" " << endl;
	saida.open( "ordenado.txt" ); //Direcionando as saidas para ordenado.txt
	for( i=0; i < dim; i++)
		saida << chaves[i] << endl;
	arq.close();
	saida.close();
	} //do segundo ELSE

} //do primeiro ELSE
      return 0;
}
