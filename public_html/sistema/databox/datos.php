<?php 

include("conectar.php");

$temperatura = $_POST ['temperatura'];
$humedad = $_POST ['humedad'];

if(mysqli_query($conexion, "INSERT INTO `datos`(`temperatura`, `humedad`) values ('$temperatura','$humedad')"));

mysqli_close($conexion);
?>