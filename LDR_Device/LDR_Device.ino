/* PLATAFORMA: ARDUINO MEGA, UNO, DUE...
   MÓDULO: ESP8266 + LDR
   ENTRADA: leitura Ligado/Desligado do LED
*/
#include <deviceheaven.h> // BIBLIOTECA DEVICE HEAVEN
/**************** NOME DA REDE E SENHA **********************/
#define SSID "******" // rede WIFI que deseja conectar
#define PASS "******" // senha da rede WIFI
/**************** TOKEN E ID_SENSOR **********************/
#define TOKEN "********" //Device Heaven Token do usuário
#define LEITURA_ID "***" //Device Heaven ID da Leitura
/**************** VARIÁVEIS **********************/
int luz = 0;  // variável armazenar 0 ou 1 (led ligado ou desligado)
const int luz_pino = 4;   // pino para leitura HIGH/LOW do LED
/***************************************************/
void setup()
{
  Serial.begin(9600);                           // velocidade de comunicação serial entre Arduino e Computador
  Serial2_start();                              // função genérica para todos os Arduinos. Inicia HardwareSerial2 para Mega e Due e SoftwareSerial2 para Arduino Uno e outros.
  pinMode(luz_pino, INPUT);
  Serial.println("Iniciando envio de dados..");
  delay(1000);
  connectWiFi(SSID, PASS);                      // função da biblioteca para conectar à rede WIFI escolhida
}
/***************************************************/
void loop()
{
  sensor_luz();                                     // realiza a leitura do sensor LM35
  delay(1000);
  send_to_DH(TOKEN, LEITURA_ID, String(luz));     // empacote e envia o valor escrito para o Device Heaven
  delay(1000);
}
/***************************************************/
/* Função para realizar a leitura do sensor de temperatura LM35 */
void sensor_luz()
{
  luz = map((digitalRead(luz_pino)), 0, 1, 1 , 0); //lógica invertida
  if (luz == 0)
  {
    Serial.println("LEITURA: 0 (LUZ DESLIGADA)");
  }
  else Serial.println("LEITURA: 1 (LUZ LIGADA)");
}

