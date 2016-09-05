/* Biblioteca Device Heaven para Arduino
   Compatível com Arduino UNO, MEGA, DUE... */
#include <Arduino.h>
#include <string.h>

void connectWiFi(String SSID, String PASS);

String ComandoAT(String comando, const int timeout);
 
void send_to_DH(String TOKEN, String LEITURA_ID, String LEITURA);

void Serial2_start();
