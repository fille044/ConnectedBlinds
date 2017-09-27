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
    if (request.indexOf("/Auto") != -1) {
        ModeState = 0;
    }
    if (request.indexOf("/Open") != -1) {

        ModeState = 1;
    }
    if(request.indexOf("/Closed") != -1) {
        ModeState = 2;
    }
}


/* ------------------------------------------------------*/
/*
   Build webpage in HTML with variable ModeState
*/
/* ------------------------------------------------------*/
void handleLayout(void)
{
	// Return the response
	client.println("HTTP/1.1 200 OK");
	client.println("Content-Type: text/html");
	client.println(""); //  do not forget this one
	client.println("<!DOCTYPE HTML>");
	client.println("<html>");
	client.println("<head><title>ConnectedBlinds</title></head>");
	client.println("<style>");

	client.println(".button {");
	client.println("display: inline-block;");
	client.println("padding: 15px 25px;");
	client.println("font-size: 24px;");
	client.println("cursor: pointer;");
	client.println("text-align: center;");
	client.println("text-decoration: none;");
	client.println("outline: none;");
	client.println("color: #fff;");
	client.println("background-color: #cc0000;");
	client.println("border: none;");
	client.println("border-radius: 15px;");
	client.println("box-shadow: 0 9px #999;");
	client.println("}");

	client.println(".button:focus{");
	client.println("background:#990000;");
	client.println("}");

	client.println(".button:hover {background-color: #990000");
	client.println("}");

	client.println(".button:active {");
	client.println("background-color: #990000;");
	client.println("box-shadow: 0 5px #666;");
	client.println("transform: translateY(4px);");
	client.println("}");

	client.println(".button1 {");
	client.println("display: inline-block;");
	client.println("padding: 15px 25px;");
	client.println("font-size: 24px;");
	client.println("cursor: pointer;");
	client.println("text-align: center;");
	client.println("text-decoration: none;");
	client.println("outline: none;");
	client.println("color: #fff;");
	client.println("background-color: #4CAF50;");
	client.println("border: none;");
	client.println("border-radius: 15px;");
	client.println("box-shadow: 0 9px #999;");
	client.println("}");

	client.println(".button1:focus{");
	client.println("background:#009900;");
	client.println("}");

	client.println(".button1:hover {background-color: #009900}");
	client.println(".button1:active {");
	client.println("background-color: #006600;");
	client.println("box-shadow: 0 5px #666;");
	client.println("transform: translateY(2px);");
	client.println("}");

	client.println("h1 {");
	client.println("text-align: left;");
	client.println("text-transform: uppercase;");
	client.println("font-family: 'Poppins', sans-serif;");
	client.println("color: #4CAF50;");
	client.println("}");

	client.println("</style>");
	client.println("<body bgcolor=#f1e4da>");
	client.print("<h1>Mode is now:</h1>");

	if (ModeState == 0) {
        client.print("<h1>Auto</h1>");
        client.println("<br><br>");
        client.println("<a href=\"/Open\"\"><button class=button>Open</button></a>");
        client.println("<a href=\"/Closed\"\"><button class=button>Closed</button></a>");
        client.println("<a href=\"/Auto\"\"><button class=button1>Auto</button></a>");
        client.println("<br><br>");
        client.println("</body>");
        client.println("</html>");
    }
    else if (ModeState == 1){
        client.print("<h1>Open</h1>");
        client.println("<br><br>");
        client.println("<a href=\"/Open\"\"><button class=button1>Open</button></a>");
        client.println("<a href=\"/Closed\"\"><button class=button>Closed</button></a>");
        client.println("<a href=\"/Auto\"\"><button class=button>Auto</button></a>");
        client.println("<br><br>");
        client.println("</body>");
        client.println("</html>");
    }
    else if (ModeState == 2){
        client.print("<h1>Closed</h1>");
        client.println("<br><br>");
        client.println("<a href=\"/Open\"\"><button class=button>Open</button></a>");
        client.println("<a href=\"/Closed\"\"><button class=button1>Closed</button></a>");
        client.println("<a href=\"/Auto\"\"><button class=button>Auto</button></a>");
        client.println("<br><br>");
        client.println("</body>");
        client.println("</html>");
    }
    delay(1);
    Serial.println("Ready");
}


