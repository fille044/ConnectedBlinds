/*
 * declaration.h
 *
 *  Created on: 20 Sep 2017
 *      Author: fille
 */

#ifndef DECLARATION_H_
#define DECLARATION_H_


#define FALSE 0
#define TRUE 1
#define ON 0
#define OFF 1

#define MAX 180
#define SERVOSPEED 30


/* Static variables */
const char* ssid = "ConnectB";
const char* password = "12345678";

Servo myservo;
WiFiServer server(80);
WiFiClient client;

int light = 0;
const byte phototransistor = A0;
const byte blueLed = 13; 		// D7
const byte greenLed = 12;  	// D6
const byte button = 16;

bool isTimeout = FALSE;
int timeoutCounter = 0;

/* Function declarations */
void initWifi(void);
void buildWebpage(void);

int ModeState = 0;


#endif /* DECLARATION_H_ */
