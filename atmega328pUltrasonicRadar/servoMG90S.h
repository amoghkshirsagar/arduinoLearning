
#include <Servo.h>
Servo servo;

int trackingAngle = 0;
int ACLOCK_RUN_MS = 85;
int ACLOCK_PULSE = 1550;
int CLOCK_RUN_MS = 90;
int CLOCK_PULSE = 1450;
int STOP_PULSE = 1500;
int STOP_RUN_MS = 60;
int DEG_10 = 1;
int SIDE = 1;

void rotate(int angle, int pusle, int ms, float (*f)());
void rotateAntiClockwise(int angle, float (*f)());
void pause(int ms);
void rotateClockwise(int angle, float (*f)());

void oscillate(int angle, int pauseDur, float (*f)())
{
    rotateClockwise(angle,*f);
    pause(pauseDur);
    rotateAntiClockwise(angle,*f);
    pause(pauseDur);
}

void rotateClockwise(int angle, float (*f)())
{
    rotate(angle, CLOCK_PULSE, CLOCK_RUN_MS, *f);
}

void rotateAntiClockwise(int angle, float (*f)())
{
    rotate(angle, ACLOCK_PULSE, ACLOCK_RUN_MS, *f);
}
int angleCounter = 0;

void rotate(int angle, int pulse, int runMs, float (*f)())
{
    int pulseAngle = angle / 10;
    int totalDeg = DEG_10 * pulseAngle;
    if (CLOCK_PULSE == pulse) {
      angleCounter = 18;
    } else {
      angleCounter = 180;
    }
    for (int i = 0; i < totalDeg; i++)
    {
        servo.writeMicroseconds(pulse);
        delay(runMs);
        servo.writeMicroseconds(STOP_PULSE);
        delay(STOP_RUN_MS);
        if (CLOCK_PULSE  == pulse)
        {
            SIDE = 1;
        }
        else if (trackingAngle <= 0)
        {
            SIDE = -1;
        }
        angleCounter = angleCounter + (pulseAngle * SIDE)/2;
        float distance = (*f)();
        
        Serial.print(angleCounter);
        Serial.print(",");
        Serial.print(distance);
        Serial.println("|");
    }
}

void pause(int duration)
{
    servo.writeMicroseconds(STOP_PULSE);
    delay(duration);
}