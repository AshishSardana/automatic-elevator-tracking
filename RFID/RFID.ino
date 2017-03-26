#include <SPI.h>
#include <MFRC522.h>      // Downloaded

#define RST_PIN         5          // Default Configuration
#define SS_PIN          53         

MFRC522 mfrc522(SS_PIN, RST_PIN);     // Create MFRC522 instance

void setup() {
  Serial.begin(9600);     // Initialize serial communications with the PC
  SPI.begin();      
  mfrc522.PCD_Init();     // Initialise MFRC522
  mfrc522.PCD_DumpVersionToSerial();      // Show details of PCD - MFRC522 Card Reader details
}

void loop() {
  // Look for new cards
  
  if ( ! mfrc522.PICC_IsNewCardPresent())
    return;
  if ( ! mfrc522.PICC_ReadCardSerial())
    return;
  
  Serial.println(F("The NUID tag is:"));
  sendHex(mfrc522.uid.uidByte, mfrc522.uid.size);
  Serial.println();
}

void sendHex(byte *buffer, byte bufferSize)
{
  byte t[4][4] = {{06,79,203,50},{245,52,177,107},{237,172,177,101},{243,131,16,43}};
  byte temp[4];
  byte c=0,s=0;
  Serial.println(bufferSize);
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.println(buffer[i]);
    temp[i]=buffer[i];
  }
  Serial.println("Finding the corresponding UID i.e floor number");

   for(byte j=0;j<4;j++)
   { 
    for(byte k=0;k<4;k++)
    {
      if(temp[k]==t[j][k])
      c++;
    }
    if(c==4) 
      {Serial.println("FLOOR NO.:");
      s=j;
      }
    c=0;
    }
    Serial.println(s);
}


