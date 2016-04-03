#include <stdio.h>
#include <stdlib.h>

int eax, ebx, ecx, edx, mascara[4]={0x000000ff,0x0000ff,0x00ff,0xff};

/*Imprime na tela o nome do processador presente nos registradores*/
void decompoe ()
{
	int i,j;
	char nome[5];
	int palavra[3]={ebx, edx, ecx}; /*Na ordem que deve ser impresso*/

	printf("\nExemplo do uso da função cpuid\n");
	printf("Nome do Fabricante do Processador: ");
	for(i=0;i<3;i++)
	{/*Cada chamada do "i" eh um registrador*/
		
		for(j=0;j<5;j++)
		{
			/*Mascara para "pegar" os 8 bits finais*/
                        nome[j] = palavra[i] & 0xff;/*mascara[j];*/
			palavra[i] = palavra[i]>>8;
		}
		printf("%s",nome);		
	}
	printf("\n\n");

}

int main()
{
	int i;

__asm__ ("cpuid": 
		"=a" (eax),
                "=b" (ebx),
                "=c" (ecx),
                "=d" (edx)
            :   "a" (0x00));


decompoe();

return 0;
}
