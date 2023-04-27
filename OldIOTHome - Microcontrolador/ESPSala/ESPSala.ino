#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

WiFiClient wifiClient;

const int pinoSensor = D1;
 
void setup() {
 
  Serial.begin(115200);                 //Serial connection
  WiFi.begin("MILENAREDE", "Fa1718280317");   //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
 
  delay(1000);
  Serial.println("CONECTANDO...");

  pinMode(pinoSensor, INPUT_PULLUP);
  }
}
 
void loop() {
  
  //Check WiFi connection status
  if (WiFi.status() == WL_CONNECTED) { 

     if(digitalRead(pinoSensor) == LOW) {
       Serial.println("--------");
       delay(1000);
    }
    else if(digitalRead(pinoSensor) == HIGH){
      Serial.println("DETECTADO");
      Serial.println("ENVIANDO...");
            
      // or WiFiClientSecure for HTTPS
      WiFiClient client;  
      HTTPClient http;
      
      // Send request
      http.begin(client, "http://192.168.0.120:8080/historico/post");
      http.addHeader("Content-Type", "application/json");
      http.POST("{\"comodo\": \"Sala\",\"numComodo\": 1}");
      
      // Read response
      Serial.println(http.getString());
      // Disconnect
      http.end();

      delay(2000);
    }
  }
  else{
    Serial.println("Error in WiFi connection");
  }
}
