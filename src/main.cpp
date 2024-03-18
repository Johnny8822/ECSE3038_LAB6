#include <Arduino.h> 
#include <ArduinoJson.h>  
#include <OneWire.h>
#include <HTTPClient.h> 
#include "env.h"
#include <DallasTemperature.h> 


OneWire oneWire(ONE_WIRE_BUS); 


DallasTemperature sensors(&oneWire);

//LiquidCrystal My_LCD(22,23,5,18,19,21);

unsigned long lastTime = 0; 
unsigned long Timerdelay =2000;
// put function declarations here:

void getLight(void){
  
  HTTPClient http;  
  String serverPath_light = endpoint + "light";
  http.begin(serverPath_light); 
  http.addHeader("Content-Type", "application/json"); 
  String RequestBody;  
  
  int httpResponseCode = http.GET();
    if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String responseBody = http.getString(); 
    Serial.println(responseBody); 
    JsonDocument doc;

  DeserializationError error = deserializeJson(doc, responseBody);

  if (error) {
  Serial.print("deserializeJson() failed: ");
  Serial.println(error.c_str());
  return;
   }

   bool light = doc["light"];
   
  if(light == LOW){
  digitalWrite(LED_PIN, light);  
  }
   else {
  digitalWrite(LED_PIN, light); 
    }
  } 
  http.end();
} 

void patchTemp(float temperature){
  HTTPClient http;  
  String serverPath_temp = endpoint + "temp";
  http.begin(serverPath_temp); 
  http.addHeader("Content-Type", "application/json"); 
  String RequestBody;  

  JsonDocument doc;  
  doc ["temp"] = 32; 
  doc.shrinkToFit(); 
  serializeJson(doc, RequestBody);

  int httpRequestCode = http.PATCH(RequestBody);
  http.PUT(RequestBody); 
  Serial.print("HERE IS THE RESPONSE");
  Serial.println(temperature);
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
  delay(1000);  
  sensors.requestTemperatures();    
  float x = sensors.getTempCByIndex(); 
  patchTemp(x);
  Serial.println(x);  

}

// put function definitions here:
