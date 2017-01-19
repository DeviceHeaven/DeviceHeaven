/* PLATAFORMA: ARDUINO MEGA, UNO, DUE...
   MÓDULO: ESP8266 + sensor de Temperatura LM35
   ENTRADA: leitura do Sensor LM35
*/
#include <deviceheaven.h> // BIBLIOTECA DEVICE HEAVEN
/**************** NOME DA REDE E SENHA **********************/
#define SSID "******" // rede WIFI que deseja conectar
#define PASS "******" // senha da rede WIFI
/**************** TOKEN E ID_SENSOR **********************/
#define TOKEN "********" //Device Heaven Token do usuário
#define LEITURA_ID "***" //Device Heaven ID da Leitura
/**************** VARIÁVEIS **********************/
float temperatura = 0;  // variável para armazenar valor de temperatura
const int LM35 = A0;   // saída do sensor LM35 na entrada analógica A0 do Arduino
/***************************************************/
void setup() 
{
  Serial.begin(9600);                           // velocidade de comunicação serial entre Arduino e Computador 
  Serial2_start();                              // função genérica para todos os Arduinos. Inicia HardwareSerial2 para Mega e Due e SoftwareSerial2 para Arduino Uno e outros.
  pinMode(LM35, INPUT);
  Serial.println("Iniciando envio de dados..");
  delay(1000);  
  connectWiFi(SSID, PASS);                      // função da biblioteca para conectar à rede WIFI escolhida  
}
/***************************************************/ 
void loop() 
{
  temperatura_LM35();                                     // realiza a leitura do sensor LM35
  delay(1000);                                            
  send_to_DH(TOKEN, LEITURA_ID, String(temperatura));     // empacote e envia o valor de temperatura para o Device Heaven
  delay(1000);
}
/***************************************************/
/* Função para realizar a leitura do sensor de temperatura LM35 */
void temperatura_LM35() 
{
  Serial.println("Valor de temperatura: ");
  delay(1000);
  temperatura = (float(analogRead(LM35))*5/(1023))/0.01;
  Serial.println(temperatura);
  delay(1000);
}

