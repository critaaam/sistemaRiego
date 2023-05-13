//LCD
#include <LiquidCrystal.h>
int rs = 12;
int e = 11;
int d4 = 5;
int d5 = 4;
int d6 = 3;
int d7 = 2;
int dTime = 1000;
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);

//Sensor humedad del suelo
int SensorPin = A1; 
int Suelo = 0;

//Sensor de temperatura
int TMP = 0;
float temperatura = 0;

//Motor
int motor = 6;       //Motor conectado en el pin 6
int velocidad = 255; //Este valor dependera del tipo de bomba habría que hacer pruebas

//fotorresitencia
int fotorresistor = 0;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  Serial.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
  temperatura = map(analogRead(TMP),0,1023,-50,450); 
  int Suelo = analogRead(SensorPin); 
  Suelo = map (Suelo, 0, 876, 0,100);
  int fotorresistor = analogRead(A5);
  //fotorresistor = map(fotorresistor,969,49,0,100); 
  
   
//Verificamos los valores en el monitor en Serie.
  Serial.println(String("Temperatura: ") + temperatura);
  Serial.println(String("Humedad suelo: ") + Suelo);
  Serial.println(String("Valor Fotorresistencia: ") + fotorresistor + String("\n"));

//imprimimos en la primer fila del lcd la temperatura
  lcd.setCursor(0, 0);           
  lcd.print(String("Temp: ") + temperatura + String(" C"));
  
 
//imprime en la segunda fila del lcd la humedad del suelo
  lcd.setCursor(0, 1);  
  lcd.print(String("H. Suelo: ") + Suelo + String("% "));
   
 
  delay(dTime);
  lcd.clear();
  /* La siguiente condición activa el motor si:
  - La humedad del suelo es menor al 50%
  - Si la luminosidad es menor a 10, osea empieza a haber iluminacion
  - Si la temperatura ambiental es menor a 30°
  */
  if (Suelo <= 50 && fotorresistor < 80 && temperatura < 30){
    digitalWrite(motor, HIGH);
    analogWrite(motor, velocidad);
  }else {
    digitalWrite(motor, LOW);
  }
  
}
