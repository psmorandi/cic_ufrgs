public class Teste{
public static void main( String args[] )
{
	Racional x = new Racional("2/3");
	Racional y = new Racional(3);
	Racional z = new Racional(3,4);
	Racional teste = new Racional(0);
//	Racional erro1 = new Racional(1,0);
//	Racional erro2 = new Racional("1/0");
	Racional possivel_erro = new Racional("0/1");
	Racional r;

        System.out.println("TESTANDO AS INICIALIZCOES");
	System.out.println("-------------------------------\n");
	
	r = new Racional();
	System.out.println("Valor inical de r = "+r);

//Imprimindo os racionais
	System.out.println("teste = "+teste);
	System.out.println("x = "+x);
	System.out.println("y = "+y);
	System.out.println("z = "+z);
	System.out.println("possivel_erro = " + possivel_erro);

//Usando os metodos
	System.out.println("\nTESTANDO OS METODOS");
	System.out.println("-------------------------------\n");
	System.out.print(x+" + "+ y +" = ");
	x.soma(y);
	System.out.println(x);
	
	System.out.print(z+" - "+ x +" = ");
	z.sub(x);
	System.out.println(z);
	
	System.out.print(x+" / "+ z +" = ");
	x.div(z);
	System.out.println(x);
	
	System.out.print(z+" * "+ y +" = ");
	z.mul(y);
	System.out.println(z);

	if ( x.equals(y) )
		System.out.println(x+" and "+ y +" are equals!");
	else System.out.println(x+" and "+ y +" aren't equals!");
	if ( x.greatThan(y) )
		System.out.println(x+" > "+ y);

	x = new Racional(3,4);
	y = new Racional("3/4");

	if ( x.greatEqualThan(y) )
		System.out.println(x+" >= "+ y);

	
}}
