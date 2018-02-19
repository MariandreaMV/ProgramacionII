<?php
 session_start();
 include_once 'logica.php';
 ?>

<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <title>INICIO</title>
    <style type="text/css">
      fieldset , h1 {
        background-color: gray;
        text-align: center;
      }
    </style>
  <body>
    <h1>BIENVENIDO AL JUEGO DE LA VIEJA</h1>
    <form action="" method="post">
      <fieldset>
        <label> jugador x:
          <input type="text" name="jugadorX" value="">
        </label>
        <br>
        <label> jugador O:
          <input type="text" name="jugadorY" value="">
        </label>
        <br>
        <label>
          <input type="submit" name="cargar" value="empezar">
        </label>
        <?php

          if(isset($_POST["cargar"])){
            if(datosCorrectos()==1){
              header("location:juego.php");
            }else{
              echo "<script>alert('incorrect values')</script>";
            }
          }
        ?>
      </fieldset>
    </form>
  </body>
</html>
