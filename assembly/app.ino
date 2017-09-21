/* Defines */
#include <ESP8266WiFi.h>
#include <Servo.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#include "declaration.h"


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
		timeoutCounter++;
		if (timeoutCounter > 60) {
			isTimeout = TRUE;
			Serial.println("Connection has timed out, entering manual mode");
			return;
		}
		Serial.print(".");
	}
	Serial.println("");
	Serial.println("WiFi connected");

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
