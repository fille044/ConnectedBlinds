/* ------------------------------------------------------------------------
   First test of controlling the blinds using an Arduino Uno and the library
   Servo.h.
   The servo rotates from 0-180 degrees based on the light on a phototransistor.

   openDone and closeDone are flags to detect when blinds have come to end-point.

   Servo           on D9
   Phototransistor on A0
   ------------------------------------------------------------------------ */



#include <Servo.h>
#define FALSE 0
#define TRUE 1

/* Static variables */
Servo myservo;
int servoPosition;
int light;
bool closeDone;
bool openDone;

void setup() {
    Serial.begin(9600);
    myservo.attach(9);
}

void loop() {
    servoPosition = 0;
    light = analogRead(A0);
    Serial.println(light);


  /* Close blinds when light is high, and blinds are not already closed */
  if(light >= 150 && closeDone == FALSE){
        for (servoPosition = 0; servoPosition <= 180; servoPosition += 1) { // goes from 0 degrees to 180 degrees
            // in steps of 1 degree
            myservo.write(servoPosition);              // tell servo to go to servoPositionition in variable 'servoPosition'
            delay(15);                       // waits 15ms for the servo to reach the servoPositionition
            openDone = FALSE;
            closeDone = FALSE;
            if(servoPosition == 180){
                closeDone = TRUE;
            }
        }
    }

    /* Open blinds when light is low, and blinds are not already opened */
    if(light < 150 && openDone == FALSE) {
        for (servoPosition = 180; servoPosition >= 0; servoPosition -= 1) {    // goes from 180 degrees to 0 degrees
            myservo.write(servoPosition);                  // tell servo to go to servoPositionition in variable 'servoPosition'
            delay(15);                           // waits 15ms for the servo to reach the servoPositionition
            openDone = FALSE;
            closeDone = FALSE;
            if(servoPosition == 0){
                openDone = TRUE;
            }
        }
    }
}
