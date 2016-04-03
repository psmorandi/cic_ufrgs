<html>
 <head>
  <title>PHP Teste</title>
 </head>
 <body>
 <?php 

function http_request ($url) {
	
	$parseURL = parse_url ($url);
	$porta = $parseURL ['port'];
	
	$address = gethostbyname ($parseURL['host']);
	

/* Create a TCP/IP socket. */
	$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
	if ($socket < 0) {
	   echo "socket_create() failed: reason: " . socket_strerror($socket) . "\n";
	} else {
	   echo "OK.\n";
	}


	
	$result = socket_connect($socket, $address, $porta);
	if ($result < 0) {
	   echo "socket_connect() failed.\nReason: ($result) " . socket_strerror($result) . "\n";
	} else {
	   echo "OK.\n";
	}

	$in = "GET / HTTP/1.1\r\n";
	$in .= "Host: ";
	$in .= $address . "\r\n";
	$in .= "Connection: Close\r\n\r\n";
	$out = ''; 
	$resposta = '';
	
	echo "Sending HTTP HEAD request...\n";
	socket_write($socket, $in, strlen($in));
	echo "OK.\n";
	
	echo "Receive some.. <br>";
	while($out = socket_read($socket,1024) ) {
		$resposta .= $out;
	}

	ereg("HTTP/([0-9]\.[0-9]).*Date: ([^\r\n]*).*Content-Length: ([0-9]*).*<title>([^<]*)</title>", $resposta, $regs);
	
	echo "Versão do Protocolo: " . $regs[1] . "<br>";
	echo "Data de recuperação: " . $regs[2] . "<br>"; 
	echo "Título da Página: " . $regs[4] . "<br>";
	echo "Tamanho total de bytes transferidos: " . strlen($resposta) . " bytes <br>";
		
	
	echo "Closing socket...";
	socket_close($socket);
	echo "OK.\n\n";

}

if (!isset($_POST ['url'])) {
?>
<form action="http.php" method="post">
	URL a ser obtida: 
	<input type="text" name="url">
	<input type="submit" value="enviar">
</form>

<?

} else {

	$url = $_POST ['url'];

	http_request ($url);

}
 ?>



</body>
</html>
