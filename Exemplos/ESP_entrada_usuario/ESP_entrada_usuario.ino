#include <Arduino.h>
#include <string.h>
#include <deviceheaven.h> // BIBLIOTECA DEVICE HEAVEN
/**************** NOME DA REDE E SENHA **********************/
#define SSID "********" // rede WIFI que deseja conectar
#define PASS "********" // senha da rede WIFI
/**************** TOKEN E ID_SENSOR **********************/
#define TOKEN "********" //Device Heaven Token do usuário
#define LEITURA_ID "******" //Device Heaven ID da Leitura
 /**************** VARIÁVEL PARA ARMAZENAR VALOR QUE SERÁ ENVIADO **********************/
char caractere;    // valor que será enviado para o Device Heaven
/***************************************************/
void setup() 
{
  Serial.begin(9600);                           // velocidade de comunicação serial entre Arduino e Computador 
  Serial2.begin(115200);                        // velocidade de comunicacao serial do Arduino com ESP8266
  Serial.println("Iniciando envio de dados..");
  connectWiFi(SSID, PASS);                      // função da biblioteca para conectar à rede WIFI escolhida
  delay(700);  
  Serial.println("Digite um valor para enviar para o Device Heaven.."); // aguarda entrada de um valor pelo usuário. Este valor será enviado ao Device Heaven
}
/***************************************************/ 
void loop() 
{
        if (Serial.available()) {                              // verificação contínua para detectar se o usuário digitou algo no Monitor Serial (Atalho: Ctrl + Shift + M)
                                 caractere = Serial.read();    // realiza a leitura do valor digitado
                                 Serial.println(caractere);                     
                                 send_to_DH(TOKEN, LEITURA_ID, String(caractere)); //empacote e envia o valor escrito para o Device Heaven
                                 Serial.println("Digite um novo valor para envio ao Device Heaven.."); 
                                }
}
