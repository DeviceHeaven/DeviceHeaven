/* Biblioteca Device Heaven para Arduino
   Compatível com Arduino UNO, MEGA, DUE... */
#include <Arduino.h>
#include <string.h>
#include <Ethernet.h>
#include <SPI.h>

void connectWiFi(String SSID, String PASS);

String ComandoAT(String comando, const int timeout);
 
void send_to_DH(String TOKEN, String LEITURA_ID, String LEITURA);

void send_to_DH2(String TOKEN, String LEITURA_ID, String LEITURA);

void Ethernet_start(uint8_t *mac);

void Ethernet_start(uint8_t *mac, IPAddress ip);

void Serial2_start();
