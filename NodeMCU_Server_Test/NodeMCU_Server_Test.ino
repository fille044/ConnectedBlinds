/* Defines */
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

/* Static variables */
const char* ssid = "Molk";
const char* password = "Molk0901";
int ModeState = LOW;
int blueLed = 13; // D7
int greenLed = 12;  // D6
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
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
       delay(500);
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
    delay(10);
    pinMode(16, INPUT);
    pinMode(blueLed, OUTPUT);
    pinMode(greenLed, OUTPUT);
    digitalWrite(blueLed, LOW);
    digitalWrite(greenLed, LOW);
    initWifi();
}


/* ------------------------------------------------------*/
/*
   Main loop for functionality
*/
/* ------------------------------------------------------*/
void loop()
{
    // Check if a client has connected
    WiFiClient client = server.available();
    if (!client) {
        return;
    }

    // Wait until the client sends some data
    Serial.println("new client");
    while(!client.available()){
        delay(1);
    }

    // Read the first line of the request
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();

    // Match the request
    if (request.indexOf("/Manual") != -1) {
        if (digitalRead(16) == 0) {
            digitalWrite(blueLed, HIGH);
            digitalWrite(greenLed, HIGH);
            ModeState = 1;
        }
    }
    if (request.indexOf("/Manual") != -1) {
        if (digitalRead(16) == 1) {
            digitalWrite(blueLed, LOW);
            digitalWrite(greenLed, HIGH);
            ModeState = 2;
        }
    }
    if (request.indexOf("/Open") != -1) {
        digitalWrite(blueLed, HIGH);
        digitalWrite(greenLed, LOW);
        ModeState = 3;
    }
    if (request.indexOf("/Closed") != -1) {
        digitalWrite(blueLed, LOW);
        digitalWrite(greenLed, LOW);
        ModeState = 4;
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

    if(ModeState == 1) {
        client.print("Manual open");
    }
    else if (ModeState == 2) {
        client.print("Manual closed");
    }
    else if (ModeState == 3) {
        client.print("Automatic open");
    }
    else if (ModeState == 4) {
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
    Serial.println("");
}
