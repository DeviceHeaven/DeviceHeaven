# DeviceHeavenLibrary
Biblioteca para Arduino: Device Heaven

Arduino Mega e Due:
Comunicação com ESP8266 utilizando porta "Serial2", pinos 16(Tx2) e 17(Rx2).

No arquivo "deviceheaven.cpp", na pasta "C:\Users\User\Documents\Arduino\libraries\DeviceHeaven".

Para Arduino Uno:

Comunicação com ESP8266 utilizando pinos digitais 2 e 3 (você pode mudar) a partir de biblioteca SoftwareSerial "Serial2".
SoftwareSerial Serial2(2,3);  // Rx = pino 2; Tx = pino 3;
