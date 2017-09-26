/*
 * assembly.h
 *
 *  Created on: 26 Sep 2017
 *      Author: fille
 */

#ifndef ASSEMBLY_H_
#define ASSEMBLY_H_


/* Includes */
#include <ESP8266WiFi.h>
#include <Servo.h>

#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>


/* Defines */
// General definitions
#define FALSE 0
#define TRUE 1

// SERVO defines
#define MAXROTATION 180
#define SERVOSPEED 20

// Calculation defines
#define DIFF 3.33
#define DZ 50

// IO pin defines
#define BLUELED 13 		// D7 GPIO13
#define GREENLED 12  	// D6 GPIO12
#define BUTTON 16      // D0 GPIO16
#define PHOTOTRANSISTOR A0
#define LIGHTCOUNTERLIMIT 1000

/* Public variables */
const char* ssid = "Molk";
const char* password = "Molk0901";

int ModeState = 0;

bool closeDone;
bool openDone;

int connectTimeOutCounter = 0;

int LightCounter = 0;

Servo myservo;        // D5 GPIO14
WiFiServer server(80);
WiFiClient client;
String request;

enum enumStatus{
	Open,
	Close,
	Photo,
};


/* Public functions */
void initWifi(void);
void initIO(void);
void runWeb(void);
void handleRequest(void);
void handleLayout(void);
void controlServo(int Status);



#endif /* ASSEMBLY_H_ */
