#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>

//Funcao INT 25h do DOS para leitura de setores de disco
#define DIS 0x25

typedef struct {
	unsigned char  jmp[3];
	unsigned char  OEM[8];
	unsigned short bytes_setor;
	unsigned char setor_cluster;
	unsigned short setor_reser;
	unsigned char n_FAT;
	unsigned short num_ent_raiz;
	unsigned short total_fat16;
	unsigned char media;
	unsigned short n_setor_fat;
	unsigned short setor_trilha;
	unsigned short n_cabecas;
	unsigned short set_hidden;
	unsigned long total_32;
	unsigned char n_drive;
	unsigned char reservado;
	unsigned char sinal_boot;
	unsigned short volume[2];
	unsigned char label[11];
	unsigned char tipo_sys_arq[8];

}BOOT;

typedef struct {

	char nome[8];
	char ext[3];
	unsigned char atributo;
	unsigned char reservado;
	unsigned char seg;
	unsigned short hora_min_seg;
	unsigned short data;
	unsigned short ult_acesso;
	unsigned short cluster_HI;
	unsigned short last_time_write;
	unsigned short last_date_write;
	unsigned short cluster_LO;
	unsigned long tam;
}ROOT;

void DiskRead()
{

   union REGS regs;
   char buffer[512];
   BOOT boot;
   ROOT root[512/sizeof(ROOT)];
   int i,j;
   long entrada;

   regs.h.al = 0x00;
   regs.x.cx = 0x01;
   regs.x.dx = 0x00;
   regs.x.bx = (int)&buffer[0];

   int86(DIS,&regs,&regs);

   memcpy( &boot, buffer, sizeof(BOOT) );

   entrada = boot.setor_reser + boot.n_setor_fat*boot.n_FAT;

//Lendo as informacoes das entradas da raiz

   regs.h.al = 0x00;
   regs.x.cx = 0x01;
   regs.x.dx = entrada;
   regs.x.bx = (int)&root[0];

   int86(DIS,&regs,&regs);

//Imprimindo as 4 primeiras entradas
   for(j=0;j<4;j++)
   {

		printf("----------------ENTRADA %i------------------\n",j+1);
		printf("Nome do Arquivo: ");
		for(i=0;i<8;i++)
			if ( root[j].nome[i] )
				printf("%c",root[j].nome[i]);

		printf(" ------> Extensao: ");
		for(i=0;i<3;i++)
		{
			if( root[j].ext[i] )
				printf("%c",root[j].ext[i]);
		}

		printf("\n");

		printf("Atributos do Arquivo: ");

		//L - apenas leitura
		//O - oculto
		//S - sistema
		//V - volume
		//D - Diretorio
		//A - Arquivado
		printf("%s-%s-%s-%s-%s-%s\n",
				root[j].atributo&1? "L":" ",
				root[j].atributo&2? "O":" ",
				root[j].atributo&4? "S":" ",
				root[j].atributo&8? "V":" ",
				root[j].atributo&16? "D":" ",
				root[j].atributo&32? "A":" ");

		printf("Ultimas Modificacoes: \n");
		printf("HORA  ------  DATA\n");
		printf("%02i:%02i      %02i/%02i/%02i\n",
				root[j].last_time_write>>11,
				(root[j].last_time_write>>5)&63,
				root[j].last_date_write&15,
				(root[j].last_date_write>>4)&15,
				( (root[j].last_date_write>>9) + 1980)%100 );

		printf("Tamanho: %10.2f Kb\n",(double)root[j].tam/1024);
		printf("Cluster inicial: %i\n",root[j].cluster_LO);
		getch();
	}
}


int main()
{
	clrscr();

	printf("Informacoes sobre os 4 primeiros setores do disquete\n");

	DiskRead();


	return 0;

}
