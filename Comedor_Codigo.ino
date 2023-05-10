#include "EasyBuzzer.h"
#include <ESP32Servo.h>
#include <virtuabotixRTC.h>

//Buzzer
int buzzerPin = 16;
const int CanalPWM = 1;


//Servo
 Servo miServo;  // Creo un objeto servo para controlarlo
int pos = 0;    // variable que guarda la posicion


//Clock
virtuabotixRTC myRTC(21, 22, 23);

void done() {
	Serial.print("Done!");
}

void setup() {
  Serial.begin(115200);
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

boolean timeForFood(){
  if(myRTC.seconds==15) {
    return true;
  }
  else return false;
}

void buzzerMakeSound(){
  ledcWriteNote(CanalPWM, NOTE_C, 4);
  delay(500);
  ledcWriteNote(CanalPWM, NOTE_D, 4);
  delay(500);
  // Silencio Buzzer
  ledcWrite(CanalPWM,0);
}

void releaseFood(){
  for (pos = 0; pos <= 180; pos += 1) { // va de 0 grados a 180 grados
    // in steps of 1 degree
    miServo.write(pos);              // indicar al servo que vaya a la posición en la variable 'pos'
    delay(15);                       // espera 15 ms para que el servo alcance la posición
  }
  for (pos = 180; pos >= 0; pos -= 1) { // va de 180 grados a 0 grados
    miServo.write(pos);              // indicar al servo que vaya a la posición en la variable 'pos'
    delay(15);                       // espera 15 ms para que el servo alcance la posición
  }
}

void setupBuzzer(){
  ledcAttachPin(buzzerPin, CanalPWM);
    

}

void setupServo(){
  miServo.attach(4);  // Defino en que pin va conectado el servo
  
}

void setupClock(){
  Serial.begin(9600);
  // segundos, minutos, horas, dia de la semana, numero de día, mes y año

  myRTC.setDS1302Time(00, 39, 11, 03, 10, 05, 2023);
}

void updateClock(){
    myRTC.updateTime();
     // Se imprime el resultado en el Monitor Serial
    Serial.print("Fecha y hora actual: ");
    Serial.print(myRTC.dayofmonth); // Se puede cambiar entre día y mes si se utiliza el sistema Americano
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
