#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
int temperatura;
int humedad;
int luminosidad;
const char* host = "polotic.000webhostapp.com";
String strhost = "polotic.000webhostapp.com";
String strurl = "/registroDatos.php";
String chipId = "";
String str = "";
const char separator = ',';
const int dataLength = 3;
int data[dataLength];

void parpadeo(){
  int i;
  for(i=0; i<8; i++){
    digitalWrite(2, LOW);
    delay(100);
    digitalWrite(2, HIGH);
    delay(100);
  }
}

void setup(){
pinMode(2, OUTPUT);
digitalWrite(2, HIGH);
IPAddress miIP = WiFi.localIP() ;
Serial.print(miIP);
WiFi.mode(WIFI_STA); //modo establecido explícitamente, esp por defecto es STA + AP

    // ponga su código de configuración aquí, para que se ejecute una vez:
    Serial.begin(115200);
    
    // WiFi.mode(WiFi_STA); // Es una buena práctica asegurarse de que su código establezca el modo wifi como lo desea.

    //WiFiManager, Inicialización local. Una vez que compila no hay necesidad de modificarlo.
    WiFiManager wm;

    //restablecer la configuración: borra las credenciales para realizar pruebas
    //wm.resetSettings();

    // Se conecta automáticamente usando credenciales guardadas,
    // si falla la conexión, inicia un punto de acceso con el nombre especificado ("AutoConnectAP"),
    // si está vacío generará automáticamente SSID, si la contraseña está en blanco será AP anónimo (wm.autoConnect ())
    // luego entra en un bucle de bloqueo en espera de configuración y devolverá un resultado exitoso
    
    bool res;
    // res = wm.autoConnect(); // nombre de AP generado automáticamente a partir de chipid
    // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
    res = wm.autoConnect("AutoConnectAP","password"); // Contraseña protegida ap

    if(!res) {
        Serial.println("Failed to connect");
        // ESP.restart();
    } 
    else {
        //si llegas aquí te has conectado al wifi   
        Serial.println("Conectado...yeey :)");
    }

}
void loop(){
   if (Serial.available())
   {
     if (Serial.find(','))
   {
      str = Serial.readStringUntil('\n');
      Serial.println(str);
      const int dataLength = 3;
      for (int i = 0; i < dataLength ; i++)
      {
         int index = str.indexOf(separator);
         data[i] = str.substring(0, index).toInt();
         str = str.substring(index + 1);
      }
      temperatura = (data[0]);
      humedad = (data[1]);
      luminosidad = (data[2]);
     
     Serial.print("temperatura= ");
     Serial.println(temperatura);
     Serial.print("humedad= ");
     Serial.println(humedad);
     Serial.print("luminosidad= ");
     Serial.println(luminosidad);

     WiFiClient client;

  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, 80))
  {
    Serial.println("connected]");
    //Serial.print("ChipID= ");
    //Serial.println(chipId);
    String datos("$id=" + chipId + "&temperatura=" + (String(temperatura)) + "&humedad=" + (String(humedad)) + "&luminosidad=" + (String(luminosidad)));
    Serial.println(datos);
    Serial.println("[Sending a request]");
    client.print(String("POST ") + strurl + " HTTP/1.1" + "\r\n" + 
               "Host: " + strhost + "\r\n" +
               "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:90.0) Gecko/20100101 Firefox/90.0" + "\r\n" +
               "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8" + "\r\n" +
               "Accept-Language: es-ES,es;q=0.8,en-US;q=0.5,en;q=0.3" + "\r\n" +
               //"Accept-Encoding: gzip, deflate" + "\r\n" +
               "Content-Type: application/x-www-form-urlencoded" + "\r\n" +
               "Content-Length: " + datos.length() + "\r\n" +
               "Origin: https://polotic.000webhostapp.com/" + "\r\n" +
               "Connection: keep-alive" + "\r\n" +
               "Referer: https://polotic.000webhostapp.com/" + "\r\n" +
               "Cookie: __test=c7f732785cf62927bcb3935b77920a45" + "\r\n" +
               "Upgrade-Insecure-Requests: 1" + "\r\n" +

               "\r\n" + datos);

    Serial.println("[Response:]");
    while (client.connected())
    {
      if (client.available())
      {
        String line = client.readStringUntil('\n');
        Serial.println(line);
      }
    }
    client.stop();
    Serial.println("\n[Disconnected]");
    parpadeo();
  }
  else
  {
    Serial.println("connection failed!]");
    client.stop();
  }  
   }
}
}
