<?php session_start(); ?>

<html>
<head>
	<meta charset = "UTF-8">
	<title>MATRIZ</title>
	<link rel="stylesheet" type="text/css" href="estilos.css" />
	
</head>
<body>
	<?php
		if (!isset($_SESSION["Mat"])) {
			for ($i=0; $i <8 ; $i++) {
				for ($j=0; $j <8 ; $j++) {
					$mat[$i][$j]=rand(1,5);
					$cont[$i][$j]=0;
				}
			}

			$_SESSION["Mat"]=$mat;
			$_SESSION["Cont"]=$cont;

		}else{

			$mat = $_SESSION["Mat"];
			$cont = $_SESSION["Cont"];

		}
	 ?>

	<?php
		if (isset($_GET["fil"]) && isset($_GET["col"])) {
			$_SESSION["Cont"][$_GET["fil"]][$_GET["col"]]++;
			$_SESSION["Mat"][$_GET["fil"]][$_GET["col"]] = "*";
			$mat = $_SESSION["Mat"];
			$cont = $_SESSION["Cont"];
		}
	?>


	<script type="text/javascript">
		function cargar(fila,col){
			document.location = "matriz.php?fil="+fila+"&col="+col;
		}

		function comprobar(){
			alert("holaaa entro a comprobar");
		}

	</script>

	<table>
		<?php
			for ($i=0; $i <8 ; $i++) {
				echo "<tr>";
				for ($j=0; $j <8 ; $j++) {
					//echo "<td class='caja'  onclick='cargar(".$i.",".$j."); comprobar();'>",$mat[$i][$j],"</td> ";
					if($mat[$i][$j]== "*"){
						echo "<td class='caja'  onclick='cargar(".$i.",".$j.");'>*</td> ";
					}else {
						echo "<td class='caja'  onclick='cargar(".$i.",".$j.");'></td> ";
					}

					//echo "<td> <a onclick='cargar(".$1.",".$j.");'><img src=img/",$mat[$i][$j],".jpg/></td>";
				}
				echo "</tr>";
			}

		 ?>
	</table>

	<table>
		<?php
		echo "<tr>";
		echo "<tr>";
		echo "<tr>";
		echo "<tr>";
			for ($i=0; $i <8 ; $i++) {
				echo "<tr>";
				for ($j=0; $j <8 ; $j++) {
					echo "<td>",$cont[$i][$j],"</td>";
				}
				echo "</tr>";
			}
		 ?>
	</table>

</body>
</html>
