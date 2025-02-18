// IR Sensor Distance Calculation Program

#include <Servo.h>
Servo servo;  

int servoPin = 9;
 
const int IR = 5;  // IR sensor connected to pin 5const int irPin = 5;  // IR sensor connected to pin 5
int detection = HIGH;    // no obstacle

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  pinMode(IR, INPUT);  // Set IR sensor pin as input
  Serial.begin(9600);
  servo.attach(servoPin); 
  // servo.attach(servoPin,550,2200);  // (pin, min, max)
  Serial.println("Attached!!!");
  servo.writeMicroseconds(1500);
  delay(2000);
  Serial.println("Started!!!");
  servo.writeMicroseconds(1500);
  delay(2000);
}
int trackingAngle = 0;
void loop() {
  detection = digitalRead(IR);
  if(detection == LOW){
    Serial.print("There is an obstacle!\n");
    rotateAntiClockwise(90);
  }
  else{ 
    Serial.print("No obstacle!\n");
  }
  delay(500);    // in ms

}


void oscillate(int angle, int pauseDur) {
  rotateClockwise(angle);
  pause(pauseDur);
  rotateAntiClockwise(angle);
  pause(pauseDur);
}

int ACLOCK_RUN_MS = 85;
int ACLOCK_PULSE = 1550;
int CLOCK_RUN_MS = 90;
int CLOCK_PULSE = 1450;
int STOP_PULSE = 1500;
int STOP_RUN_MS = 60;
int DEG_10 = 1;

void rotateClockwise(int angle) {
  rotate(angle, CLOCK_PULSE, CLOCK_RUN_MS); 
}

void rotateAntiClockwise(int angle) {
 rotate(angle, ACLOCK_PULSE, ACLOCK_RUN_MS);
}

int SIDE = 1;
void rotate(int angle, int pulse, int runMs) {
  int pulseAngle = angle/10;
  int totalDeg = DEG_10 * pulseAngle;
 for (int i=0; i<totalDeg;i++) {
    servo.writeMicroseconds(pulse);
    delay(runMs);
    servo.writeMicroseconds(STOP_PULSE);
    delay(STOP_RUN_MS);
    if(trackingAngle >= angle) {
      SIDE = -1;
    } else if(trackingAngle <=0) {
      SIDE = 1;
    }
    trackingAngle = trackingAngle+(pulseAngle*SIDE);
    //Serial.print("Angle: ");
    //Serial.println(trackingAngle);
  } 
}

void pause(int duration) {
    servo.writeMicroseconds(STOP_PULSE);
    delay(duration);
}