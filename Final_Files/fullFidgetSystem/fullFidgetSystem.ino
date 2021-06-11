/*
 * By: Bayan Assali, Ibrahim Nayfeh, and Gelila Kebede
 * Date: 11 June 2021
 * 
 * Senses fidgeting motion, displays a calming mechanism when fidget threshhold is met. 
 * User selects number of breaths/calming intervals from the associated webpage
 * 
 * Website refernces:
 * Elochukwu Ifediora (fedy0)
 * Prince Steven Annor
 * 
 * Sensor refernces:
 * Mike Klepper 
 * Patrio Geek blog
 * ATOM Matrix: Using the MPU6886 Accelerometer - 
 *  Detect a Shake and Roll a Die, aka AccelerometerTest03.ino
 *  
 */

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <Arduino.h>
#include "M5Atom.h"
#include "millisDelay.h"

//Website varriables 
// Set these to your desired credentials.
const char *ssid = "group16AP";
const char *password = "ToPieces";

long var = 0;

WiFiServer server(80);

//Fidget variables
//Set up accel varriables 
float accX = 0, accY = 0, accZ = 0;

//Set up fidget checks
bool fidgetState = false;
int fidgetCtr = 0;

//Set up time varriables
int timeCheck = 0;
int interval = 3000;

//Set up screen
uint32_t blue = 0x0000ff; // blue color to test
int screenInterval = 1000;
int screenDuration = 0;
bool screenOff = true;

//Screen color values
uint32_t black = 0x0000; 
uint32_t blue1 = 0x0000ff; // blue color to test
uint32_t L1color = 0xD1EEEE;  // light cyan2
uint32_t L2color = 0xADEAEA;  // turquoise
uint32_t L3color = 0x70DBDB;  // medium turquoise
uint32_t L4color = 0x00CED1;  // dark turquoise (SVG)
uint32_t L5color = 0x00868B;  // turquoise4

//Spiral display timer
millisDelay Delay; 
int Screeninterval = 900;
int i = 0; // counter
int breathCtr = 5; //Breath counter
int breathWebInput = 5; //Determines number of breaths from the website


void setup() {
  //Website setup
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");

  //Fidget setup
  M5.begin(true,false, true);
  M5.IMU.Init(); 
  M5.dis.setBrightness(20);
}

void loop() {
  runWebsite(); //Funtion that runs the associated website

  M5.IMU.getAccelData(&accX, &accY, &accZ);   //Get movement data
  timeCheck = millis() + interval;
  while(timeCheck > millis()){
    if(abs(accX) > 2 || abs(accY) > 2){       //Senses movement
      fidgetState = true;
    }
    if(abs(accX) < 1 &&  abs(accY) < 1){      //Sets up counter to differentiate natural movement and fidgeting
      fidgetState = false;
    }
    if(fidgetState == true){                  //Increments if fidgeting
      fidgetCtr++;
    }
    if(fidgetState == false){                 //Decay if not fidgeting
      fidgetCtr = (0.99 * fidgetCtr);
    }
  }
  if(fidgetCtr > 4){                          //Sets threshold and tiggers calming if threshold is met, then resets
    setBreaths();
    for(breathCtr; breathCtr > 0; breathCtr--){
      calmScreen();
    }
    fidgetCtr = 1;
    setBreaths();
  } else {
    fidgetCtr = 1; 
  }
  M5.update();
}

//Functions that control fidget sensor
//Sets number of breaths based on website
void setBreaths(){
  breathCtr = breathWebInput;
}

//Displays calming screen
void calmScreen(){
  Delay.start(Screeninterval);
  i++;
  
  while(i > 0){
  displaySpiral();
  }
}

//Determines if the wearer is fidgetting or moving naturally
void fidgetTimer(){
  timeCheck = millis() + interval;
  while(timeCheck > millis()){
    if(abs(accX) > 2 || abs(accY) > 2){
      fidgetState = true;
    }
    if(abs(accX) < 1 &&  abs(accY) < 1){
      fidgetState = false;
    }
    if(fidgetState == true){
      fidgetCtr++;
    }
    if(fidgetState == false){
      fidgetCtr = (0.9 * fidgetCtr);
    }
  }
  if(fidgetCtr > 10){
    M5.dis.fillpix(blue);
  } else {
    fidgetCtr = 0; 
  }
}

