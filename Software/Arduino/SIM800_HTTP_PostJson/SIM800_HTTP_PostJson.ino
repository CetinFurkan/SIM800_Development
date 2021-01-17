#include <ArduinoJson.h>
StaticJsonDocument<200> jsonBuffer;
#include <SoftwareSerial.h>

SoftwareSerial mySerial(7, 8);

char t[32];
char deviceID[12] = "MYTEST56";

void setup()
{
  mySerial.begin(9600);        // the GPRS baud rate
  Serial.begin(9600);
  Serial.println("Initializing..........");

  DynamicJsonDocument jsonBuffer(200);

  delay(1000);
}

void loop()
{
  Serial.println("");
  Serial.println("************************************************************");

  if (mySerial.available())
    Serial.write(mySerial.read());

  mySerial.println("AT");
  delay(3000);

  //mySerial.println("AT+CSTT=\"internet\",\"vodafone\",\"vodafone\"");
  //delay(4000);
  //ShowSerialData();

  mySerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  delay(6000);
  ShowSerialData();

  mySerial.println("AT+SAPBR=3,1,\"APN\",\"internet\"");//APN
  delay(4000);
  ShowSerialData();
  
  mySerial.println("AT+SAPBR=3,1,\"USER\",\"vodafone\"");//APN
  delay(4000);
  ShowSerialData();
  
  mySerial.println("AT+SAPBR=3,1,\"PWD\",\"vodafone\"");//APN
  delay(4000);
  ShowSerialData();

  mySerial.println("AT+SAPBR=1,1");
  delay(6000);
  ShowSerialData();

  mySerial.println("AT+SAPBR=2,1");
  delay(6000);
  ShowSerialData();

  mySerial.println("AT+HTTPINIT");
  delay(6000);
  ShowSerialData();

  mySerial.println("AT+HTTPPARA=\"CID\",1");
  delay(6000);
  ShowSerialData();

  DynamicJsonDocument  object(256);

  object["key"] = 45;
  object["raw"] = 34;

  serializeJson(object, Serial);

  Serial.println(" ");
  String sendtoserver;
  serializeJson(object, sendtoserver);

  delay(4000);

  mySerial.println("AT+HTTPPARA=\"URL\",\"https://smartapp.netcad.com/api/v1/tok/telemetry\""); //Server address
  delay(4000);
  ShowSerialData();

  mySerial.println("AT+HTTPPARA=\"CONTENT\",\"application/json\"");
  delay(4000);
  ShowSerialData();

  mySerial.println("AT+HTTPDATA=" + String(sendtoserver.length()) + ",100000");
  Serial.println(sendtoserver);
  delay(6000);
  ShowSerialData();

  mySerial.println(sendtoserver);
  delay(6000);
  ShowSerialData;

  mySerial.println("AT+HTTPACTION=1");
  delay(6000);
  ShowSerialData();

  mySerial.println("AT+HTTPREAD");
  delay(6000);
  ShowSerialData();

  mySerial.println("AT+HTTPTERM");
  delay(10000);
  ShowSerialData();

  /********************GSM Communication Stops********************/

}


void ShowSerialData()
{
  while (mySerial.available() != 0)
    Serial.write(mySerial.read());
  delay(1000);

}
