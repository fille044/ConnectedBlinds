/* Defines */
#include <ESP8266WiFi.h>
#include <Servo.h>

#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#define FALSE 0
#define TRUE 1
#define ON 0
#define OFF 1

#define MAX 180
#define SERVOSPEED 30

/* Static variables */
const char* ssid = "CB";
const char* password = "Molk0901";

int ModeState = 0;
int blueLed = 13; 		// D7
int greenLed = 12;  	// D6
int button = 16;

int servoPosition = 0;
bool closeDone;
bool openDone;

bool isTimeout = FALSE;
int timeoutCounter = 0;

bool isButtonPressed;
int prevButtonState = digitalRead(16);

Servo myservo;
WiFiServer server(80);


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

    initWifi();

    myservo.write(30);
    delay(1000);

    pinMode(button, INPUT);
    pinMode(blueLed, OUTPUT);
    pinMode(greenLed, OUTPUT);
    digitalWrite(blueLed, LOW);
    digitalWrite(greenLed, LOW);
}


/* ------------------------------------------------------*/
/*
   Sets servo max and min based on input state
*/
/* ------------------------------------------------------*/
void controlServo(int Status)
{
	// OPEN
	if (Status == 0 && openDone == FALSE) {
        digitalWrite(blueLed, HIGH);
		myservo.attach(14);

		// Runs servo slowly until end is reached
		for (int pos = 0; pos <= MAX ; pos++) {
			myservo.write(pos);
			delay(SERVOSPEED);
			if (pos == MAX) {
				openDone = TRUE;
				closeDone = FALSE;
				Serial.println("Open done");
				myservo.detach();    // To eliminate noise
			}
		}
	}
	// CLOSE
	if (Status == 1 && closeDone == FALSE) {
        digitalWrite(blueLed, LOW);
		myservo.attach(14);

		// Runs servo slowly until end is reached
		for (int pos = MAX; pos >= 0 ; pos--) {
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
}


/* ------------------------------------------------------*/
/*
   Goes through the different states of modes and calls function
   servo setting
*/
/* ------------------------------------------------------*/
void function(void)
{
	enum enumStatus{
		Open,
		Close,
	};

	switch (ModeState) {
	case 0:
		// Manual Open
        if (digitalRead(16) == 1) {
            digitalWrite(greenLed, HIGH);
            controlServo((int)Open);
        }
        // Manual Close
        else if (digitalRead(16) == 0) {
        	digitalWrite(greenLed, HIGH);
            controlServo((int)Close);
        }
		break;

	case 1:
		// Auto Open
        digitalWrite(greenLed, LOW);
        controlServo((int)Open);
		break;

	case 2:
		// Auto Close
        digitalWrite(greenLed, LOW);
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
	if (prevButtonState != digitalRead(16)) {
		ModeState = 0;
	}
	prevButtonState = digitalRead(16);
    function();
    int counter = 0;
    // Check if a client has connected
    WiFiClient client = server.available();
    if (!client) {
        return;
    }

    // Wait until the client sends some data
    Serial.println("new client");
    while(!client.available()) {
        delay(1);
        Serial.println(counter);
        counter++;
        if (counter > 500) {
        	return;
        }
    }

    // Read the first line of the request
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();

    // Match the request
    if (request.indexOf("/Manual") != -1) {
        ModeState = 0;
    }
    if (request.indexOf("/Open") != -1) {
        ModeState = 1;
    }
    if (request.indexOf("/Closed") != -1) {

        ModeState = 2;
    }

    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); //  do not forget this one
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head><title>ConnectedBlinds</title></head>");
    client.println("<body>");
    client.print("Mode is now: ");

    if(ModeState == 0) {
        client.print("Manual");
    }
    else if (ModeState == 1) {
        client.print("Automatic open");
    }
    else if (ModeState == 2) {
        client.print("Automatic closed");
    }

    client.println("<br>-----------------------------------------------</br>");
    client.println("<br><br>");
    client.println("<a href=\"/Manual\"\"><button>Manual</button></a>");
    client.println("<br><br>");
    client.println("<a href=\"/Open\"\"><button>Open</button></a>");
    client.println("<a href=\"/Closed\"\"><button>Closed</button></a>");
    client.println("</body>");
    client.println("</html>");

    delay(1);
    Serial.println("Ready");
}
