int TEST_PIN = 13;
int PIN13_STATUS = HIGH; 

void setup()
{
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(TEST_PIN, OUTPUT);
  Serial.println("Running Setup!!!");
}

void loop()
{
  // put your main code here, to run repeatedly:
  if(PIN13_STATUS == HIGH) {
    delay(3000);
    PIN13_STATUS = LOW;
  } else {
    PIN13_STATUS = HIGH;
    delay(2000);
  }
  digitalWrite(TEST_PIN, PIN13_STATUS);
  Serial.println("Running in loop!!!");
}
