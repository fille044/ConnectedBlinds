/* Defines */
#include "assembly.h"


/* Static variables */


/* ------------------------------------------------------*/
/*
   Sets up serial monitor to 115200 baud/s.
   Sets LED pin to output and default to LOW.
   Starts initialization of Wifi server.
*/
/* ------------------------------------------------------*/
void setup()
{
    Serial.begin(115200);
    delay(1500);

    initIO();
    initWifi();

    myservo.write(0);
    delay(1000);
}


/* ------------------------------------------------------*/
/*
   Goes through the different states of modes and calls function
   servo setting
*/
/* ------------------------------------------------------*/
void handleStates(void)
{
	switch (ModeState) {
	case 0:
		//Phototransistor Auto
		digitalWrite(GREENLED, HIGH);
		digitalWrite(BLUELED, LOW);
		controlServo((int)Auto);
		break;
	case 1:
		// Forces the servo to adjust to light if auto mode is chose
		LightCounter = LIGHTCOUNTERLIMIT;
		// Web Open
		digitalWrite(GREENLED, LOW);
		controlServo((int)Open);
		break;
	case 2:
		// Forces the servo to adjust to light if auto mode is chosen
		LightCounter = LIGHTCOUNTERLIMIT;
		// Web Close
		digitalWrite(GREENLED, LOW);
		controlServo((int)Close);
		break;
  }
}


/* ------------------------------------------------------*/
/*
   Main loop for functionality
*/
/* ------------------------------------------------------*/
void loop()
{
	handleStates();
	delay(20);
    int clientCounter = 0;
    // Check if a client has connected
    client = server.available();
    if (!client) {
        return;
    }

    // Wait until the client sends some data
    Serial.println("new client");
    while(!client.available()) {
        delay(1);
        clientCounter++;
        if (clientCounter > 500) {
        	return;
        }
    }

    // Read the first line of the request
    request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();

    runWeb();


    delay(1);
    Serial.println("Ready");
}
