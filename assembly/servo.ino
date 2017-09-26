/*
 * servo.ino
 *
 *  Created on: 26 Sep 2017
 *      Author: fille
 */


#include "assembly.h"


/* ------------------------------------------------------*/
/*
   Sets servo max and min based on input state
*/
/* ------------------------------------------------------*/
void controlServo(int Status)
{
	// OPEN
	if (Status == Open && openDone == FALSE) {
        digitalWrite(BLUELED, HIGH);
		myservo.attach(14);

		// Runs servo slowly until end is reached
		for (int pos = 0; pos <= MAXROTATION ; pos++) {
			myservo.write(pos);
			delay(SERVOSPEED);
			if (pos == MAXROTATION) {
				openDone = TRUE;
				closeDone = FALSE;
				Serial.println("Open done");
				myservo.detach();    // To eliminate noise
			}
		}
	}
	// CLOSE
	if (Status == Close && closeDone == FALSE) {
        digitalWrite(BLUELED, LOW);
		myservo.attach(14);

		// Runs servo slowly until end is reached
		for (int pos = MAXROTATION; pos >= 0 ; pos--) {
			myservo.write(pos);
			delay(SERVOSPEED);
			if (pos == 0) {
				closeDone = TRUE;
				openDone = FALSE;
				Serial.println("Close done");
				myservo.detach(); // To eliminate noise
			}
		}
	}

	// If Phototransistor mode is chosen on webpage, run this state.
	if(Status == Photo) {
		myservo.detach(); // To eliminate noise
		LightCounter++;
		delay(10);
		// Time to sample analog input
		if (LightCounter > LIGHTCOUNTERLIMIT) {
			static int PrevLight = myservo.read();
			Serial.print("pos is: ");
			Serial.println(PrevLight);
			int Light = 0;
			int pos = myservo.read();

			LightCounter = 0;
			Light = analogRead(PHOTOTRANSISTOR);
			Light = (Light - DZ) / DIFF;	// From 50-650 to X-X

			myservo.attach(14);
			delay(200);
			// Light has gone down since last time
			if (PrevLight > Light) {
				for (; pos > Light; pos--) {
					myservo.write(pos);
					delay(SERVOSPEED);
				}
			}
			// Light has gone up since last time
			else if (PrevLight < Light) {
				for (; pos < Light; pos++) {
					myservo.write(pos);
					delay(SERVOSPEED);
				}
			}
			// Save value to compare next time
			PrevLight = Light;
		}
	}
}

