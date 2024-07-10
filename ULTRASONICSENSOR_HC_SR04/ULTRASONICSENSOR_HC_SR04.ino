int TEST_PIN = 13;
int TEST_PIN2 = 7;

int PING_12 = 12;
int ECHO_2 = 2;
int USPING_12status = LOW;
int TST_STATUS = HIGH;
int TST_STATUS2 = HIGH;
int duration = 0;
int distance = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PING_12, OUTPUT);
  pinMode(ECHO_2, INPUT);
  pinMode(TEST_PIN, OUTPUT);
  pinMode(TEST_PIN2, OUTPUT);
  Serial.println("in setup");
}

void loop() {
  Serial.println("in loop");
  // send :
  digitalWrite(PING_12, LOW);
  delay(2);
  digitalWrite(PING_12, HIGH);
  delay(10);
  digitalWrite(PING_12, LOW);

  // Read echo pulse
  digitalRead(ECHO_2);

  duration = pulseIn(ECHO_2, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
  if(distance<20) {
    digitalWrite(TEST_PIN, HIGH);
    digitalWrite(TEST_PIN2, LOW);
  } else if(distance<40) {
    digitalWrite(TEST_PIN, LOW);
    digitalWrite(TEST_PIN2, HIGH);
  } else {

  digitalWrite(TEST_PIN, HIGH);
  digitalWrite(TEST_PIN2, HIGH);
  }
}
