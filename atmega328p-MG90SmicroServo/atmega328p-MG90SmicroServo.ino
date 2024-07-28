
//Red = 5V, Brm = Gnd, Orn = COntrolor PWM
// see if it can move otherway also. It will not work with -ve values of Degrees
// 90 deg mid vale is 1350. 0 deg is 1350. 180 deg is 2300. Test


//servo.attach() - assign arduino pin connected to PWM pin of servo
//servo.datach() - opposite of above?
//servo.write(angle) - move servo to given angle
//servo.writeMicroseconds(us)- 1000 is fully CCW. 1500 is middle. 2000 is fully CW

#include <Servo.h>
Servo servo;  

int servoPin = 9;
 
void setup()
{
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
void loop()
{
  oscillate(360, 100);
  // servo.write(90);
  // pause(500);
  // servo.write(0);
  // pause(5000);
  // servo.write(180);
  // pause(5000);
  // servo.write(90);
  // pause(500);
  // rotateClockwise(360);
  // pause(100);
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
    Serial.print("Angle: ");
    Serial.println(trackingAngle);
  } 
}

void pause(int duration) {
    servo.writeMicroseconds(STOP_PULSE);
    delay(duration);
}