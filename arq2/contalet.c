#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX 100

int main(){

	int i, cont[26]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; /*Inicializa vetor com zero*/
	char texto[MAX]={'0',},let='A';

	printf("Digite um texto de no maximo %d:\n",MAX);
	gets(texto);

	for(i=0;i<100; i++){

	    switch( texto[i] ){
			case 'A':  	cont['A'-'A']++;
					break;
			case 'B':  	cont['B'-'A']++;
					break;
			case 'C':  	cont['C'-'A']++;
					break;
			case 'D':  	cont['D'-'A']++;
					break;
			case 'E':  	cont['E'-'A']++;
					break;
			case 'F':  	cont['F'-'A']++;
					break;
			case 'G':  	cont['G'-'A']++;
					break;
			case 'H':  	cont['H'-'A']++;
					break;
			case 'I':  	cont['I'-'A']++;
					break;
			case 'J':  	cont['J'-'A']++;
					break;
			case 'K':  	cont['K'-'A']++;
					break;
			case 'L':  	cont['L'-'A']++;
					break;
			case 'M':  	cont['M'-'A']++;
					break;
			case 'N':  	cont['N'-'A']++;
					break;
			case 'O':  	cont['O'-'A']++;
					break;
			case 'P':  	cont['P'-'A']++;
					break;
			case 'Q':  	cont['Q'-'A']++;
					break;
			case 'R':  	cont['R'-'A']++;
					break;
			case 'S':  	cont['S'-'A']++;
					break;
			case 'T':  	cont['T'-'A']++;
					break;
			case 'U':  	cont['U'-'A']++;
					break;
			case 'V':  	cont['V'-'A']++;
					break;
			case 'W':  	cont['W'-'A']++;
					break;
			case 'X':  	cont['X'-'A']++;
					break;
			case 'Y':  	cont['Y'-'A']++;
					break;
			case 'Z':  	cont['Z'-'A']++;
					break;
			case 'a':  	cont['a'-'a']++;
					break;
			case 'b':  	cont['b'-'a']++;
					break;
			case 'c':  	cont['c'-'a']++;
					break;
			case 'd':  	cont['d'-'a']++;
					break;
			case 'e':  	cont['e'-'a']++;
					break;
			case 'f':  	cont['f'-'a']++;
					break;
			case 'g':  	cont['g'-'a']++;
					break;
			case 'h':  	cont['h'-'a']++;
					break;
			case 'i':  	cont['i'-'a']++;
					break;
			case 'j':  	cont['j'-'a']++;
					break;
			case 'k':  	cont['k'-'a']++;
					break;
			case 'l':  	cont['l'-'a']++;
					break;
			case 'm':  cont['m'-'a']++;
					break;
			case 'n':  	cont['n'-'a']++;
					break;
			case 'o':  	cont['o'-'a']++;
					break;
			case 'p':  	cont['p'-'a']++;
					break;
			case 'q':  	cont['q'-'a']++;
					break;
			case 'r':  	cont['r'-'a']++;
					break;
			case 's':  	cont['s'-'a']++;
					break;
			case 't':  	cont['t'-'a']++;
					break;
			case 'u':  	cont['u'-'a']++;
					break;
			case 'v':  	cont['v'-'a']++;
					break;
                        case 'w':       cont['w'-'w']++;
                                        break;
			case 'x':  	cont['x'-'a']++;
					break;
			case 'y':  	cont['y'-'a']++;
					break;
			case 'z':  	cont['z'-'a']++;
					break;
		}
	}
	printf("Resultados: \n");
	for (i=0;i<26;i++)
		printf("\t%c = %d\n",let+i,cont[i]);
	printf("\n");

	return 0;

}
