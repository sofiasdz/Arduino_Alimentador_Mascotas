

#include "EasyBuzzer.h"
#include <ESP32Servo.h>

//Buzzer
unsigned int frequency = 1000;  
unsigned int onDuration = 50;
unsigned int offDuration = 100;
unsigned int beeps = 2;
unsigned int pauseDuration = 500;
unsigned int cycles = 10;

//Servo
 Servo miServo;  // Creo un objeto servo para controlarlo
int pos = 0;    // variable que guarda la posicion

void done() {
	Serial.print("Done!");
}

void setup() {
  setupBuzzer();
  setupServo();


    
}

void foodDeployment(){
  buzzerMakeSound();
}

void loop() {

  if (timeForFood()) {
    buzzerMakeSound();
    releaseFood();
  }

}

boolean timeForFood(){
  return true;
}

void buzzerMakeSound(){
  	/* Always call this function in the loop for EasyBuzzer to work. */
	EasyBuzzer.update();
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
	Serial.begin(115200);
	/* Start a beeping sequence. */
	EasyBuzzer.beep(
		frequency,		// Frequency in hertz(HZ). 
		onDuration, 	// On Duration in milliseconds(ms).
		offDuration, 	// Off Duration in milliseconds(ms).
		beeps, 			// The number of beeps per cycle.
		pauseDuration, 	// Pause duration.
		cycles, 		// The number of cycle.
		done			// [Optional] Callback. A function to call when the sequence ends.
	);
}

void setupServo(){
 
  miServo.attach(4);  // Defino en que pin va conectado el servo
  
}
