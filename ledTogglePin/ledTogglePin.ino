int ledpin = 5;  // This is the pin the LED connects to. 

void setup() {
  // put your setup code here, to run once:
  pinMode(ledpin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledpin, HIGH);   // turn the LED on (HIGH)
  delay(100);                       // wait for a second
  digitalWrite(ledpin, LOW);    // turn the LED off (LOW)
  delay(1000);                       // wait for a second
}
