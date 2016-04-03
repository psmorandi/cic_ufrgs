#include <iostream.h>
#include <iomanip.h>
#include <stdio.h>

//----------------------------------------------------------------
// Trabalho de Classificacao e Pesquisa de Dados - TRABALHO NO. 3
// Nome: Paulo Sergio Morandi Junior - 2767/01-1
// 3o. semestre
// JAN/2003
// Este trabalho cria uma tabela para ser manipulada fazendo-se
// uso de uma tabela extra de descritores que serve para indexar a 
// tabela principal. A funcao HASH definida aqui ( (chave mod TAM)+1 )nao eh a 
// mais complicada para facilitar a colisoes e testar se o trabalho
// consegue manipular adequadamente as mesmas. Existe um "BUG" neste trabalho
// que nao foi contornado, mas nada tem a haver com as rotinas implementadas
// e sim com a funcao "cin". Quando eh solicitada a leitura de um array de
// caracters, a mesma pega os caracteres ateh o primeiro espaco, e devolve na 
// tela. Mas se o usuario digitar "NOME <espaco> OUTRO" a funcao se perde 
// e entra em "loop infinito". Como a solucao deste problema foge do escopo do
// trabalho, nao foi implementada. Hah outros problemas como o nao tratamento
// da data de nascimento. Qualquer numero eh valido como data de nascimento.
// Mas, denovo, como fugia do escopo do trabalho nada foi feito para contornar
// este problema.
// ---------------------------------------------------------------

//Area "oficial" da tabela eh TAM/2 mas eh colocado o dobro para questoes de
//estudo sobre remocao e inclusao na tabela
//OBS.: A posicao "0" (zero) dos vetores tab e desc abaixo nao serao usadas para
//facilitar o entendimento do programa e a programacao

#define TAM 14

//Caso queira que a tabela de descritores naum seja mostrada COMENTE a linha
//abaixo:
#define DESCR

typedef struct{
	int num;
	char nome[200];
	long datnasc;
	int prox;
	int ant;
}tabela;

typedef struct{
	int prim;
	int ult;
}descritor;

tabela tab[TAM+1];       //Tabela que vai conter os dados
descritor desc[TAM/2+1]; //Tabela de descritores

int Hash( int c )
{
	return( c%(TAM/2)+1 );
}

void Screen()
{
	cout << "*----------------------------------*"<< endl;
	cout << "0 - Sair do programa (PRIORITY)"     << endl;
	cout << "1 - Inserir  Dado na Tabela"         << endl;
	cout << "2 - Procurar Dado na Tabela"         << endl;
	cout << "3 - Apagar Dado da Tabela"         << endl;
	cout << "4 - Imprimir toda a Tabela"          << endl;
	cout << "*----------------------------------*"<< endl;
	cout << "Opcao: ";
}

void Initialize()
{
	int i;

	for(i=1;i<=TAM;i++)
	{
		if (i <= (TAM/2) )
		{
			desc[i].prim = 0; desc[i].ult  = 0;
		}
		tab[i].num  = 0; tab[i].ant  = 0;
		tab[i].prox = 0; tab[i].datnasc = 0;
	}
}

//Procura a proxima posicao igual a zero
int SearchForZero()
{
	int i=1;

	while ( i )
	{
		if (i > TAM)    //Estourou a capacidade da tabela???
			return 0;
		else
		{
			if ( tab[i].num != 0 )
				i++;
			else return i;
		}
	}
	return 0;
}

//Imprimere toda a tabela e, se desejar, imprime tambem a tabela de descritores
void FullPrint()
{
	int i;
cout << "*---------------------TABELA---------------------*"<<endl;
cout << "i   Num     Nome        Nascimento      Prox   Ant" <<endl;
	for(i=1;i<=TAM;i++)
	{
		cout << i <<setw(5)<< tab[i].num<< setw(14)<<tab[i].nome
			 <<setw(11)<<tab[i].datnasc<<setw(11)<<tab[i].prox
			 <<setw(6)<<tab[i].ant<<endl;
	}
	getchar(); getchar();

#ifdef DESCR
		cout << "*--DESCRITOR--*"<<endl;
	cout <<"i   PRIM   ULT"<<endl;
	for(i=1;i<=TAM/2;i++)
		cout <<	i <<"   "<<desc[i].prim<<"      "<<desc[i].ult<<endl;
#endif
}

