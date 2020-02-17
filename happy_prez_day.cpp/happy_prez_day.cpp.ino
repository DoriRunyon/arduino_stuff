int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT);

}

void blinker(int highTime, int lowTime) {
  digitalWrite(ledPin, HIGH);
  delay(highTime);
  digitalWrite(ledPin, LOW);
  delay(lowTime);
}

void loop() {

  // Happy 
  blinker(300, 190);
  blinker(300, 700);

  // Presidents 
  blinker(300, 140);
  blinker(300, 140);
  blinker(300, 700);

  // Day
  blinker(300, 3000);
}
