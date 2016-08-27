/*  Tentativa 1 de Biblioteca  */
#include <Arduino.h>
#include <string.h>
#include <SoftwareSerial.h>
void connectWiFi(String SSID, String PASS);

String ComandoAT(String comando, const int timeout);
 
void send_to_DH(String TOKEN, String LEITURA_ID, String LEITURA);
