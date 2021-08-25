#include <LiquidCrystal_I2C.h>

#include <RTClib.h>

#include <DHT.h>

#include <SPI.h>

#include <Wire.h>

int periodo1 = 3000; //3 segundo para millis()
unsigned long TiempoAhora = 0;  //para millis()
// 2.- CREACIÓN DE OBJETOS Y DEFINICIÓN DE PINES

RTC_DS3231 RTC;
const int CS = 9;  // Para este módulo.
int minuto = 0;  // Para periodos con rtc
int segundo = 0; // Para periodos con rtc
#define DHTPIN 8     // pin digital del sensor DHT
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

/*  -------------------------------------------------
 *  Declaración de constantes y variables 
*/

#define LIGHTSENSORPIN A3 //Ambient light sensor reading

const int sensor = A3;  // Sensor de luminosidad

const int boton = 2; // Boton de apagado de alarma

// Pines de los Relay
#define relay1 10
#define relay2 9
// Pines de los Sensores
#define pirPin 4    // Sensor movimiento
#define buzzer 7    //alarma
#define led1 5// Alarma
#define led2 6// Envio de datos

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

//variables globales
int cont = 1;  // Para el refresco de la pantlla
int m;   // Minutos de rtc
int s;   // Segundos de rtc
bool rel = true; // Bandera de encendido luz
bool em = true;  // Bandera del emisor
int ta; // Temperatura
int luz; // Luminosidad
bool l= true; // variable para bandera de relay
bool val=true; // Variable para bandera de alarma

byte customChar[] = {
  0x00,
  0x0E,
  0x0A,
  0x0E,
  0x00,
  0x00,
  0x00,
  0x00
};


String datos;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  RTC.begin();
  // Se establece fecha y hora sólo la primera vez, una vez hecho
  // se comenta esta línea y se vuelve a cargar el programa.
  //RTC.adjust(DateTime(__DATE__,__TIME__));
  if(!RTC.begin())
  {
    delay(3000);
  }
  // Inicia el LCD
  lcd.begin();
  lcd.createChar(0, customChar);
  // Prende la luz de fondo de la pantalla.
  lcd.backlight();
  dht.begin();
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(pirPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(boton, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(boton), alarm, FALLING); // Interrupcion para activar y desactivar la alarma con el boton
  digitalWrite(buzzer, HIGH);
  //Establece el cursor del LCD para centrar la palabra
  lcd.setCursor(3, 0);
  lcd.print("Bienvenido");  
  lcd.setCursor(0, 0);
  delay(3000);
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("DATA BOX");
  delay(3000);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
   funcion(); // Muestra en pantalla los datos
   encendidoDeLuz(); // Segun el sensor de movimiento inicia la funcion relay
   alarma();  // Enciende un buzzer en condiciones criticas
   emisor();  // Envia un String por serie al Esp
}

int temp() // Lee la temperatura
{
  float t = dht.readTemperature();
  ta=t;
  return t;
  }
int hum() // Lee la humedad
{
  float h = dht.readHumidity();
  return h;
  }
  
int porcentajeDeLuz() // lee la luminosidad
{
  int sensorValue = analogRead(sensor);
  luz = map(sensorValue, 0, 200, 0, 100);
  if(luz >= 100){
    luz = 100;
  }
  return luz;
  }

void hora() // Imprime en pantalla la fecha y hora
{
    DateTime now = RTC.now(); 
    lcd.setCursor(3, 0);
    lcd.print(now.day(), DEC);
    lcd.print('/');
    if(now.month()<10)
    lcd.print(0);
    lcd.print(now.month(), DEC);
    lcd.print('/');
    lcd.print(now.year(), DEC);
    lcd.setCursor(4, 1);
    lcd.print(now.hour(), DEC);
    lcd.print(':');
    if(now.minute()<10)
    lcd.print(0);
    lcd.print(now.minute(), DEC);
    lcd.print(':');
    if(now.second()<10)
    lcd.print(0);
    lcd.print(now.second(), DEC);
  
}

void funcion() // Muestra el menu
{
 if (millis()> TiempoAhora + periodo1){ 
      TiempoAhora = millis();
      lcd.clear();
  if(cont == 1){
   hora();
  }
  if(cont == 2)
  {
    lcd.setCursor(2, 0);
    lcd.print("Temperatura: ");
    lcd.setCursor(6, 1);
    lcd.print(temp());
    lcd.write(0);
    lcd.print("C");
  }
  if(cont == 3)
  {
    lcd.setCursor(4, 0);
    lcd.print("Humedad: ");
    lcd.setCursor(6, 1);
    lcd.print(hum());
    lcd.print("%");
  }
  if(cont ==4)
  {
    lcd.setCursor(2, 0);
    lcd.print("Luminosidad: ");
    lcd.setCursor(7, 1);
    lcd.print(porcentajeDeLuz());
    lcd.print("%");
  }
  if(cont ==5)
  {
    if(val ==true){
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("Alarma");
    lcd.setCursor(4, 1);
    lcd.print("Activada");
    digitalWrite(led1, HIGH);
    }
    else{
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("Alarma");
    lcd.setCursor(3, 1);
    lcd.print("Desactivada");
    digitalWrite(led1, LOW);
      }
  }
  cont++;
  if(cont==6)
    cont=1;
 }
 
}

void relay() // Enciede los relay segun el porcentaje de luminosidad
{   
    l = false;
  luz = porcentajeDeLuz();
  if (luz >=70)
  {
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);
  }
  if ((luz >= 50) && (luz <= 69))
  {
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, HIGH);
  }
  if (luz <= 49)
  {
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
  }
}

void encendidoDeLuz()
{
  DateTime now = RTC.now();
    m = now.minute(), DEC;
    s = now.second(), DEC;
  
  int valPIR;
  valPIR = digitalRead(pirPin);
  if (valPIR == HIGH && l == true)
  {
    porcentajeDeLuz();
    relay();
  }
  
   else
  {
  if(((m == 0)&&(rel==true))||((m == 10)&&(rel==false))||((m == 20)&&(rel==true))||((m == 30)&&(rel==false))||((m == 40)&&(rel==true))||((m == 50)&&(rel==false)))
   {
    if(((m == 0)&&(rel==true))||((m == 20)&&(rel==true))||((m == 40)&&(rel==true))){
      rel=!rel;
      }
      if(((m == 10)&&(rel==false))||((m == 30)&&(rel==false))||((m == 50)&&(rel==false))){
      rel=!rel;
      }
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);
    l = true;
    }
  }
}

void alarm()
{
  val=!val;
}

void alarma()
{
  digitalWrite(buzzer, HIGH);
  if(val ==true){
  if (ta > 20)
  {
    digitalWrite(buzzer, LOW);
    }
  }
    else
    {
      digitalWrite(buzzer, HIGH);
      }
 }


void emisor(){
  DateTime now = RTC.now();
    m = now.minute(), DEC;
    s = now.second(), DEC;
  
   if(((m == 0)&&(em==true))||((m == 30)&&(em==false)))
   {
    if((m == 0)&&(em==true)){
      em=!em;
      }
      if((m == 30)&&(em==false)){
      em=!em;
      }
  datos = (','+(String(temp()))+','+(String(hum()))+','+(String(porcentajeDeLuz())));
  Serial.println(datos);
  digitalWrite(led2, HIGH);
  delay(100);
  digitalWrite(led2, LOW);
  }
}
