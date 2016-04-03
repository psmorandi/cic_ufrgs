#include <iostream.h>

int dia[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

int bis( long dat)
{
   return ( (dat % 4) == 0);
}

void decompoe( char *d, long& dia, long& mes, long& ano )
{
  dia = 10 * d[0] + d[1] - 528;
  mes = 10 * d[3] + d[4] - 528;
  ano = 1000 *long(d[6]) + 100 * d[7] + 10 * d[8] + d[9] - 53328;
}

int valida(long dd, long mm, long aaaa)
{
if ((dd <= 0) || (dd > 31) || (mm <= 0) || (mm > 12) || (aaaa < 1900) ||
   (aaaa > 2100))
   return 0;
else  {
	  if (mm == 2)  {
		 if (bis(aaaa)) {
						if (dd <= 29) return 1;
						else return 0;
						}
		 else {
			  if (dd >= 29) return 0;
			  else return 1;
			  }
		 }
	  else {
		   if (dd > dia[mm - 1]) return 0;
		   else return 1;
		   }
	  }
}

int main()
{
	long dd, mm, aaaa, j, i, dpass = 0;
	long semana;
	char date[10];

	cout << "\nEntre com a data (01/01/2002): "; cin >> date;
	decompoe(date, dd, mm, aaaa);
if (valida(dd,mm,aaaa) != 0) {
	for(i = 1900, j = 0; i <= aaaa; i++)
		if (bis(i)) j++;
	for(i = (mm - 1); i <= 11; i++) 
		dpass += dia[i];
	semana = ((aaaa - 1900)*365 - dpass + dd + j) % 7;
	switch (semana)
	{
		 case 0: cout << "Dia da semana = domingo" << endl;
				 break;
		 case 1: cout << "Dia da semana = segunda" << endl;
				 break;
		 case 2: cout << "Dia da semana = terca" << endl;
				 break;
		 case 3: cout << "Dia da semana = quarta" << endl;
				 break;
		 case 4: cout << "Dia da semana = quinta" << endl;
				 break;
		 case 5: cout << "Dia da semana = sexta" << endl;
				 break;
		 case 6: cout << "Dia da semana = sabado" << endl;
				 break;
	}
}
  else cout << "Data invalida!" << endl;
  cout << endl;
	
	return 0;
}
