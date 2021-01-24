#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti WiFiMulti;

const char* ssid = "ESP8266-Access-Point";
const char* password = "123456789";

//Ip Adresse und URL
const char* serverNameStatus = "http://192.168.4.1/status";

unsigned long prev_Millis = 0;
const long interval = 10000; 
String Status;


void setup() {
  Serial.begin(9600);
  Serial.println();
 
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);
  while((WiFiMulti.run() == WL_CONNECTED)) { 
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Verbinden mit WiFi");
}

void loop() {
  unsigned long cur_Millis = millis();
  if(cur_Millis - prev_Millis >= interval) {
     // Wifi Status Testen
    if ((WiFiMulti.run() == WL_CONNECTED)) {
      Status = httpGETRequest(serverNameStatus);
      Serial.println("Wifi Verbunden");
      prev_Millis = cur_Millis;
    }
    else {
      Serial.println("WiFi getrennt");
    }
  }
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path 
  http.begin(serverName);
  
  // senden der http post abfrage
  int httpResponseCode = http.GET();
  
  String payload = "--"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Abfrage beenden
  http.end();

  return payload;
}
