<?php
include("../conexion.php");

?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <link rel="stylesheet" type="text/css" href="css/css.css">
    <link rel="stylesheet" type="text/css"
        href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css">
    <link rel="stylesheet" type="text/css"
        href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.bundle.min.js">
    <script type="text/css" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
</head>

<body>


    <div class="container d-flex justify-content-center">
        <div class="weather">
            <div id="encabezado" class="row-md-12 mt-6">
                <div class="col-md-12">
                    <img src="img/logo.png" class="logotipo" style="align-items: center;">
                </div>
            </div>

            <div class=" row">
                <div class=" col-md-6">
                    <div class="card"> <span class="icon"><img class="img-fluid" src="img/temperatura.png" /></span>
                        <div class="title">
                            <?php
                            //Toma el ultimo registro de la base de datos
                            $sql = "SELECT * FROM databox ORDER BY id DESC LIMIT 1";
                            //$sql = "SELECT * from registro";
                            $result = mysqli_query($con, $sql);
                            if ($mostrar = mysqli_fetch_array($result)) {
                            ?>

                            <p>Temperatura</p>
                        </div>
                        <div class="temp"><?php echo $mostrar['temperatura'] ?><sup>&deg;</sup></div>
                        <!--<div class="row">
                            <div class="col-4">
                                <div class="header">General</div>
                                <div class="value">Sunny</div>
                            </div>
                            <div class="col-4">
                                <div class="header">Air pollution</div>
                                <div class="value">47</div>
                            </div>
                            <div class="col-4">
                                <div class="header">Fire</div>
                                <div class="value">No</div>
                            </div>
                        </div>-->
                    </div>
                </div>
                <div class="col-md-6">
                    <div class="card"> <span class="icon"><img class="img-fluid" src="img/luminosidad.png" /></span>
                        <div class="title">
                            <p>Luminosidad</p>
                        </div>
                        <div class="temp"><?php echo $mostrar['luminosidad'] ?><sup>&deg;</sup></div>
                        <!--<div class="row">
                            <div class="col-4">
                                <div class="header">General</div>
                                <div class="value">Sunny</div>
                            </div>
                            <div class="col-4">
                                <div class="header">Air pollution</div>
                                <div class="value">20</div>
                            </div>
                            <div class="col-4">
                                <div class="header">Fire</div>
                                <div class="value">No</div>
                            </div>
                        </div>-->
                    </div>
                </div>
            </div>
            <div class="row">
                <div class="col-md-6">
                    <div class="card"> <span class="icon"><img src="img/humedad.png" /></span>
                        <div class="title">
                            <p>Humedad</p>
                        </div>
                        <div class="temp"><?php echo $mostrar['humedad'] ?><sup>&deg;</sup></div>
                        <!--<div class="row">
                            <div class="col-4">
                                <div class="header">General</div>
                                <div class="value">Wind</div>
                            </div>
                            <div class="col-4">
                                <div class="header">Air pollution</div>
                                <div class="value">52</div>
                            </div>
                            <div class="col-4">
                                <div class="header">Fire</div>
                                <div class="value">No</div>
                            </div>
                        </div>-->
                    </div>
                </div>
                <div class="col-md-6">
                    <v class="card"> <span class="icon"><img src="img/hora.png" /></span>
                        <div class="title">
                            <p>Hora</p>
                        </div>
                        <div class="temp"><?php echo $mostrar['hora'] ?><sup>&deg;</sup></div>
                        <!--<div class="row">
                            <div class="col-4">
                                <div class="header">General</div>
                                <div class="value">Cloudy</div>
                            </div>
                            <div class="col-4">
                                <div class="header">Air pollution</div>
                                <div class="value">34</div>
                            </div>
                            <div class="col-4">
                                <div class="header">Fire</div>
                                <div class="value">No</div>
                            </div>
                        </div>-->
                        <?php
                            }
                    ?>
                </div>
            </div>
        </div>
    </div>
    </div>
</body>

</html>