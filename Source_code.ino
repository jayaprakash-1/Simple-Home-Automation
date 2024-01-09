#include <WiFi.h>

const char* ssid     = "2710";
const char* password = "11111111";

unsigned long int previous_millis = 0;
unsigned long int interval = 1000;
IPAddress static_IP(192,168,240,100);
IPAddress gateway(192,168,240,1);
IPAddress subnet(255,255,0,0);
WiFiServer server(80);
void setup()
{
    Serial.begin(115200);
    pinMode(26, OUTPUT);      
    pinMode(25,OUTPUT);
    delay(10);
    digitalWrite(26,LOW);
    digitalWrite(26,LOW);
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
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    server.begin();
}

void loop(){

 WiFiClient client = server.available();
  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client1.println("HTTP/1.1 200 OK");
            client1.println("Content-type:text/html");
            client1.println();

            // the content of the HTTP response follows the header:
            client1.print("Click <a href=\"/H1\">here</a> to turn the LED on pin 26 on.<br>");
            client1.print("Click <a href=\"/L1\">here</a> to turn the LED on pin 26 off.<br>");
            client1.print("Click <a href=\"/H2\">here</a> to turn the FAN on pin 25 on.<br>");
            client1.print("Click <a href=\"/L2\">here</a> to turn the FAN on pin 25 off.<br>");
            // The HTTP response ends with another blank line:
            client1.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H1")) {
          digitalWrite(26, HIGH);               // GET /H turns the Relay 1 on
        }
        if (currentLine.endsWith("GET /L1")) {
          digitalWrite(26, LOW);                // GET /L turns the Relay 1 off
        }
        if (currentLine.endsWith("GET /H2")) {
          digitalWrite(25, HIGH);               // GET /H turns the Relay 2 on
        }
        if (currentLine.endsWith("GET /L2")) {
          digitalWrite(25, LOW);                // GET /L turns the Relay 2 off
        }
      }
    }
    // close the connection:
    client1.stop();
    Serial.println("Client Disconnected.");
  }
  while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
}
