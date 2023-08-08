#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

WiFiClient client;  
HTTPClient http;

unsigned char ReadMulti[10] = {0XAA,0X00,0X27,0X00,0X03,0X22,0XFF,0XFF,0X4A,0XDD};
unsigned int timeSec = 0;
unsigned int timemin = 0;
unsigned int dataAdd = 0;
unsigned int incomedate = 0;
unsigned int parState = 0;
unsigned int codeState = 0;
unsigned int EPC = 0;
#define MAX_EPC_LENGTH 12 // Tamanho máximo do EPC
unsigned char epc[MAX_EPC_LENGTH]; // Matriz para armazenar o EPC
int epcIndex = 0; // Índice para rastrear a posição do EPC na matriz
int pinoR = D0; //PINO DIGITAL EM QUE O TERMINAL 'R' ESTÁ CONECTADO
int pinoG = D1; //PINO DIGITAL EM QUE O TERMINAL 'G' ESTÁ CONECTADO
int pinoB = D2;
 
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pinoR, OUTPUT); //DEFINE O PINO COMO SAÍDA
  pinMode(pinoG, OUTPUT); //DEFINE O PINO COMO SAÍDA
  pinMode(pinoB, OUTPUT); //DEFINE O PINO COMO SAÍDA
  Serial.begin(115200);                 //Serial connection
  Serial.println("Hello world.");// "Hello world."
  
  Serial.write(ReadMulti,10);
  WiFi.begin("MILENAREDE3", "12345678");   //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
 
  delay(1000);
  Serial.println("CONECTANDO...");
  }
  Serial.println("CONECTADO!");
}
 
void loop() {
  timeSec ++ ;
  
  if(timeSec >= 50000){
    timemin ++;
 
    timeSec = 0;
  
    if(timemin >= 20){
      timemin = 0;
      // Enviar comando de leitura cíclica
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.write(ReadMulti,10);
      digitalWrite(LED_BUILTIN, LOW);
      //Serial.print("oi");
    }
  }
  
  if(Serial.available() > 0) { // A porta serial recebe dados
    incomedate = Serial.read();// Obtenha os dados recebidos pela porta serial

    if((incomedate == 0x02)&(parState == 0))
    {
      parState = 1;
    }
    // Determine se é o parâmetro de instrução correspondente
    else if((parState == 1)&(incomedate == 0x22)&(codeState == 0)){  
        codeState = 1;
        dataAdd = 3;
    }
    else if(codeState == 1){
      dataAdd ++;
      
    if((dataAdd >= 9)&(dataAdd <= 20)&& epcIndex < MAX_EPC_LENGTH){
        epc[epcIndex] = incomedate;
        epcIndex++;
        if(dataAdd == 9){
          //Serial.print("EPC:"); 
        }
        EPC = (incomedate, HEX);      
        //Serial.print(incomedate, HEX);
        //Check WiFi connection status
       }
       // Estouro de localização, re-receber
       else if(dataAdd >= 21){
        //Serial.print("EPC: ");

        String epcString = "";
          for (int i = 0; i < MAX_EPC_LENGTH; i++) {
            epcString += String(epc[i], HEX);
          }
          //Serial.print("EPC String: ");
          //Serial.println(epcString);
          
          //Serial.println(" ");
          if(epcString == "e2047864706821e5c31b"){
            setColor(0, 255, 0);
          }
          else if(epcString == "e280689400501a4940f4e8"){
            setColor(255, 0, 0);
          }
          else if(epcString == "e280689400401a4f65ba2b"){
            setColor(0, 0, 255);
          }
          
          
        if (WiFi.status() == WL_CONNECTED) {
    
          String teste = "{\"comodo\": \"Sala\",\"numComodo\": 1,\"tag\":\""+epcString+"\"}";
          
          // Send request
          http.begin(client, "http://192.168.155.129:8080/historicoOldIotHome/post");
          http.addHeader("Content-Type", "application/json");
          http.POST(teste);
          
          // Read response
          Serial.print(http.getString());
          Serial.println(" "+epcString);
          // Disconnect
          http.end();
    
          delay(1000);
        }
      else{
        Serial.println("Error in WiFi connection");
      } 
        epcIndex = 0;
        memset(epc, 0, sizeof(epc));
        dataAdd= 0;
        parState = 0;
        codeState = 0;
        }
    }
     else{
      dataAdd= 0;
      parState = 0;
      codeState = 0;
      epcIndex = 0;
      memset(epc, 0, sizeof(epc));
      EPC = 1;
    }
  }  
}

void setColor(int vermelho, int verde, int azul){
  
  #ifdef COMMON_ANODE //SE O LED RGB FOR DEFINIDO COMO ANODO COMUM, FAZ
    vermelho = 255 - vermelho; //VARIÁVEL RECEBE O RESULTADO DA OPERAÇÃO '255 MENOS O PARÂMETRO (vermelho) INFORMADO' NA CHAMADA DA FUNÇÃO
    verde = 255 - verde; //VARIÁVEL RECEBE O RESULTADO DA OPERAÇÃO '255 MENOS O PARÂMETRO (verde) INFORMADO' NA CHAMADA DA FUNÇÃO
    azul = 255 - azul; //VARIÁVEL RECEBE O RESULTADO DA OPERAÇÃO '255 MENOS O PARÂMETRO (azul) INFORMADO' NA CHAMADA DA FUNÇÃO
  #endif
  analogWrite(pinoR, vermelho); //DEFINE O BRILHO DO LED DE ACORDO COM O VALOR INFORMADO PELA VARIÁVEL 'vermelho'
  analogWrite(pinoG, verde); //DEFINE O BRILHO DO LED DE ACORDO COM O VALOR INFORMADO PELA VARIÁVEL 'verde'
  analogWrite(pinoB, azul); //DEFINE O BRILHO DO LED DE ACORDO COM O VALOR INFORMADO PELA VARIÁVEL 'azul'
}
