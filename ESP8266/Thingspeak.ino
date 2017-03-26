#include <SoftwareSerial.h>     // Required if using arduino uno or some other arduino which has only 1 serial port.

int sensor1State=1;     // Initial value of data to be sent.


String apiKey = "3GT71M7GQXPWQOQP";     // Thingspeak's channel apiKey.
void setup() {                
  
  Serial.begin(9600);     // Serial Monitor's baud rate.
  Serial3.begin(115200);      // Enable Wi-Fi serial. ESP8266's may have different baud rate's.
  
  Serial3.println("AT+RST");      // Reset ESP8266
  Serial3.println("AT+CWJAP=\"Bhagat Singh\",\"123456789\"");     // Wi-Fi's SSID and Password
}

void loop() {
  
  String state1=String(sensor1State);
  
  String cmd = "AT+CIPSTART=\"TCP\",\"";      // TCP connection(Default to connect to thingspeak's server)
  cmd += "184.106.153.149"; // api.thingspeak.com
  cmd += "\",80";
  Serial3.println(cmd);     // Sending the command to Wi-Fi Module
  Serial.println(cmd);
   
  if(Serial3.find("Error")){
    Serial.println("AT+CIPSTART error");      // Checking for any error's which usually doesn't occur.
    return;
  }
  
  String getStr = "GET /update?api_key=";     // Preparing a string to be sent.
  getStr += apiKey;
  getStr +="&field1=";      // Updating only field one's value
  getStr += String(state1);     // With our new value state1.
  
  getStr += "\r\n\r\n";

  // Length/Size of data must be sent before sending the data itself.
  
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  Serial3.println(cmd);
  Serial.println(cmd);

  if(Serial3.find(">")){      // If only a positive response('>') is received, the data is sent.
    Serial3.print(getStr);
    Serial.print(getStr);
  }
  else{
    Serial3.println("AT+CIPCLOSE");
    // alert user
    Serial.println("AT+CIPCLOSE");
  }
    
  delay(15000);     // Thingsspeak requires 15 seconds delay in between the updates.
  
  sensor1State=sensor1State+1;  
}
