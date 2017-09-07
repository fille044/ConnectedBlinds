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
int servoPosition = 0;
int light;
bool closeDone;
bool openDone;

void setup() {
    Serial.begin(9600);
    myservo.attach(9);
}

void loop() {
    light = analogRead(A0);
    Serial.println(light);

    /* Close blinds when light is high, and blinds are not already closed */
    if(light >= 150 && closeDone == FALSE){
        myservo.write(servoPosition);
        delay(15);
        servoPosition++;
        openDone = FALSE;
        closeDone = FALSE;
        if(servoPosition == 180){
            closeDone = TRUE;
        }
    }
           /* Open blinds when light is low, and blinds are not already opened */
    if(light < 150 && openDone == FALSE) {
        myservo.write(servoPosition);
        delay(15);
        servoPosition--;
        openDone = FALSE;
        closeDone = FALSE;
        if(servoPosition == 0){
            openDone = TRUE;
        }
    }
}

