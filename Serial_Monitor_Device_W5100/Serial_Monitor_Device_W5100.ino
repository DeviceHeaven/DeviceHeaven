/* PLATAFORMA: ARDUINO MEGA, UNO, DUE...
   MÓDULO: W5100
   ENTRADA: VALOR DIGITADO PELO USUÁRIO via Serial MONITOR
*/
#include <deviceheaven.h> // BIBLIOTECA DEVICE HEAVEN
/**************** ENDEREÇO MAC DO SHIELD W5100 **********************/
byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02}; //se for uma das placas novas, inserir aqui o MAC impresso no verso desta!!! Se for das antigas, você pode escolher.
/**************** TOKEN E ID_SENSOR **********************/
#define TOKEN "***********" //Device Heaven Token do usuário
#define LEITURA_ID "**" //Device Heaven ID da Leitura
/**************** VARIÁVEIS **********************/
String valor;    // valor que será enviado para o Device Heaven
IPAddress ip(192,168,0,100); // caso DHCP não funcione, defina aqui o IP. Também comente a linha "Ethernet.begin(mac)"; e descomente a linha Ethernet.begin(mac, ip);
/***************************************************/ 
void setup() 
{
  Serial.begin(9600);                           // velocidade de comunicação serial entre Arduino e Computador 
  Serial.println("Iniciando envio de dados..");
  delay(1000);
  Ethernet_start(mac);                         // inicializa comunicação Ethernet
//Ethernet_start(mac, ip);
  Serial.println("Digite um valor para enviar ao Device Heaven.."); // aguarda entrada de um valor pelo usuário. Este valor será enviado ao Device Heaven
}
/***************************************************/ 
void loop() 
{
   if (Serial.available()) {                              // verificação contínua para detectar se o usuário digitou algo no Monitor Serial (Atalho: Ctrl + Shift + M)
                                 valor = Serial.readString();    // realiza a leitura do valor digitado
                                 Serial.println(valor);                     
                                 send_to_DH2(TOKEN, LEITURA_ID, valor); //empacote e envia o valor escrito para o Device Heaven
                                 Serial.println("Digite um novo valor entre 0 e 9 para envio ao Device Heaven.."); 
                                }
}
