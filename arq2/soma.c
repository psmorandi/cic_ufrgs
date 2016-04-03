#include <stdio.h>


int main(){

 int ini, ini2, fim, s = 0;

printf("Digite o inicio e o fim da soma:\n");
scanf("%d %d",&ini,&fim);

ini2 = ini; /*para imprimir no fim o valor de inicio*/

if (ini > fim) printf("Fim deve ser maior que o inicio!!");
else{


 loop:
      if (ini <= fim){
      s += ini;
      ++ini;
      goto loop;
      }
      printf("Soma de %d ateh %d: %d",ini2,fim,s);
}
 
return 0;

}