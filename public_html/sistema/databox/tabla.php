<?php
$conexion = mysqli_connect('localhost', 'root', '', 'databox')
?>
<!DOCTYPE html>
<html>

<head>
    <title>DATA BOX</title>
    <meta name="author" content="Matzke Guillermo Adriel">
    <meta name="viewport" content="width = device-width, initial-scale = 1.0">
    <link rel="stylesheet" type="text/css" href="estilo.css">
    <link rel="icon" href="favicon.ico">

</head>

<body class="pag">
    <div class="databox">
        <img src="logo.png" class="logo">
    </div>
    <div class="databox">
        <table class="tabla">
            <tr class="fila">
                <td class="columna"><b>TEMPERATURA</b></td>
                <td class="columna"><b>HUMEDAD</b></td>
                <td class="columna"><b>LUMINOSIDAD</b></td>
                <td class="columna"><b>HORA</b></td>
            </tr>
            <?php
			$sql = "SELECT * from registro";
			$result = mysqli_query($conexion, $sql);
			while ($mostrar = mysqli_fetch_array($result)) {
			?>
            <tr class="fila">
                <td class="columna"><?php echo $mostrar['temperatura'] ?>ºc</td>
                <td class="columna"><?php echo $mostrar['humedad'] ?>%</td>
                <td class="columna"><?php echo $mostrar['luminosidad'] ?>%</td>
                <td class="columna"><?php echo $mostrar['hora'] ?></td>
            </tr>
            <?php
			}
			?>
        </table>
    </div>
    <div class="ir_a">
        <a class="boton reg" href="index.php">INICIO</a>
    </div>
</body>

</html>