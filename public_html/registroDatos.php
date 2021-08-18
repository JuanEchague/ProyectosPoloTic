<?php

//Este es el archivo al que deberia conectarse el arduino


$servername = "localhost";
$username = "id17275302_root";
$password = "prototipos_Polotic123";
$dbname = "id17275302_proyectos";

// Creamos la conexión
$con = new mysqli($servername, $username, $password, $dbname);
mysqli_set_charset($con, "utf8");

// Verificamos la conexión
if ($con->connect_error) {
    die("Conexión fallida: " . $con->connect_error);
} else {
     echo "Conexión exitosa";
}

//Variables a grabar
date_default_timezone_set("America/Argentina/Buenos_Aires");
$date = new DateTime();
$hora = $date->format('Y-m-d H:i:s');

$temperatura = $_POST['temperatura'];
$humedad = $_POST['humedad'];
$luminosidad = $_POST['luminosidad'];

//En teoria deberia generar la fecha y hora automaticamente XD
$query = "INSERT INTO `id17275302_proyectos`.`databox` (`id`, `temperatura`, `humedad`, `luminosidad`, `hora`) VALUES (NULL, '$temperatura', '$humedad', '$luminosidad', '$hora')";

//"registro" es el nombre de la tabla que use para probar la bd en mi servidor local, cambiar por lo que corresponda.



echo mysqli_query($con, $query);