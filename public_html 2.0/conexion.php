<?php


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
    // echo "Conexión exitosa";
}