/* PLATAFORMA: ARDUINO MEGA, UNO, DUE...
   MÓDULO: ESP8266
   ENTRADA: VALOR ENTRE 0 E 9 DIGITADO PELO USUÁRIO via Serial MONITOR
*/
#include <deviceheaven.h> // BIBLIOTECA DEVICE HEAVEN
/**************** NOME DA REDE E SENHA **********************/
#define SSID "******" // rede WIFI que deseja conectar
#define PASS "******" // senha da rede WIFI
/**************** TOKEN E ID_SENSOR **********************/
#define TOKEN "********" //Device Heaven Token do usuário
#define LEITURA_ID "***" //Device Heaven ID da Leitura
/**************** VARIÁVEIS **********************/
char caractere;    // valor que será enviado para o Device Heaven
/***************************************************/
void setup() 
{
  Serial.begin(9600);                           // velocidade de comunicação serial entre Arduino e Computador 
  Serial2_start();                              // função genérica para todos os Arduinos. Inicia HardwareSerial2 para Mega, Due e SoftwareSerial2 para Arduino Uno. Comunicação com ESP
  Serial.println("Iniciando envio de dados..");
  delay(1000);  
  connectWiFi(SSID, PASS);                      // função da biblioteca para conectar à rede WIFI escolhida  
  Serial.println("Digite um valor entre 0 e 9 para enviar ao Device Heaven.."); // aguarda entrada de um valor pelo usuário. Este valor será enviado ao Device Heaven
}
/***************************************************/ 
void loop() 
{
        if (Serial.available()) {                              // verificação contínua para detectar se o usuário digitou algo no Monitor Serial (Atalho: Ctrl + Shift + M)
                                 caractere = Serial.read();    // realiza a leitura do valor digitado
                                 Serial.println(caractere);                     
                                 send_to_DH(TOKEN, LEITURA_ID, String(caractere)); //empacote e envia o valor escrito para o Device Heaven
                                 Serial.println("Digite um novo valor entre 0 e 9 para envio ao Device Heaven.."); 
                                }
}
