<?php session_start();
	//si la variable usuario no existe
	// entonces lo redirecciona a inicio.php para que inicie sesion
	if (!isset($_SESSION["usuario"])) {
		header("location:inicio.php");
	}

 ?>

 <html>
 <head>
 	<meta charset="UTF-8">
 	<title>DOCUMENT</title>
 </head>
 <body>
 	<h1>BIENVENIDO
 		<?php 
 			echo $_SESSION["usuario"],"Rol:",$_SESSION["tipo"];
 		 ?>
 	</h1>
 	<a href="cerrar.php">SALIR</a>
 </body>
 </html>