#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
//#include "SoftwareSerial.h"
//SoftwareSerial Serial1(6, 7); // RX, TX

String URL = "https://e6mjmurtkd.execute-api.us-east-2.amazonaws.com/default/nova3d-form-to-google-sheets";

void setup()
{

  Serial.begin(115200);                //Serial connection
  WiFi.begin("Vilchis", "0047621814"); //WiFi connection

  while (WiFi.status() != WL_CONNECTED)
  { //Wait for the WiFI connection completion
    delay(500);
    Serial.println("Waiting for connection");
  }
}

void loop()
{
  StaticJsonDocument<200> doc;
  doc["correas"] = 4;
  doc["whatsapp"] = 2;
  doc["caretas_ad"] = 0;
  doc["caretas_ni"] = 0;
  doc["nombre"] = "pruebaArduino";
  String output;
  serializeJsonPretty(doc, output);
  if (WiFi.status() == WL_CONNECTED)
  {                  //Check WiFi connection status
    HTTPClient http; //Declare object of class HTTPClient

    http.begin(URL);                                    //Specify request destination
    http.addHeader("Content-Type", "application/json"); //Specify content-type header

    int httpCode = http.POST(output); //Send the request

    String payload = http.getString(); //Get the response payload
    Serial.println(payload);           //Print request response payload

    Serial.println(httpCode); //Print HTTP return code

    http.end(); //Close connection
  }
  else
  {
    Serial.println("Error in WiFi connection");
  }

  delay(5000); //Send a request every 30 seconds
}
