<?php session_start();
	  include_once 'logica.php';
		echo "<h1>LA VIEJA</h1>";
		echo "<h3>JUGADOR X: ",$_SESSION["jX"],"</h3>";
		echo "<h3>JUGADOR 0: ",$_SESSION["jY"],"</h3>";
		if(isset($_POST["reiniciar"])){
			generarMatriz(3);
		}else{
			if (!isset($_SESSION["Mat"])) {
				generarMatriz(3);
			}else{
				capturaVariablesURL();
			}
		}
?>

<html>
<head>
	<meta charset = "UTF-8">
	<title>MATRIZ</title>
	<link rel="stylesheet" type="text/css" href="estilos.css" />
	<script type="text/javascript" src="scripts.js"></script>
</head>
<body>
	<table> <?php imprimirMatriz(); ?> </table>
	<form action="" method="post">
		<br>
		<input type="submit" name="reiniciar" value="reiniciar partida">
	</form>
</body>
</html>
