/*
 * web.ino
 *
 *  Created on: 26 Sep 2017
 *      Author: fille
 */


#include "assembly.h"


/* ------------------------------------------------------*/
/*
   Handles the functions for wepage layout and request
*/
/* ------------------------------------------------------*/
void runWeb(void)
{
	handleRequest();
	handleLayout();
}


/* ------------------------------------------------------*/
/*
   Checks requests from webpage input and sets ModeState to
   corresponding value, between 0-3.
*/
/* ------------------------------------------------------*/
void handleRequest(void)
{
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
    if(request.indexOf("/Phototransistor") != -1) {
        ModeState = 3;
    }
}


/* ------------------------------------------------------*/
/*
   Build webpage in HTML with variable ModeState
*/
/* ------------------------------------------------------*/
void handleLayout(void)
{
    // Return the response and build webpage
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
        client.print("Web open");
    }
    else if (ModeState == 2) {
        client.print("Web closed");
    }
    else if (ModeState == 3) {
    	client.print("Photo");
    }

    client.println("<br>-----------------------------------------------</br>");
    client.println("<br><br>");
    client.println("<a href=\"/Manual\"\"><button>Manual</button></a>");
    client.println("<a href=\"/Phototransistor\"\"><button>Phototransistor</button></a>");
    client.println("<br><br>");
    client.println("<a href=\"/Open\"\"><button>Open</button></a>");
    client.println("<a href=\"/Closed\"\"><button>Closed</button></a>");
    client.println("<br><br>");
    client.println("</body>");
    client.println("</html>");
}


