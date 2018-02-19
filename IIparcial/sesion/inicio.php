<?php session_start();?>
<html>
<head>
	<meta charset="UTF-8">
	<title>INICIO</title>
</head>
<body>	
	<form name="form1" action="" method="post">
		<fieldset>
			<legend> INICION  DE SESION</legend>
			<label>USUARIO: </label>
			<input type="text" name="usuario">
			<label>CLAVE:</label>
			<input type="password" name="clave">
			<input type="submit" name="boton" value="aceptar">
		</fieldset>   
	</form>
	<?php 
		if (isset($_POST["boton"])) {
			if ($_POST["usuario"]=="mariandrea"&&$_POST["clave"]==123) {

				$_SESSION["usuario"]=$_POST["usuario"];
				$_SESSION["tipo"]=1;
				header("location:principal.php");
			}
			else {
				echo "no coinciden los datos";
			}
		}
	 ?>
</body>
</html>