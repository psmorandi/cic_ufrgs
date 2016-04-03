/**
 * A classe dos Racionais implementa a manipulação de números racionais que 
 * tem como tipo primitivo um inteiro. Um obtjeto do tipo Racional contem dois 
 * campos (denominador e numerador) do tipo int. 
 * <p>
 * Adicionalmente, esta classe provê métodos de conversão dos Racionais em 
 * String e String em Racionais, e outros médotos úteis quando se está 
 * trabalhando com Racionais (soma, subtração, comparação ...).
 *
 * @author	Mairo Pedrini
 * @author	Paulo S&eacute;rgio Morandi J&uacute;unior
 * @version	0.1&beta;, %G%
*/ 
public class Racional 
{
	private int num; //Numerador
	private int den; //Denominador

	/** 
	 * Constrói uma nova alocação de um objeto Racional, com valor inicial 
         * igual a 0 
	 * @see #Racional( int, int )
	 * @see #Racional( int )
	 * @see #Racional( java.lang.String )
	 */
	public Racional() 
	{ 
		num=0;
		den=1;
	}

	/**Constrói uma nova alocação de um objeto Racional que representa um 
	 * número racional: num/den, onde num e den são int
	 * @param num Numerador
	 * @param den Denominador
	 * @throws ArithmeticException Se den é 0 (division by zero)
	 * @see #Racional()
	 * @see #Racional( int )
	 * @see #Racional( java.lang.String )
	 * 
	 */
	public Racional( int num, int den ) throws ArithmeticException
	{
		if (den == 0)
			throw new ArithmeticException("Division by zero");
		
		this.num=num;
		this.den=den;
	}

	/**Constrói uma nova alocação de um objeto Racional que representa como
	 * um número raciona um tipo primitivo int
	 * num 
	 * @param num o valor inteiro a ser guardado como Racional
	 * @see #Racional()
	 * @see #Racional( int, int )
	 * @see #Racional( java.lang.String )
	 */
	public Racional( int num )
	{
		this( num, 1 );
	}

	/** Constrói uma nova alocação de um objeto Racional que será 
	 * representado pelo valor da String 
	 * @param s a string que será convertida para um racional ("1/2", "2" são exemplos de strings válidos)
	 * @throws NumberFormatException se o fomrato não for um formato de número racional válido
	 * @throws ArithmeticException se a string convertida em Racional tiver denominador 0
	 * @see #Racional()
	 * @see #Racional( int )
	 * @see #Racional( int, int )
	 */
	public Racional( String s ) throws NumberFormatException, ArithmeticException
	{
		if (s == null || s.trim().equals(""))
			throw new NumberFormatException("Not a valid rational number");
		
		s.trim();
		int pos = s.indexOf('/');
		if (pos == -1)
		{
			num = Integer.parseInt(s.substring(0, s.length()));
			den = 1;
		}
		else
		{
			num = Integer.parseInt(s.substring(0, pos));
			den = Integer.parseInt(s.substring(pos+1, s.length()));
			if (den == 0)
				throw new ArithmeticException("Division by zero");
		}
	}
	
	/**
	 * Retorna o numerador do número Racional
	 * @return o numerador desse número racional
	 */
	public int numerador() { return num; }
	/**
	 * Retorna o denominador do número Racional
	 * @return o denominador desse número racional
	 */
	public int denominador() { return den; }

	/**
	 * Adiciona ao número racional outro número racional.
	 * @param rac o número racional a ser adicionado
	 * @see #soma( int )
	 */
	public void soma( Racional rac )
	{
		
		num = num*rac.denominador() + den*rac.numerador();
		den = den*rac.denominador();
		if (num == 0)
			den = 1;
	}

	/**
	 * Adiciona ao número racional um inteiro
	 * @param i o inteiro a ser adicionado
	 * @see #soma( Racional )
	 */
	public void soma( int i )
	{
		num = num + den*i;
	}
	
	/**
	 * Subtrái do Racional outro número racional
	 * @param rac o número racional a ser subtraído
	 * @see #sub( int )
	 */
	public void sub( Racional rac ) 
	{
		num = num*rac.denominador() - den*rac.numerador();
		den = den*rac.denominador();
		if (num == 0)
			den = 1;
	}
	
