// Load Wi-Fi library
#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid     = "WiFi name";
const char* password = "Your password";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String LIGHT_TOW_VALUE = "off";
String LIGHT_ONE_VALUE = "off";
String HEATER_VALUE = "off";
String humidity_="";
String temperature_="";
String myipaddress = "" ;


void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi network with SSID and password
  //Serial.print("Connecting to ");
//  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  //Print local IP address and start web server
  //Serial.println("");
  //Serial.println("WiFi connected.");
  //Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
    
}

void loop(){
  
  WiFiClient client = server.available();   // Listen for incoming clients
 
  if (client) {                             // If a new client connects,
    //Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
   
    if(Serial.available()){
       String getvalue ="";
      
       temperature_ = Serial.readStringUntil('\n');
       for(int i =0 ; i < temperature_.length(); i++){
           if(temperature_[i]!= 'b')
              getvalue+= temperature_[i];
           else
            {
                humidity_ = getvalue;
                getvalue = "";
            }
        }
       temperature_ = getvalue;
   }
       
      if (client.available()) {             // if there's bytes to read from the client,
        
        char c = client.read();             // read a byte, then
        //Serial.println(c);                    // print it out the serial monitor
        header += (c);
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /LightOne/on") >= 0) {
              Serial.println("11"); 
              LIGHT_ONE_VALUE = "on";
              
            } else if (header.indexOf("GET /LightOne/off") >= 0) {
              Serial.println("10");
              LIGHT_ONE_VALUE = "off";
            } else if (header.indexOf("GET /LightTow/on") >= 0) {
              Serial.println("21");
              LIGHT_TOW_VALUE = "on";
            } else if (header.indexOf("GET /LightTow/off") >= 0) {
              Serial.println("20");
              LIGHT_TOW_VALUE = "off";
            }else if (header.indexOf("GET /heater/on") >= 0) {
              Serial.println("31");
              HEATER_VALUE = "on";
             
            }else if (header.indexOf("GET /heater/off") >= 0) {
               Serial.println("30");
               HEATER_VALUE = "off";
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px; width: 100%;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>Home Automation</h1>");
            
            // Display current state, and ON/OFF buttons for Light One  
            client.println("<p>Light One - State " + LIGHT_ONE_VALUE + "</p>");
            
            // If the LIGHT_ONE_VALUE is off, it displays the ON button       
            if (LIGHT_ONE_VALUE=="off") {
              client.println("<p><a href=\"/LightOne/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/LightOne/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for Light Tow 
            client.println("<p>Light Tow - State " + LIGHT_TOW_VALUE + "</p>");
            
            // If the output4State is off, it displays the ON button       
            if (LIGHT_TOW_VALUE=="off") {
              client.println("<p><a href=\"/LightTow/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/LightTow/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

             // Display current state, and ON/OFF buttons for heater 
            client.println("<p>Heater - State " + HEATER_VALUE + "</p>");
            
            // If the output4State is off, it displays the ON button       
            if (HEATER_VALUE=="off") {
              client.println("<p><a href=\"/heater/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/heater/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            
            //Display  Humidity and Temperature;  
            client.println("<br/>");
            client.println("<br/>");
            client.println("<h3>Humidity : </h3>" + humidity_);
            client.println("<h3>Temperature</h3>" + temperature_);      
            client.println("</body></html>");
           
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();

  }
  
}
