<?php

function datosCorrectos(){
  if(isset($_POST["jugadorX"]) && strlen($_POST["jugadorX"])>0 && isset($_POST["jugadorY"]) && strlen($_POST["jugadorY"])>0 ){
    $_SESSION["jX"] = $_POST["jugadorX"];
    $_SESSION["jY"] = $_POST["jugadorY"];
    return 1;
  }else{
     return 2;
  }
}

function generarMatriz($tamanio){
    for ($i=0; $i <8 ; $i++) {
      for ($j=0; $j <8 ; $j++) {
        $mat[$i][$j]=2;
        $cont[$i][$j]=0;
      }
    }
      $_SESSION["Mat"]=$mat;
      $_SESSION["Cont"]=$cont;
      $_SESSION["turno"]=1;
      $_SESSION["finJuego"]=false;
}

function capturaVariablesURL(){

  if (isset($_GET["fil"]) && isset($_GET["col"])) {
    $fila = $_GET["fil"];
    $columna = $_GET["col"];
    $_SESSION["Cont"][$_GET["fil"]][$_GET["col"]]++;

    if (!$_SESSION["finJuego"]) {
      if ($_SESSION["Mat"][$_GET["fil"]][$_GET["col"]] == 2 ) {
        if ($_SESSION["turno"]==1) {
          $_SESSION["Mat"][$_GET["fil"]][$_GET["col"]] = 1;
        }
        else{
          $_SESSION["Mat"][$_GET["fil"]][$_GET["col"]] = 0;

        }

        validar($fila,$columna);
        cambiarTurno();

      }else{
        echo "<script>alert('MOVIMIENTO NO VALIDO')</script>";
      }
    }
  }
}

function validacionHorizontal($fila,$columna){
  //validacion horizontal izquierda
    $gana = false;
    $contador=1;

    for ($i=$columna -1 ; $i >=0 ; $i--) {
      if ($_SESSION["Mat"][$fila][$i]==$_SESSION["turno"]) {
          $contador = $contador + 1;
      }
    }
    //validacion horizontal derecha
    for ($i=$columna +1 ; $i < $_SESSION["dimension"] ; $i++) {
      if ($_SESSION["Mat"][$fila][$i]==$_SESSION["turno"]) {
          $contador = $contador + 1;
       }
    }


  if($contador == 3){
    $gana = true;
  }
     return $gana;
}

function validacionVertical($fila,$columna){
    $gana=false;
    $contador=1;
     //validacion vertical abajo
     for ($i=$fila -1 ; $i >=0; $i--) {
       if ($_SESSION["Mat"][$i][$columna]==$_SESSION["turno"]) {
         $contador = $contador + 1;
       }
     }
     //validacion vertical arriba
     for ($i=$fila +1 ; $i < $_SESSION["dimension"]; $i++) {
       if ($_SESSION["Mat"][$i][$columna]==$_SESSION["turno"]) {
         $contador = $contador + 1;
       }
     }

    if($contador == 3){
        $gana = true;
    }
     return $gana;
}

function validacionDiagonalIzquierda($fila,$columna){
  $gana = false;
  $contador=1;
  //validacion superior izquierda inferior
  $r = $fila -1 ;
  $c = $columna -1;
  while ($r >= 0 && $c>=0) {
    if ($_SESSION["Mat"][$r][$c]==$_SESSION["turno"]) {
      $contador = $contador + 1;
    }
    $r--;$c--;
  }
  //validacion diagonal inferior derecha
  $r = $fila +1 ;
  $c = $columna +1;
  while ($r < $_SESSION["dimension"] && $c < $_SESSION["dimension"]) {
    if ($_SESSION["Mat"][$r][$c]==$_SESSION["turno"]) {
      $contador = $contador + 1;
    }
    $r++;$c++;
  }

  if($contador == 3){
      $gana = true;
  }
  return $gana;
}

function validacionDiagonalDerecha($fila,$columna){

  $gana = false;
  $contador=1;
  //validacion diagonal superior derecha
  $r = $fila -1 ;
  $c = $columna +1;
  while ($r >= 0 && $c< $_SESSION["dimension"]) {
    if ($_SESSION["Mat"][$r][$c]==$_SESSION["turno"]) {
      $contador = $contador + 1;
    }
    $r--;$c++;
  }

  $r = $fila +1 ;
  $c = $columna -1;
  while ($r <$_SESSION["dimension"] && $c>= 0) {
    if ($_SESSION["Mat"][$r][$c]==$_SESSION["turno"]) {
    $contador = $contador + 1;
    }
    $r++;$c--;
  }

  if($contador == 3){
      $gana = true;
  }
  return $gana;
}

function validar($fila,$columna){
  $_SESSION["dimension"] = 3;

  $gana = validacionHorizontal($fila,$columna);
   if($gana == true){
     echo "<script>alert('GANA HORIZONTALMENTE')</script>";
   }else{
     $gana = validacionVertical($fila,$columna);
     if($gana == true){
       echo "<script>alert('GANA VERTICALMENTE')</script>";
     }else{
         $gana = validacionDiagonalIzquierda($fila,$columna);
            if($gana == true){
              echo "<script>alert('GANA POR DIAGONAL IZQUIERDA')</script>";
            }else{
              $gana = validacionDiagonalDerecha($fila,$columna);
                if($gana == true){
                  echo "<script>alert('GANA POR DIAGONAL DERECHA')</script>";
                }
            }
     }
   }
  if($gana){
    $_SESSION["finJuego"]=true;
    cambiarTurno();
  }
}


function imprimirMatriz(){

  $mat = $_SESSION["Mat"];
    for ($i=0; $i <3 ; $i++) {
      echo "<tr>";
      for ($j=0; $j <3 ; $j++) {
        //echo "<td class='caja'  onclick='cargar(".$i.",".$j."); comprobar();'>",$mat[$i][$j],"</td> ";
        if($mat[$i][$j]== 1){
          echo "<td class='caja'  onclick='cargar(".$i.",".$j.");'>X</td> ";
        }else {
          if($mat[$i][$j]== 0){
            echo "<td class='caja'  onclick='cargar(".$i.",".$j.");'>O</td> ";
          }else
          echo "<td class='caja'  onclick='cargar(".$i.",".$j.");'></td> ";
        }

        //echo "<td> <a onclick='cargar(".$1.",".$j.");'><img src=img/",$mat[$i][$j],".jpg/></td>";
      }
      echo "</tr>";
    }
    if($_SESSION["finJuego"]){
      if($_SESSION["turno"]==1){
        echo "GANADOR: ",$_SESSION["jX"];
      }else{
        echo "GANADOR: ",$_SESSION["jY"];
      }

    }
}

function imprimirMatrizConteoClicks(){
  echo "<tr>";
  echo "<tr>";
  echo "<tr>";
  echo "<tr>";
  $cont = $_SESSION["Cont"];
    for ($i=0; $i <3 ; $i++) {
      echo "<tr>";
      for ($j=0; $j <3 ; $j++) {
        echo "<td>",$_SESSION["Cont"][$i][$j],"</td>";
      }
      echo "</tr>";
    }
}

function cambiarTurno(){
  if ($_SESSION["turno"]==1) {
    $_SESSION["turno"]=0;
  }else{
    $_SESSION["turno"]=1;
  }
}

 ?>
