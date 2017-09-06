#include <Servo.h>
#define FALSE 0
#define TRUE 1

Servo myservo;
int pos;
int light;
bool closeDone, openDone;

void setup() {
  Serial.begin(9600);
  myservo.attach(9);
  pinMode(7,INPUT);  
}

void loop() {
  pos = 0;
  light = analogRead(A0);
  Serial.println(light);

   
  //Close blinds
  if(light >= 150 && closeDone == FALSE){
      for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
      openDone = FALSE;
      closeDone = FALSE;
      if(pos == 180){
        closeDone = TRUE;
      }
    }
  }
  //Open blinds
  if(light < 150 && openDone == FALSE) {
      for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
      openDone = FALSE;
      closeDone = FALSE;
      if(pos == 0){
        openDone = TRUE;
      }
    }
  }
}
