#include <SPI.h>                   // Serial Peripheral Interface
#include <MFRC522.h>               // Library for RFID(MFRC522)
#include <LiquidCrystal.h>
#define RST_PIN         5          // Configurable pin for RFID
#define SS_PIN          53         // Configurable pin for RFID
String apiKey = "3GT71M7GQXPWQOQP";
byte t[4][4] = {{06,79,203,50},{245,52,177,107},{237,172,177,101},{243,131,16,43}};
byte temp[4];
byte c=0,s=0;
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
LiquidCrystal lcd(36, 37, 34, 35, 32, 33);

void setup() {
  // LCD initialisation
  lcd.begin(16, 2);
  lcd.setCursor(1,0);
  lcd.print("MATE: RealTime");
  lcd.setCursor(0,1);
  lcd.print("Elevator Tracker");
  
  Serial.begin(9600);             // Initialize serial communications with the PC

  SPI.begin();      
  mfrc522.PCD_Init();     
  mfrc522.PCD_DumpVersionToSerial();  
  
  Serial3.begin(115200);
  Serial3.println("AT+RST");          
  Serial3.println("AT+CWJAP=\"Bhagat Singh\",\"ashish123\"");
}
void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  sendHex(mfrc522.uid.uidByte, mfrc522.uid.size);
  Serial.println(); 
}
void sendHex(byte *buffer, byte bufferSize)
{
  c=0;
  s=0;
  for (byte i = 0; i < bufferSize; i++) {
    temp[i]=buffer[i];                               
  }
  for(byte j=0;j<bufferSize;j++){
    c=0;
    for(byte k=0;k<bufferSize;k++){
      if(temp[k]==t[j][k])
        c++;
        }
    if(c==4){
      s=j*10;
      uploadData(s);
      break;
    }
  }
    
}

// Uploading data to thingspeak

void uploadData(int s){
  lcd.clear();
  String state=String(s);
  lcd.print("Lift Floor: " + state);
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149"; // api.thingspeak.com
  cmd += "\",80";
  Serial3.println(cmd);
  Serial.println(cmd);
  if(Serial3.find("Error")){
    Serial.println("AT+CIPSTART error");
    return;
  }
  String getStr = "GET /update?api_key=";
  getStr += apiKey;
  getStr +="&field1=";
  getStr += String(state);
  getStr += "\r\n\r\n";
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  Serial3.println(cmd);
  Serial.println(cmd);
  if(Serial3.find(">")){
    Serial3.print(getStr);
    Serial.print(getStr);
  }
  else{
    Serial3.println("AT+CIPCLOSE");
    Serial.println("AT+CIPCLOSE");
  }
  delay(15000);
}