	/**
	 * Subtrái do Racional um inteiro
	 * @param i o inteiro a ser subtraído do racional
	 * @see #sub( Racional )
	 */
	public void sub( int i )
	{
		num = num - den*i;
	}
	/**
	 * Multiplica dois números racionais
	 * @param rac o número racional a ser multiplicado
	 * @see #mul( int )
	 * */
	public void mul( Racional rac )
	{
		num = num*rac.numerador();
		den = den*rac.denominador();
		if (num == 0)
			den = 1;
	}
	/**
	 * Multiplica o racional por um inteiro
	 * @param i o número inteiro que será multiplicado
	 * @see #mul( Racional )
	 * */
	public void mul( int i )
	{
		num = num*i;
		if (num == 0)
			den = 1;
	}
	/**
	 * Divide dois números racionais
	 * @param rac o número racional a ser dividido
	 * @throws ArithmeticException se o numerador de rac for 0
	 * @see #div( int )
	 * */
	public void div( Racional rac ) throws ArithmeticException
	{
		if (rac.numerador() == 0)
			throw new ArithmeticException("Division by zero");
		
		num = num*rac.denominador();
		den = den*rac.numerador();
		if (num == 0)
			den = 1;
	}
	/**
	* Divide o racional por um inteiro
	* @param i o número inteiro que será dividido pelo racional
	* @throws ArithmeticException se o inteiro for 0
	* @see #div( Racional )
	* */	
	public void div( int i ) throws ArithmeticException
	{
		if (i == 0)
			throw new ArithmeticException("Division by zero");
		
		den = den*i;
	}

	/**
	 * Retorna um objeto String que representa este número Racional.
	 * O racional é apresentado na tela no formato "(sinal)int/int" caso 
	 * não se encaixe em nenhum dos seguintes casos:<br>
	 * Caso o número seja um inteiro representado como racional ( 3/1 
	 * por exemplo) o mesmo é apresentado na tela como um inteiro sem
	 * o denominador 1. Se o número for menor do que zero, inverte-se o
	 * sinal do numerador e do denominador ( 3/-4 resulta em -3/4).
	 * @return uma representação em string desse número racional no formato int/int. */ 
	public String toString()
	{
		if ( den < 0 )
		{
			den *= -1;
			num *= -1;
		}
		
		if (num == 0)
			return new String("0");
		else if (num == den)
			return new String("1");
		else if (den == 1)
			return new Integer(num).toString();
		else
			return new String(num + "/" + den);
	}

//Comparacoes
	/**
	 * Indica se algum objeto o é igual a esse.
	 * @return <i>true</i> se forem iguais </br> <i>false</i> se forem diferentes
	 * @see #greatThan( Racional )
	 * @see #greatEqualThan( Racional )
	 * @see #lessThan( Racional )
	 * @see #lessEqualThan( Racional )
	 * */
	public boolean equals(Object o)
	{
		if (o == null)
			return false;
		if (!(o instanceof Racional))
			return false;
		Racional r = (Racional)o;
		return ( (num*r.denominador() == den*r.numerador()) );
	}
	/**
	 * Indica se o racional rac é maior que esse.
	 * @return <i>true</i> se esse for maior que rac </br> <i>false</i> caso contrário
	 * @see #equals( java.lang.Object )
	 * @see #greatEqualThan( Racional )
	 * @see #lessThan( Racional )
	 * @see #lessEqualThan( Racional )
	 * */
	public boolean greatThan( Racional rac )
	{
		return ( (num*rac.denominador()) > (den*rac.numerador()) ); 
	}
	/**
	 * Indica se o rac é maior ou igual a esse.
	 * @return <i>true</i> se esse for maior ou igual a rac </br> <i>false</i> caso contrário
	 * @see #equals( java.lang.Object )
	 * @see #greatThan( Racional )
	 * @see #lessThan( Racional )
	 * @see #lessEqualThan( Racional )
	 * */
	public boolean greatEqualThan( Racional rac )
	{
		return ( equals(rac) || greatThan(rac) );
	}
	/**
	 * Indica se o rac é menor ou igual a esse.
	 * @return <i>true</i> se esse for menor ou igual a que rac </br> <i>false</i> caso contrário
	 * @see #equals( java.lang.Object )
	 * @see #greatThan( Racional )
	 * @see #greatEqualThan( Racional )
	 * @see #lessThan( Racional )
	 * */	
	public boolean lessEqualThan( Racional rac )
	{
		return ( !greatThan(rac) );  
	}
	/**
	 * Indica se o rac é menor que esse.
	 * @return <i>true</i> se esse for menor que rac </br> <i>false</i> caso contrário
	 * @see #equals( java.lang.Object )
	 * @see #greatThan( Racional )
	 * @see #greatEqualThan( Racional )
	 * @see #lessEqualThan( Racional )
	 * */
	public boolean lessThan( Racional rac )
	{
		return ( !greatEqualThan(rac) );
	}
}
