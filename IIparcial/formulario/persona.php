

<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <title>persona.php</title>
  </head>
  <body>
    <h1>HOLA
      <?php
        echo $_POST["ok"];
       ?>
    </h1>
  </body>
</html>

<?php
  if(isset($_POST ["ok"]) && isset($_POST["EC"]) ){
    echo $_POST ["ok"];
    echo "<br>";
    echo $_POST["apellido"];
    echo "<br>".$_POST["EC"];
  }
 ?>
