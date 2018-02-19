<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <style type="text/css">
      fieldset {
        background-color: gray;
      }
      legend{
        font-style: italic;
        color: white;
        background-color: black;
      }
    </style>
    <title></title>
  </head>
  <body>
      <form action="persona.php" method="post">
        <fieldset>
          <legend> Formulario</legend>
          <label for="">nombre</label>
          <input type="text" name="ok" value="">
          <br>
          <label for="">apellido</label>
          <input type="text" name="apellido" value="">
          <input type="submit" name="botton" value="aceptar">
          <ul>
            <li> <input type="radio" name="EC" value="soltero"> soltero </li>
            <li> <input type="radio" name="EC" value="casado">casado </li>
          </ul>
       </fieldset>
      </form>

      <form action="../../form-result.php" method="post" enctype="multipart/form-data" target="_blank">
          <p><label>Archivo: <input type="file" name="archivo"></label> <input type="submit" value="Enviar datos"></p>
      </form>

    <form action="../../form-result.php" method="get" target="_blank">
      <fieldset>
        <legend>Información básica</legend>
        <p><label>Nombre completo: <input type="text" name="nombrecompleto"></label></p>
        <p><label>Fecha de nacimiento: <input type="date" name="fechadenacimiento"></label></p>
        <p>Gender:
          <label><input type="radio" name="genero" value="masculino"> Masculino</label>
          <label><input type="radio" name="genero" value="femenino"> Femenino</label>
        </p>
        <p><label>Dirección: <input type="text" name="direccion"></label></p>
        <p><label>Número telefónico: <input type="tel" name="telefono"></label></p>
      </fieldset>

      <fieldset>
        <legend>Información extra</legend>
        <p>Interests:
          <label><input type="checkbox" name="libros"> Libros</label>
          <label><input type="checkbox" name="peliculas"> Películas</label>
          <label><input type="checkbox" name="videojuegos"> Videojuegos</label>
        </p>
        <p><label>Color favorito: <input type="color" name="colorfavorito"></label></p>
      </fieldset>
      <p>
        <input type="submit" value="Enviar datos">
        <input type="reset" value="Restaurar formulario">
      </p>
    </form>

  </body>
</html>
