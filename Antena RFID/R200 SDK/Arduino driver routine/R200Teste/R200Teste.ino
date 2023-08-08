/*
由四川睿频科技有限公司编写
复制及使用请保留版权所属
Preparado por Sichuan Ruipin Technology Co., Ltd.
Copie e use, por favor, mantenha os direitos autorais
*/


/*多次读取指令 - leia o comando várias vezes*/
unsigned char ReadMulti[10] = {0XAA,0X00,0X27,0X00,0X03,0X22,0XFF,0XFF,0X4A,0XDD};
unsigned int timeSec = 0;
unsigned int timemin = 0;
unsigned int dataAdd = 0;
unsigned int incomedate = 0;
unsigned int parState = 0;
unsigned int codeState = 0;
unsigned int EPCAtual = 0;
unsigned int EPCAntiga = 0;

#define MAX_EPC_LENGTH 12 // Tamanho máximo do EPC

unsigned char epc[MAX_EPC_LENGTH]; // Matriz para armazenar o EPC
int epcIndex = 0; // Índice para rastrear a posição do EPC na matriz


void setup() {
  //Defina a porta serial e defina - LED
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(115200); // Defina a taxa de transmissão da porta serial 115200
  
  Serial.println("Hello world.");// "Hello world."
  
  Serial.write(ReadMulti,10);
}

void loop() {

  // Comandos de leitura cíclica ocorrem após algum intervalo de tempo
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
    }
  }
  
  if(Serial.available() > 0) { // A porta serial recebe dados
  	incomedate = Serial.read();// Obtenha os dados recebidos pela porta serial

    if((incomedate == 0x02)&(parState == 0))
    {
      parState = 1;
    }
    //判断是否为对应指令参数 - Determine se é o parâmetro de instrução correspondente
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
          Serial.print("EPC: ");
        }       
        Serial.print(incomedate, HEX);
       }
       // Estouro de localização, re-receber
        else if(dataAdd >= 21){
        Serial.print("EPC: ");

        String epcString = "";
          for (int i = 0; i < MAX_EPC_LENGTH; i++) {
            epcString += String(epc[i], HEX);
          }
          Serial.print("EPC String: ");
          Serial.println(epcString);

        dataAdd= 0;
        parState = 0;
        codeState = 0;
        Serial.println();
        }
          
    }
     else{
      dataAdd= 0;
      parState = 0;
      codeState = 0;
    }
  }
}
