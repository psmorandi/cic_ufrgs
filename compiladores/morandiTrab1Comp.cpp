//------------------------------------------------------------------------------
//INF01147 - Compiladores - Trabalho 1
//Prof. Jo�o Comba
//Aluno: Paulo S�rgio Morandi J�nior - 2767/01-1
//PsMj FreeSoftware (R) C-PageNumbering 2004-1
//------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <time.h>

#define MAXPAGE 50  //n�mero m�ximo de linhas em uma p�gina

using namespace std;

//------------------------------------------
//Devolve o nome do arquivo sem extensao...
// S� para salvar como "nomeSemExtensao.txt"
//------------------------------------------
char * arqNome( char *nomeComExtensao ) 
{
    int j,i=0;
    char *nomeSemExtensao;
    
    while (nomeComExtensao[i] != '.')
     i++;
    
    nomeSemExtensao = (char *)malloc(i);
    for (j=0;j<i;j++)
        nomeSemExtensao[j] = nomeComExtensao[j];
        
   return nomeSemExtensao;
}

int main( int argc, char **argv)
{
	ifstream arq;
	ofstream saida;
	time_t times;  //Estrutura que vai armazenar a data do cabe�alho...

	char *cab = "//INF01147 - Compiladores - Trabalho 1\n//Prof. Jo�o Comba\n//Aluno: Paulo S�rgio Morandi J�nior - 2767/01-1\n//PsMj FreeSoftware (R) C-PageNumbering 2004-1\n";
	char *pg = "PAGE";
	char *nomeTXT;
	char read;
	int line=0, page=0; //Contadores de p�ginas e linhas...

	if (argc == 1) //Se Nenhum par�metro foi digitado....
	{
		cout << "PsMj FreeSoftware (R) C-PageNumbering 2004-1" << endl;
		cout << "PsMj(TM) Corp. 1981-2004 (c) " << endl;
		cout << "-----------------------------------------------------" << endl;
		cout << "Usage: ident file.c" << endl << endl;
	}
	else
	{
		arq.open( argv[1] ); //Primeiro argumento � o nome do exec. o segundo
		                     //o nome do Arquivo que deseja-se numerar...
		if ( !arq )          //Verifica se conseguiu abrir o arquivo...
			cout << "Erro: " << argv[1] << " - Arquivo nao encontrado" << endl;
		else
		{
   			time(&times);    //Salava em times a data e as horas....
			line=1; page=1;
			
			nomeTXT = arqNome( argv[1] );
			strcat(nomeTXT,".txt");
			
			//Abre o arquivo e coloca os cabe�alhos principais:
			saida.open(nomeTXT);
			saida << cab << endl;
			saida << pg << " " << page << "   " << argv[1] << "  " << ctime(&times) << endl;
            saida << "    " << line << ":   ";
            
			while (arq) //Enquanto n�o for fim de arquivo....
			{
				read = arq.get(); //Le caracter por caracter...
				
                if (read != EOF) 
                {
                    saida << read;
				    if (read == '\n')  //Se for enter....
                    {
                        line++;     //...incrementa linha....
                        if ( ( line % MAXPAGE ) == 0 )  // se linha for m�ltiplo de 50...
                        {
                           page++; // ... nova pagina...
                           saida << endl 
                                 << pg << " " << page << "   " << argv[1] 
                                 << "  " << ctime(&times) << endl;
                           //...ctimes imprime a data no formato 
                           // "Wed Mar 17 19:36:43 2004"
                       }
                       saida << "    " << line << ":   ";
                   }
               }// do if EOF
            }//do While
			saida.close();
		}
		arq.close();
	}
	return 0;
}