//Constroi a tabela inserindo registros na primeira posicao livre encontrada
// a partir do incio da tabela
void Build ()
{
	int numero, indice;

	cout << "Digite \"0\" (zero) para sair"<<endl;
	cout << "Numero: " ; cin >> numero;

	//Procura a proxima posicao na qual deve ser inserida o registro
	indice = SearchForZero();
	if( indice && numero )
	{
		if( desc[Hash(numero)].prim == 0 )
		{
			desc[Hash(numero)].prim = indice;
			tab[indice].num = numero;
			cout << "Nome (max. 10 caracteres): ";
			cin>>tab[indice].nome;
			cout << "Data de Nascimento (DDMMAA): ";
			cin>>tab[indice].datnasc;
			indice = SearchForZero();
			cout << "Construcao terminou com sucesso!!"<< endl;
		}
		else
		    {
			if (desc[Hash(numero)].ult!=0)
			{ //Se entrar aqui significa que existe um ultimo noh qu
			  //e cujo prox deve ser atualizado....
		         	tab[desc[Hash(numero)].ult].prox = indice;
				//...e ant tambem
				tab[indice].ant = desc[Hash(numero)].ult;
			}
			else
			   {
				tab[desc[Hash(numero)].prim].prox = indice;
				tab[indice].ant = desc[Hash(numero)].prim;
			   }
			
			if (numero!=0)
			{
			 desc[Hash(numero)].ult = indice; //Atualiza descritor e
			 tab[indice].num = numero; 	 //...insere na tabela.
			 cout << "Nome (max. 10 caracteres): ";
			 cin>>tab[indice].nome;
			 cout << "Data de Nascimento (DDMMAA): ";
			 cin>>tab[indice].datnasc;
			 indice = SearchForZero();
			 cout << "Construcao terminou com sucesso!!"<< endl;  
			}
		    }
	}//do if
	if ( !indice )
		cout << "Sua tabela jah foi preenchida!!!\a"<<endl;
}//da procedure Build

//Apaga um registro da tabela
void Exclude()
{
	int numero,proximo,anterior,i; //A variavel 'proximo' poderia ser 
	//reaproveitada mas por questoes de entendimento do codigo fonte usarei
	//a variavel 'anterior'				     

	cout << "Digite o numero que deseja apagar: "; cin >> numero;

	//Eh o primeiro???....
	if ( tab[desc[Hash(numero)].prim].num == numero )
	{//Entao o DESC.PRIM deve ser atualizado com o valor do campo
	 // PROX para o qual o DESC.PRIM aponta. E o anterior do proximo deve
	 // ser zero;
		proximo = tab[desc[Hash(numero)].prim].prox;
		//Atualizando a tabela
		tab[desc[Hash(numero)].prim].num = 0;
		tab[desc[Hash(numero)].prim].prox = 0;
		tab[desc[Hash(numero)].prim].datnasc = 0;
		tab[proximo].ant = 0;
		//Atualizando a tabela de descritores
		desc[Hash(numero)].prim = proximo;
		//Caso particular: Se o ultimo for igual ao primeiro na tabela 
		//de descritores significa que eu apaguei um noh de dois 
		//encadeados, por tanto nao haverah mais um ultimo noh...
		if ( desc[Hash(numero)].ult == desc[Hash(numero)].prim ) 
			desc[Hash(numero)].ult = 0;
	}
	else
	{	//Eh o ultimo???.....
		if( tab[desc[Hash(numero)].ult].num == numero )
		{//Entao o DESC.ULT deve ser atualizado com o valor do campo
		 // ULT para o qual o DESC.ULT aponta. E o proximo do anterior
		 // ser zero;		
			anterior = tab[desc[Hash(numero)].ult].ant;
			//Atualizando a tabela
			tab[desc[Hash(numero)].ult].num = 0;
			tab[desc[Hash(numero)].ult].ant = 0;
			tab[desc[Hash(numero)].ult].datnasc = 0;
			tab[anterior].prox = 0;
			//Atualizando a tabela de descritores
			desc[Hash(numero)].ult = anterior;

			//Caso particular: Se o ultimo for igual ao primeiro
			//na tabela de descritores significa que eu apaguei um 
			//noh de dois encadeados, por tanto nao haverah mais 
			//um ultimo noh...
			if ( desc[Hash(numero)].ult == desc[Hash(numero)].prim )
				desc[Hash(numero)].ult = 0;
		}
		else //Entao pode estar no meio do caminho....
		{
			anterior = 0; //Controlarah se encontrou (=1) ou nao(0)
				      // o numero que serah excluido
			i = desc[Hash(numero)].prim;
			while ( i )   //Procurando.....
			{
				if( tab[i].num == numero ) //Encontrou???
				{
					tab[i].num = 0;
					tab[tab[i].ant].prox = tab[i].prox;
					tab[tab[i].prox].ant = tab[i].ant;
					tab[i].prox = 0;
					tab[i].ant = 0;
					tab[i].datnasc = 0;
					i = 0; anterior++; //Encontrou!!!!
				}
				else i = tab[i].prox;//..nao, entao vai para o
						     //proximo...
			}// do while
		}// do else
	}//do else
	if ( anterior )//Conseguiu encontrar???
		cout << "Dado apagado com sucesso!!\a" << endl;
	else 
		cout << "Huston...We have a problem... o dado nao foi apagado"
		     << " pois nao foi encontrado!\a"<<endl;
}// da procedure;

