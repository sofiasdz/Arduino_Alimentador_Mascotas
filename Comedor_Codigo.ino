#include "EasyBuzzer.h"
#include <ESP32Servo.h>
#include <Wire.h>
#include <RTClib.h>

//Buzzer
int buzzerPin = 16;
const int CanalPWM = 1;

//Servo
Servo miServo;  // Creo un objeto servo para controlarlo
int pos = 0;    // variable que guarda la posicion

// SDA al 20 | SCL al 21 |VCC 3.3 o 5V
// Declaramos un RTC DS3231
RTC_DS3231 rtc;


void setup() {
  Serial.begin(9600);
  setupBuzzer();
  setupServo();
  setupClock();  
}

void loop(){
  updateClock();
  if (timeForFood()) {
     releaseFood();
     delay(500);
     buzzerMakeSound();  
  }
}

void updateClock(){
  DateTime now = rtc.now();
  Serial.print(now.day());
  Serial.print('/');
  Serial.print(now.month());
  Serial.print('/');
  Serial.print(now.year());
  Serial.print(" ");
  Serial.print(now.hour());
  Serial.print(':');
  Serial.print(now.minute());
  Serial.print(':');
  Serial.print(now.second());
  Serial.println();
  delay(1000);

}

boolean timeForFood(){
  DateTime now = rtc.now();
  if(now.second()==15) {
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
    miServo.write(100);
    delay(2000);
    miServo.write(260); 
}

void setupBuzzer(){
  ledcAttachPin(buzzerPin, CanalPWM);
}

void setupServo(){
  miServo.attach(4);  // Defino en que pin va conectado el servo
}

void setupClock(){
  if (! rtc.begin()) {
    Serial.println("No hay un módulo RTC");
    while (1);
  }
}
