/*
 * init.ino
 *
 *  Created on: 26 Sep 2017
 *      Author: fille
 */


#include "assembly.h"


/* ------------------------------------------------------*/
/*
   Initialize the Wifi-communication.
   Connects to network "Molk" and prints out the device
   IP-adress in serial monitor.
*/
/* ------------------------------------------------------*/
void initWifi(void)
{
  // Connect to WiFi network
	Serial.println();
	Serial.println();
	delay(500);
	Serial.print("Connecting to ");
	Serial.println(ssid);

	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		connectTimeOutCounter++;
		if (connectTimeOutCounter > 30) {
			connectTimeOutCounter = 0;
			Serial.println("Connection has timed out, trying again");
			initWifi();
		}
		Serial.print(".");
	}
	Serial.println("");
	Serial.println("WiFi connected");
	for (int ix = 0; ix < 10; ix++) {
		digitalWrite(BLUELED, HIGH);
		delay(100);
		digitalWrite(BLUELED, LOW);
		delay(100);
	}
	// Start the server
	server.begin();
	Serial.println("Server started");

	// Print the IP address
	Serial.print("Use this URL to connect: ");
	Serial.print("http://");
	Serial.print(WiFi.localIP());
	Serial.println("/");

	Serial.println();
	Serial.print("MAC: ");
	Serial.println(WiFi.macAddress());
	Serial.println("/");
	Serial.println("/");
}


/* ------------------------------------------------------*/
/*
   Sets up inputs and outputs
*/
/* ------------------------------------------------------*/
void initIO(void)
{
    pinMode(BUTTON, INPUT);
    pinMode(BLUELED, OUTPUT);
    pinMode(GREENLED, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(BLUELED, LOW);
    digitalWrite(GREENLED, LOW);
}
