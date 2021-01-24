
#include "ESP8266WiFi.h"
#include "ESPAsyncWebServer.h"
#include "string.h"


// accesspoint setzten
const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";
int button_status = 0;


// Webserver auf port80
AsyncWebServer server(80);

void setup(){
  // Serial port ausgabe
  Serial.begin(9600);
  Serial.println();
  
  Serial.print("Einstellen des AP (Access Point)…");
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("IP address: ");
  Serial.println(IP);

  server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request){
    char status_txt [100];
    sprintf(status_txt, "%i",button_status);
    request->send_P(200, "text/plain", status_txt);
  });

  
  // Start server
  server.begin();
}
 
void loop(){
  
}
