int redlight = 13;
int yellowlight = 12;
int greenlight = 11;

void setup() {
  // put your setup code here, to run once:
  pinMode(redlight, OUTPUT);
  pinMode(yellowlight, OUTPUT);
  pinMode(greenlight, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // Start with green light for 10 seconds.
  digitalWrite(redlight, LOW);
  digitalWrite(yellowlight, LOW);
  digitalWrite(greenlight, HIGH);
  Serial.println("Green Light. You may pass!");
  delay(10000); // 10 seconds = 10000 milliseconds
  
  // Go to yellow light for 2 seconds.
  digitalWrite(redlight, LOW);
  digitalWrite(yellowlight, HIGH);
  digitalWrite(greenlight, LOW);
  Serial.println("Yellow Light. Please slow to a stop!");
  
  delay(2000); // 2 seconds = 2000 milliseconds

  // Go red light for 5 seconds. 
  digitalWrite(redlight, HIGH);
  digitalWrite(yellowlight, LOW);
  digitalWrite(greenlight, LOW);
  Serial.println("Red Light. Stop now!");
  delay(5000); // 5 seconds = 5000 milliseconds
}
