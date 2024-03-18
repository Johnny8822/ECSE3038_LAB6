#include <Arduino.h> 
#include <LiquidCrystal.h> 
#include <ArduinoJson.h>  
#include <OneWire.h>
#include <HTTPClient.h> 
#include "env.h"
#include <DallasTemperature.h> 

#define LED_PIN 6
#define ONE_WIRE_BUS 4 
Onewire oneWire(ONE_WIRE_BUS); 

DallasTemperature sensors(&oneWire)

LiquidCrystal My_LCD(22,23,5,18,19,21);

unsigned long lastTime = 0; 
unsigned long Timerdelay =2000;
// put function declarations here:


void patchTemp(char * body){
  HTTPClient http 
  http.begin(endpoint); 
  http.addHeader("Content-Type", "application/json") 

  http.PUT(body); 
  Serial.print("HERE IS THE RESPONSE");
  Serial.println(body);
  Serial.println(http.getString());  
  Serial.println();

}

void setup() {
  
  Serial.begin(9600); 
  sensors.begin(); 
  sensors.setWaitForConversion(true); 
  delay(1000);
   

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  

}

void loop() {
  // put your main code here, to run repeatedly:  
  

  HTTPClient http; 
  
  http.begin(endpoint.c_str());  

  http.GET();  
  http.addHeader("api-key", api_key);
  int httpResponseCode = http.GET(); 
  
  delay(1000);  
  sensors.requestTemperatures(); 
  

  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String responseBody = http.getString(); 
    Serial.println(responseBody); 

    JsonDocument doc; 
    DeserializationError error = deserializeJson(doc, responseBody);

if (error){
    Serial.print("deserializeJson()failed: ");
    Serial.println(error.c_str());
    return;
   }
   String line_1 = doc["line_1"];  
   String line_2 = doc["line_2"]; 
   


  

  }
}
// put function definitions here:
