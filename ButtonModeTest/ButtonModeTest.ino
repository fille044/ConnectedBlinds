byte Red, Green;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(4, INPUT);
  pinMode(12, INPUT);
  Serial.println("-------Fresh Start-------");
 }

void loop() {
  // put your main code here, to run repeatedly:
  Red = digitalRead(12);
  Green = digitalRead(4);
  if (Red == 1) {
    if (Green == 0) {
      Serial.println("Manual mode, closed");
    }
    else if (Green == 1) {
      Serial.println("Manual mode, open");
    }
  }
  else if (Red == 0) {
    Serial.println("Automatic mode");
  }
  delay(250);
}
