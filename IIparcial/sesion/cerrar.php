<?php 
	if (isset($_SESSION["usuario"])) {
		unset($_SESSION["usuario"]);
		unset($_SESSION["tipo"]);
	}

	header("location:inicio.php");

 ?>