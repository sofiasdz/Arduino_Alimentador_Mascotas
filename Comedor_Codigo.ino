#include "EasyBuzzer.h"
#include <ESP32_Servo.h>
#include <virtuabotixRTC.h>
#include <Tone32.h>


//Buzzer
int buzzerPin = 16;
const int canalBuzzer = 1;


//Servo
Servo miServo;  // Creo un objeto servo para controlarlo
int pos = 0;    // variable que guarda la posicion
int servoPin = 4;
const int canalServo = 0;


//Clock
virtuabotixRTC myRTC(21, 22, 23);

void done() {
  Serial.print("Done!");
}

boolean timeForFood() {
  return myRTC.seconds == 10 || myRTC.seconds == 20 || myRTC.seconds == 30 || myRTC.seconds == 40 || myRTC.seconds == 50 || myRTC.seconds == 60;
}

void buzzerMakeSound() {
  digitalWrite(buzzerPin, HIGH);  // suena
  delay(500);
  digitalWrite(buzzerPin, LOW);  // no suena
}

void releaseFood() {
  miServo.write(180);
  delay(500);
  miServo.write(0);
}

void setupBuzzer() {
  pinMode(buzzerPin, OUTPUT);
  //ledcAttachPin(buzzerPin, canalBuzzer);
}

void setupServo() {
  pinMode(servoPin, OUTPUT);
  miServo.attach(servoPin);  // Defino en que pin va conectado el servo
}

void setupClock() {
  Serial.begin(9600);
  // segundos, minutos, horas, dia de la semana, numero de día, mes y año
  // myRTC.setDS1302Time(00, 39, 11, 03, 10, 05, 2023);
}

void updateClock() {
  // Esta función actualiza las variables para obtener resultados actuales
  myRTC.updateTime();

  // Se imprime el resultado en el Monitor Serial
  Serial.print("Fecha y hora actual: ");
  Serial.print(myRTC.dayofmonth);  // Se puede cambiar entre día y mes si se utiliza el sistema Americano
  Serial.print("/");
  Serial.print(myRTC.month);
  Serial.print("/");
  Serial.print(myRTC.year);
  Serial.print(" ");
  Serial.print(myRTC.hours);
  Serial.print(":");
  Serial.print(myRTC.minutes);
  Serial.print(":");
  Serial.println(myRTC.seconds);

  // Un pequeño delay para no repetir y leer más facil
  delay(1000);
}

void setup() {
  Serial.begin(9600);
  setupBuzzer();
  setupServo();
  setupClock();
}

void loop() {
  updateClock();
  if (timeForFood()) {
    releaseFood();
    delay(500);
    buzzerMakeSound();
  }
}
