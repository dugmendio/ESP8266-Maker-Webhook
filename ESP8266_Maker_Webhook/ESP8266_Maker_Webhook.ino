/*
 * Base code thanks to Henrik @ https://arduino.stackexchange.com/a/32641
 * I have added configuration strings and GET request has been fixed
 */

#include <SoftwareSerial.h>

/*Config strings*/
String SSID = "****";
String KEY = "****";

String HOST = "maker.ifttt.com";
String COMMAND = "/trigger/trigger_word/with/key/abc1234";
const byte txPin = 7; //TX of ESP to pin 7
const byte rxPin = 6; //RX of ESP to pin 6

SoftwareSerial ESP8266 (txPin, rxPin);
unsigned long lastTimeMillis = 0;
long baud = 115200; //Depends on the firmware


void setup() {
  Serial.begin(baud);   
  ESP8266.begin(baud);
  
  delay(1000);
  // This will run better if you configure the WiFi commands seperately. 
  // I suggest configuring the connection and and removing this.
  ESP8266.println("AT+CWJAP=\"" + SSID + "\",\"" + KEY + "\"");
  delay(1000);
  printResponse();

  //Start multi IP connection
  ESP8266.println("AT+CIPMUX=1");
  delay(1000);
  printResponse();

  //WiFi mode to client
  delay(1000);
  ESP8266.println("AT+CWMODE=1");
  delay(1000);
}

void printResponse() {
  while (ESP8266.available()) {
    Serial.println(ESP8266.readStringUntil('\n')); 
  }
}

void loop() {
  if (millis() - lastTimeMillis > 30000) {
    lastTimeMillis = millis();

    //Connects to host
    ESP8266.println("AT+CIPSTART=4,\"TCP\",\"" + HOST + "\",80");
    delay(1000);
    printResponse();

    //Sends connection string 
    String cmd = "GET "+ COMMAND + " HTTP/1.1\r\nHost:" + HOST + "\r\n\r\n";
    ESP8266.println("AT+CIPSEND=4," + String(cmd.length() + 4));
    delay(1000);

    //Sends GET command
    ESP8266.println(cmd);
    delay(1000);
    ESP8266.println(""); 

    //Stop connection (Could be handled more gracefully)
    while(1);
  }

  if (ESP8266.available()) {
    Serial.write(ESP8266.read());
  }
}
