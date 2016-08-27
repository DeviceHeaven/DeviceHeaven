
#include <Arduino.h>
#include <string.h>
#include <SoftwareSerial.h>
#include "deviceheaven.h"

#define debug false //debug da comunicação serial ESP-Arduino
#define IP "data.deviceheaven.com" //Device Heaven IP Adresss: dados.device-heaven.com.br
#define DATA_HORA "none" //
/* ConnectWiFi: */
void connectWiFi(String SSID, String PASS)
{
 Serial2.println("AT"); //comunica��o OK
 
 if (Serial2.find("OK"))
 {
  ComandoAT("AT+RST", 2000); //reset ESP
  Serial.println("INICIANDO ESP");
  ComandoAT("AT+CWMODE=1", 1000); //configura acesspoint
  //Serial.println("ACCESS POINT OK");
  String cmd = "AT+CWJAP=\"";  
  cmd += SSID;
  cmd += "\",\"";
  cmd += PASS;
  cmd += "\"";
  ComandoAT(cmd, 8000);//conecta com a rede escolhida
  Serial.println("CONECTADO NA REDE:");
  Serial.println(SSID);
  delay(500);
  ComandoAT("AT+CIFSR", 1000);//mostra endere�o IP
  //Serial.println("ENDEREÇO IP:");
  ComandoAT("AT+CIPMUX=1", 1000);//Habilita conex�o TCP
  Serial.println("CONEXAO TCP HABILITADA.");
 // return true;
 }
      else
        {
          ComandoAT("AT+CWMODE=1", 1000); //configura acesspoint
          ComandoAT("AT+RST", 2000); //reset ESP
          Serial.println("\n ESP DESLIGADO ");
          delay(3000);
          connectWiFi(SSID, PASS);
   //       return false;
         }
}

String ComandoAT(String comando, const int timeout)
{
   String resposta = ""; //variavel para armazenar a resposta do ESP
   Serial2.println(comando); //Envia os dados para o ESP para executar o comando
   long int time = millis(); //vari�vel para armazenar os millis atuais
 
   while ( (time + timeout) > millis())
  {
     while (Serial2.available()) //utilizado para armazenar o resultado enviado pelo ESP
    {
     char c = Serial2.read();
     resposta += c;
    }
  }
 
   if (debug) //se estiver em modo debug imprime para a porta serial USB
   {
    Serial.println(resposta);
   }
  return resposta;
}
 
/* Descri��o: Fun��o utilizada para enviar dados para o DeviceHeaven. */
void send_to_DH(String TOKEN, String LEITURA_ID, String LEITURA)
{
     String cmd = "AT+CIPSTART=4,\"TCP\",\""; //Configura conex�o TCP
     cmd += IP;
     cmd += "\",9012";
     ComandoAT(cmd, 2000);
     cmd = "";
     delay(1000);
      if ( Serial2.find( "Error" ) )
      {
       Serial.println(" Nao abriu a conexao TCP");
	 //    connectWiFi(SSID, PASS);
      // connectWiFi();
       return;
      }
     Serial.println("PREPARANDO PACOTE PARA ENVIO...");
	 delay(100);
     cmd = String("00 ") + String(TOKEN) + String(" ") + String(DATA_HORA) + String(" ") + String(DATA_HORA) + String(" ")+ String(LEITURA_ID) + String(" ")+ String(LEITURA);
     Serial2.print( "AT+CIPSEND=4," ); //envia comando AT para indicar o tamanho da string enviada
     Serial2.println(cmd.length());
     delay(1000);
          if (Serial2.find( ">" ) )
          {
           Serial.print(">");
           Serial.print(cmd);
		   delay(1000);
           Serial2.print(cmd); //envia dados para o Device Heaven
		   Serial.print("\nDADOS ENVIADOS COM SUCESSO PARA O DEVICE HEAVEN..");
           delay(1000);
          }

     Serial2.println( "AT+CIPCLOSE=4"); //fecha conex�o TCP
     delay(1000);
     if ( Serial2.find("OK") )
    {
     Serial.println("\nCONEXAO FECHADA");
    }
     else
          {
           Serial.println( " Erro ao fechar conexao " );
	//	     connectWiFi(SSID, PASS);
    //       connectWiFi(SSID, PASS);
          }
}
