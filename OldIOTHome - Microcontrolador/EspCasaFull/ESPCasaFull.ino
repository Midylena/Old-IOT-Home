#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

WiFiClient wifiClient;

const int pinoSala = D1;
const int pinoCozinha = D2;
const int pinoBanheiro = D3;
const int pinoQuarto = D4;
 
void setup() {
 
  Serial.begin(115200);                 //Serial connection
  WiFi.begin("TP-Link_0DA2", "34825686");   //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
 
  delay(1000);
  Serial.println("CONECTANDO...");

  pinMode(pinoSala, INPUT);
  pinMode(pinoCozinha, INPUT);
  pinMode(pinoBanheiro, INPUT);
  pinMode(pinoQuarto, INPUT);
  }
}
 
void loop() {
  
  //Check WiFi connection status
  if (WiFi.status() == WL_CONNECTED) { 

     //if(digitalRead(pinoSensor) == LOW) {
       //Serial.println("--------");
       //delay(1000);
    //}
    if(digitalRead(pinoSala) == HIGH){
      Serial.println("DETECTADO SALA");
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
    if(digitalRead(pinoCozinha) == HIGH){
      Serial.println("DETECTADO COZINHA");
      Serial.println("ENVIANDO...");
            
      // or WiFiClientSecure for HTTPS
      WiFiClient client;  
      HTTPClient http;
      
      // Send request
      http.begin(client, "http://192.168.0.120:8080/historico/post");
      http.addHeader("Content-Type", "application/json");
      http.POST("{\"comodo\": \"Cozinha\",\"numComodo\": 2}");
      
      // Read response
      Serial.println(http.getString());
      // Disconnect
      http.end();

      delay(2000);
    }
    if(digitalRead(pinoBanheiro) == HIGH){
      Serial.println("DETECTADO BANHEIRO");
      Serial.println("ENVIANDO...");
            
      // or WiFiClientSecure for HTTPS
      WiFiClient client;  
      HTTPClient http;
      
      // Send request
      http.begin(client, "http://192.168.0.120:8080/historico/post");
      http.addHeader("Content-Type", "application/json");
      http.POST("{\"comodo\": \"Banheiro\",\"numComodo\": 3}");
      
      // Read response
      Serial.println(http.getString());
      // Disconnect
      http.end();

      delay(2000);
    }
    if(digitalRead(pinoQuarto) == HIGH){
      Serial.println("DETECTADO QUARTO");
      Serial.println("ENVIANDO...");
            
      // or WiFiClientSecure for HTTPS
      WiFiClient client;  
      HTTPClient http;
      
      // Send request
      http.begin(client, "http://192.168.0.120:8080/historico/post");
      http.addHeader("Content-Type", "application/json");
      http.POST("{\"comodo\": \"Quarto\",\"numComodo\": 4}");
      
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
