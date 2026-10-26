#include "Servomotor.h"
#include "Pines.h"

void Servomotor::iniciar() {
  servo.setPeriodHertz(50);
  servo.attach(SERVO_PIN, 530, 2550);
  servo.write(Arriba90 ? 90 : 0);
}

void Servomotor::probar() {
    Serial.println("0 a 180");
for (int pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
		// in steps of 1 degree
		servo.write(pos);    // tell servo to go to position in variable 'pos'
		delay(15);             // waits 15ms for the servo to reach the position
        Serial.println(pos);
	}
    Serial.println("180 a 0");
	for (int pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
		servo.write(pos);    // tell servo to go to position in variable 'pos'
		delay(15);             // waits 15ms for the servo to reach the position
        Serial.println(pos);
	}
}

void Servomotor::subirLapiz() {
    servo.write(Arriba90 ? 90 : 0);
}

void Servomotor::bajarLapiz() {
    servo.write(Arriba90 ? 0 : 90);
}