//Sequence of pixels at set colors for an inhale/hold/exhale breathing sequence
void displaySpiral(){
    switch (i){
      case 0:
        M5.dis.clear();
        break;
      case 1:
        M5.dis.fillpix(L5color);
        CheckDelay();
        break;
      case 2:
        M5.dis.clear();
        CheckDelay();
        break;
      case 3:
        M5.dis.fillpix(L5color);
        CheckDelay();
        break;
      case 4: 
        M5.dis.drawpix(12,L1color); // sets the center pixel to the color we choose
        CheckDelay(); // calls function to check the delay
        break;
      case 5: //Inner diamond
        M5.dis.drawpix(7,L2color);
        M5.dis.drawpix(11,L2color);
        M5.dis.drawpix(13,L2color);
        M5.dis.drawpix(17,L2color);
        CheckDelay();
        break;
      case 6:
        M5.dis.drawpix(2,L3color);
        M5.dis.drawpix(6,L3color);
        M5.dis.drawpix(8,L3color);
        M5.dis.drawpix(10,L3color);
        M5.dis.drawpix(14,L3color);
        M5.dis.drawpix(16,L3color);
        M5.dis.drawpix(18,L3color);
        M5.dis.drawpix(22,L3color);
        CheckDelay();
        break;
      case 7: 
        M5.dis.drawpix(1,L4color);
        M5.dis.drawpix(5,L4color);
        M5.dis.drawpix(3,L4color);
        M5.dis.drawpix(9,L4color);
        M5.dis.drawpix(15,L4color);
        M5.dis.drawpix(19,L4color);
        M5.dis.drawpix(21,L4color);
        M5.dis.drawpix(23,L4color);
        CheckDelay();
        break;
      case 8: 
        M5.dis.drawpix(0,L5color);
        M5.dis.drawpix(4,L5color);
        M5.dis.drawpix(20,L5color);
        M5.dis.drawpix(24,L5color);
        CheckDelay();
        break;
      case 9:
        M5.dis.drawpix(0,L5color);
        M5.dis.drawpix(1,L5color);
        M5.dis.drawpix(2,L5color);
        M5.dis.drawpix(3,L5color);
        M5.dis.drawpix(4,L5color);
        M5.dis.drawpix(5,L5color);
        M5.dis.drawpix(9,L5color);
        M5.dis.drawpix(10,L5color);
        M5.dis.drawpix(14,L5color);
        M5.dis.drawpix(15,L5color);
        M5.dis.drawpix(19,L5color);
        M5.dis.drawpix(20,L5color);
        M5.dis.drawpix(21,L5color);
        M5.dis.drawpix(22,L5color);
        M5.dis.drawpix(23,L5color);
        M5.dis.drawpix(24,L5color);
        M5.dis.drawpix(6,L3color);
        M5.dis.drawpix(7,L3color);
        M5.dis.drawpix(8,L3color);
        M5.dis.drawpix(11,L3color);
        M5.dis.drawpix(13,L3color);
        M5.dis.drawpix(16,L3color);
        M5.dis.drawpix(17,L3color);
        M5.dis.drawpix(18,L3color);
        M5.dis.drawpix(12,L1color);
        CheckDelay();
        break;
      case 10:
        M5.dis.clear();
        CheckDelay();
        break;  
      case 11:
        M5.dis.drawpix(0,L5color);
        M5.dis.drawpix(1,L5color);
        M5.dis.drawpix(2,L5color);
        M5.dis.drawpix(3,L5color);
        M5.dis.drawpix(4,L5color);
        M5.dis.drawpix(5,L5color);
        M5.dis.drawpix(9,L5color);
        M5.dis.drawpix(10,L5color);
        M5.dis.drawpix(14,L5color);
        M5.dis.drawpix(15,L5color);
        M5.dis.drawpix(19,L5color);
        M5.dis.drawpix(20,L5color);
        M5.dis.drawpix(21,L5color);
        M5.dis.drawpix(22,L5color);
        M5.dis.drawpix(23,L5color);
        M5.dis.drawpix(24,L5color);
        M5.dis.drawpix(6,L3color);
        M5.dis.drawpix(7,L3color);
        M5.dis.drawpix(8,L3color);
        M5.dis.drawpix(11,L3color);
        M5.dis.drawpix(13,L3color);
        M5.dis.drawpix(16,L3color);
        M5.dis.drawpix(17,L3color);
        M5.dis.drawpix(18,L3color);
        M5.dis.drawpix(12,L1color);
        CheckDelay();
        break;
      case 12:
        M5.dis.drawpix(0,L5color);
        M5.dis.drawpix(1,L5color);
        M5.dis.drawpix(2,L5color);
        M5.dis.drawpix(3,L5color);
        M5.dis.drawpix(4,L5color);
        M5.dis.drawpix(5,L5color);
        M5.dis.drawpix(9,L5color);
        M5.dis.drawpix(10,L5color);
        M5.dis.drawpix(14,L5color);
        M5.dis.drawpix(15,L5color);
        M5.dis.drawpix(19,L5color);
        M5.dis.drawpix(20,L5color);
        M5.dis.drawpix(21,L5color);
        M5.dis.drawpix(22,L5color);
        M5.dis.drawpix(23,L5color);
        M5.dis.drawpix(24,L5color);
        CheckDelay();
        break;
      case 13:
        M5.dis.drawpix(6,L3color);
        M5.dis.drawpix(7,L3color);
        M5.dis.drawpix(8,L3color);
        M5.dis.drawpix(11,L3color);
        M5.dis.drawpix(13,L3color);
        M5.dis.drawpix(16,L3color);
        M5.dis.drawpix(17,L3color);
        M5.dis.drawpix(18,L3color);
        CheckDelay();
        break;
      case 14: 
        M5.dis.drawpix(12,L1color);
        CheckDelay();
        break;
      case 15:
        M5.dis.clear();
        CheckDelay();
        break;   
      default:
        break;
    }
    
    if(i == 16) 
      i = 0; // resets counter
}