//Procura numero na tabela
int Search( int numero )
{
	//Numero eh o primeiro?
	//Sim ==> imprime na tela
	//Nao ==> Numero eh o ultimo?
	//        Sim ==> imprime na tela
	//        Nao ==> Pode estar no meio, procura na tabela
	int i, encontrou=0;
	
  if ( numero )
  {
	if( tab[desc[Hash(numero)].prim].num == numero) 
	{
		cout << "Esse registro foi encontrado!!!\a" << endl;
		//No descritor temos o índice da tabela:
		cout << "Índice da Tabela: " << desc[Hash(numero)].prim << endl;
		cout << "Número: " << numero << endl;
		cout << "Nome: " << tab[desc[Hash(numero)].prim].nome << endl;
		cout<<"Indice do Proximo: "<< tab[desc[Hash(numero)].prim].prox 
		    << endl;
		cout<<"Indice do Anterior: "<< tab[desc[Hash(numero)].prim].ant 
	            << endl;
		encontrou++;
	}
	else
		if ( tab[desc[Hash(numero)].ult].num == numero ) 
		{
			cout << "Esse registro foi encontrado!!!\a" << endl;
			cout << "Indice da tabela: " << desc[Hash(numero)].ult
			     << endl;
			cout << "Numero: " << numero << endl;
			cout << "Nome: " << tab[desc[Hash(numero)].ult].nome
			     << endl;
			cout << "Indice do Proximo: "
			     <<tab[desc[Hash(numero)].ult].prox << endl;
			cout << "Indice do Anterior: "
			     <<tab[desc[Hash(numero)].ult].ant << endl;
			encontrou++;
		}
		else
		{//Procurando entre o primeiro e o ultimo
			i = tab[desc[Hash(numero)].prim].prox;
			//Procurando.......
			while ( i )
			{
				//Encontrou????
				if ( tab[i].num == numero )
				{
					//Sim...
					cout << "Esse registro foi encontrado!"
					     <<"!!\a"<< endl;
					cout << "Indice da tabela: "<<i<<endl;
					cout << "Numero: " <<numero<< endl;
					cout << "Nome: "<<tab[i].nome<<endl;
					cout<<"Indice do Proximo: "<<tab[i].prox
					    << endl;
					cout<<"Indice do Anterior: "<<tab[i].ant
					    << endl;
					encontrou++; i=0;
				}
				else i = tab[i].prox;
			}//do While
		}
   }
	if ( !encontrou ) 
		return 0;
	else return -1;
}//da procedure Search;

int main()
{
	int opt=1,numero;

	Initialize();
	cout << endl;
cout << "Bem-Vindo ao TABELA INSEREITOR APAGEITOR PROCUREITOR PRINTEITOR PLUS"
       <<"\n----- TIAPPP 2003 -----" << endl;
  cout << "Ver. 2.0000542.123.45-433y - FINAL" << endl;
  cout << "By PSMJ(TM) FreeSoftWare Corp. e TABAJARA(R) 2003 Inc." << endl;
	Screen();
	while( opt )
	{
		cin >> opt; cout << endl;
		switch(opt)
		{
			case 0: cout << "FIM!!! - Bugs, Sugestoes e Reclamacoes"
				     << " 0800 - 010010010010111 ou 0300 - 0FFh"
				     << endl;
				break;
			case 1: cout << endl << endl;
				cout << "OPCAO 1 - INSEREITOR" << endl;
				Build(); 
				cout << endl;
				Screen();
				break;
			case 2: cout << endl << endl;
				cout << "OPCAO 2 - PROCUREITOR" << endl;
				cout <<"Numero que deseja procurar na Tabela: ";
				cin >> numero;
				if ( !Search( numero ) )
					cout << "Huston...We have a problem!!"
					     << "\a Seu registro nao foi "
					     << "encontrado!"<<endl;
				getchar(); cout << endl;
				Screen();
				break;
			case 3: cout << endl << endl;
				cout << "OPCAO 3 - APAGEITOR" << endl;
				Exclude();
				getchar();getchar();
				Screen();
			       	break; 
			case 4: cout << endl << endl;
				cout << "OPCAO 4 - PRINTEITOR" << endl;
				FullPrint();
				cout << endl; 
				getchar(); cout << endl;
				Screen();
				break;
			default: cout << "Tsi...tsi..Sinto muito mas esta opcao"
				      << " nao existe...\a"<< endl << endl;
				 Screen();
				 break;
		}
	}
	
	return 0;
}
