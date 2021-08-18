<?php

//Este es el archivo al que deberia conectarse el arduino



include("conexion.php");

date_default_timezone_set("America/Argentina/Buenos_Aires");
$date = new DateTime();
$hora = $date->format('Y-m-d H:i:s');

//Variables a grabar
$temperatura = $_POST['temperatura'];
$humedad = $_POST['humedad'];
$luminosidad = $_POST['luminosidad'];




//En teoria deberia generar la fecha y hora automaticamente XD
$query = "INSERT INTO databox (id,temperatura,humedad,luminosidad,hora) VALUES (NULL, '$temperatura','$humedad','$luminosidad','$hora')";

//"registro" es el nombre de la tabla que use para probar la bd en mi servidor local, cambiar por lo que corresponda.

header("Location: databox/index3.php");

echo mysqli_query($con, $query);