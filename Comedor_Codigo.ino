#include <ESP32_Servo.h>
#include <virtuabotixRTC.h>


// Setup comedor

void setup() {
  Serial.begin(9600);
  setupBuzzer();
  setupServo();
  setupClock();
}

// Servo
int buzzerPin = 16;
const int canalBuzzer = 1;
void setupBuzzer() {
  pinMode(buzzerPin, OUTPUT);
}

// Buzzer
Servo miServo;  // Creo un objeto servo para controlarlo
int pos = 0;    // variable que guarda la posicion
int servoPin = 4;
const int canalServo = 0;

void setupServo() {
  pinMode(servoPin, OUTPUT);
  miServo.attach(servoPin); 
}

virtuabotixRTC myRTC(21, 22, 23);

void setupClock() {
  Serial.begin(9600);
  // myRTC.setDS1302Time(00, 39, 11, 03, 10, 05, 2023);
}

boolean timeForFood() {
  return myRTC.seconds == 10 || myRTC.seconds == 20 || myRTC.seconds == 30 || myRTC.seconds == 40 || myRTC.seconds == 50 || myRTC.seconds == 60;
}

void buzzerMakeSound() {
  digitalWrite(buzzerPin, HIGH);
  delay(500);
  digitalWrite(buzzerPin, LOW);
}

void releaseFood() {
  miServo.write(180);
  delay(500);
  miServo.write(0);
}

void loopClock() {
  myRTC.updateTime();
}

void loop() {
  loopClock();
  if (timeForFood()) {
    releaseFood();
    delay(500);
    buzzerMakeSound();
  }
}