void CheckDelay(){ // functions that checks if delay ended and sets screen to black
  if(Delay.justFinished())
  {
    Delay.repeat();
    M5.dis.fillpix(black);
    i++; // increments counter
  } 
}

//Function that sets up, connects to, and runs website
void runWebsite(){
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        //Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /FIVE")) {
          Serial.println("5 BREATHS");
          client.println("5 BREATHS");
          breathWebInput = 5;
        }
        if (currentLine.endsWith("GET /SIX")) {
          Serial.println("6 BREATHS");
          client.println("6 BREATHS");
          breathWebInput = 6;
        }
        if (currentLine.endsWith("GET /SEVEN")) {
          //INTERESTING PART 2
          Serial.println("7 BREATHS");
          client.println("7 BREATHS");
          breathWebInput = 7;
        }
        if (currentLine.endsWith("GET /EIGHT")) {
          //INTERESTING PART 2
          Serial.println("8 BREATHS");
          client.println("8 BREATHS");
          breathWebInput = 8;
        }
        if (currentLine.endsWith("GET /home")) {
          Serial.println("Home");

          // html and javascript code sent to the browser
          /*

            <!DOCTYPE HTML>
            <html>
            <head>
            <script type="text/javascript">
            window.onload = function() {
            httpGetAsync("/value");
            function httpGetAsync(theUrl) {
            var xmlHttp = new XMLHttpRequest();
            var frequency_val = 1000;
            xmlHttp.onreadystatechange = function() {
            if (xmlHttp.readyState == 4 && xmlHttp.status == 200)
                document.getElementById("val").innerHTML = xmlHttp.responseText; }
            xmlHttp.open("GET", theUrl, true);
            xmlHttp.send(null);
            
            setTimeout(function(){httpGetAsync("/value")}, frequency_val); } }
            </script>
            
            <style>
              html, body{
                width: 100%;
                height: 100%;
                margin: 0;
                padding: 0;
                background-color:white;
              }
              #container {
                width: inherit;
                height: inherit;
                margin: 0;
                padding: 0;
                background-color: white;
              }
            </style>
            </head>
            <body>
              <div id="container">
            <h1 style="font-family: sans-serif; font-size: 38px; display: inline; color: gray">Fidget Sensor Calming Function</h1><br>
            <h2 style="font-weight: 100; font-size: 30px; display: inline; color:black">How many breaths would you like to take?</h2><br>
            <form action="/FIVE">
                <input style="font-size: 20px; width: 400px; height: 100px;" type="submit" value="Five Breaths" />
            </form>
            <form action="/SIX">
                <input style="font-size: 20px; width: 400px; height: 100px;" type="submit" value="Six Breaths" />
            </form>
            <form action="/SEVEN">
                <input style="font-size: 20px; width: 400px; height: 100px;" type="submit" value="Seven Breaths" />
            </form>
            <form action="/EIGHT">
                <input style="font-size: 20px; width: 400px; height: 100px;" type="submit" value="Eight Breaths" />
            </form>
            </div>
            </body>
            </html>
          */

          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<head>");
          client.println("<script type=\"text/javascript\">");
          client.println("window.onload = function() {");
          client.println("httpGetAsync(\"/value\");");
          client.println("function httpGetAsync(theUrl) { ");
          client.println("var xmlHttp = new XMLHttpRequest();");
          client.println("var frequency_val = 1000;");
          client.println("xmlHttp.onreadystatechange = function() { ");
          client.println("if (xmlHttp.readyState == 4 && xmlHttp.status == 200)");
          client.println("document.getElementById(\"val\").innerHTML = xmlHttp.responseText; }");
          client.println("xmlHttp.open(\"GET\", theUrl, true); ");
          client.println("xmlHttp.send(null)");
          client.println("setTimeout(function(){httpGetAsync(\"/value\")}, frequency_val); } }");
          client.println("</script>");
          client.println("<style>");
          client.println("html, body{");
          client.println("width: 100%;");
          client.println("height: 100%;");
          client.println("margin: 0;");
          client.println("padding: 0;");
          client.println("background-color:white;");
          client.println("}");
          client.println("#container {");
          client.println("width: inherit;");
          client.println("height: inherit;");
          client.println("margin: 0;");
          client.println("padding: 0;");
          client.println("background-color: white;");
          client.println("}");
          client.println("</style>");
          client.println("</head>");
          client.println("<body>");
          client.println("<div id=\"container\">");
          client.println("<h1 style=\"font-family: sans-serif; font-size: 30px; display: inline; color: gray\">Fidget Sensor Calming Function</h1><br>");
          client.println("<h2 style=\"font-weight: 100; font-size: 28px; display: inline; color:black\">How many breaths would you like to take?</h2><br>");
          client.println("<form action=\"/FIVE\">");
          client.println("<input style=\"font-size: 16px; width: 450px; height: 100px;\" type=\"submit\" value=\"Five Breaths\"/>");
          client.println("</form>");
          client.println("<form action=\"/SIX\">");
          client.println("<input style=\"font-size: 16px; width: 450px; height: 100px;\" type=\"submit\" value=\"Six Breaths\"/>");
          client.println("</form>");
          client.println("<form action=\"/SEVEN\">");
          client.println("<input style=\"font-size: 16px; width: 450px; height: 100px;\" type=\"submit\" value=\"Seven Breaths\"/>");
          client.println("</form>");
          client.println("<form action=\"/EIGHT\">");
          client.println("<input style=\"font-size: 16px; width: 450px; height: 100px;\" type=\"submit\" value=\"Eight Breaths\"/>");
          client.println("</form>");
          client.println("</div>");
          client.println("</body>");
          client.println("</html>");
        }

        if (currentLine.endsWith("GET /value")) {
          var++;
          Serial.println(var);
          client.println(var);
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
