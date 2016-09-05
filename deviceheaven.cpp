/* Biblioteca Device Heaven para Arduino
   Compatível com Arduino UNO, MEGA, DUE... */
#include "deviceheaven.h"

#define debug false                   // Debug da comunicação serial para verificar resposta do ESP
#define IP "data.deviceheaven.com"    // Device Heaven IP: dados.device-heaven.com.br
#define DATA_HORA "none"              // None: o horário das leituras será o do servidor

#ifdef __AVR_ATmega328P__

#include <SoftwareSerial.h>
SoftwareSerial Serial2(2,3);  // Rx = pino 2; Tx = pino 3;

#endif

/* start_serial: configura de 115200 para 19200 o ESP8266, mas não salva na flash. 
Se o módulo é reiniciado ou desligado, na próxima vez o mesmo estará com a configuração padrão de fábrica.
Função genérica para todos os tipos de Arduino, tendo ou não Hardware Serial disponível.               */
void Serial2_start()
{
  Serial2.begin(115200); //velocidade padrão do ESP8266, se estiver configurado com outro baudrate, mudar este valor
  delay(1);
  
  Serial.println("Alterando baudrate de 115200 para 19200..");
  delay(1);
  
  ComandoAT("AT+UART_CUR=19200,8,1,0,0", 2000);
  delay(100);
  
  Serial2.flush();
  delay(1);
	
  Serial2.end();
  delay(1);
  
  Serial2.begin(19200);  //velocidade que garante que a comunicação com sucesso para Arduino com hardware serial ou software serial
  delay(10);
  
  Serial2.println("AT"); //comunica��o OK
  delay(1);
  
  if (Serial2.find("OK"))
  {
	  delay(10);
	  Serial.println("Baudrate alterado com sucesso..");
	  
  }
   else {
	     Serial.println("Problema ao estabelecer conexao..");
		 delay(100);
		 Serial2_start();
	    }
  
}

/* connectWiFi: função para conectar à rede WiFi definida pelo usuário*/

void connectWiFi(String SSID, String PASS)
{
 delay(1);
 Serial2.println("AT"); //comunica��o OK
 delay(1);
 
 if (Serial2.find("OK"))
 {
  delay(1);
  Serial.println("INICIANDO ESP");
  
  delay(1);
  ComandoAT("AT+CWMODE=1", 1000); //configura acesspoint
  
  String cmd = "AT+CWJAP=\"";  
  cmd += SSID;
  cmd += "\",\"";
  cmd += PASS;
  cmd += "\"";
  
  ComandoAT(cmd, 8000);//conecta com a rede escolhida
  delay(1);
  
  Serial.println("CONECTADO NA REDE:");
  delay(1);
  
  Serial.println(SSID);
  delay(500);
  
  ComandoAT("AT+CIFSR", 1000);//mostra endere�o IP
  delay(1);
  
  ComandoAT("AT+CIPMUX=1", 1000);//Habilita conex�o TCP
  delay(1);
  Serial.println("CONEXAO TCP HABILITADA.");
 }
      else
        {
          ComandoAT("AT+CWMODE=1", 1000); //configura acesspoint
          ComandoAT("AT+RST", 2000); //reset ESP
		  
		  delay(1);
          Serial.println("\n ESP DESLIGADO ");
		  
          delay(3000);
          connectWiFi(SSID, PASS);
		  delay(1);
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
	delay(1);
    Serial.println(resposta);
	delay(1);
   }
  return resposta;
}
 
/* Descrição: Função utilizada para enviar dados para o DeviceHeaven. */
void send_to_DH(String TOKEN, String LEITURA_ID, String LEITURA)
{
	 delay(1);
     String cmd = "AT+CIPSTART=4,\"TCP\",\""; //Configura conex�o TCP
     cmd += IP;
     cmd += "\",9012";
     ComandoAT(cmd, 2000);
     cmd = "";
     delay(1000);
      if ( Serial2.find( "Error" ) )
      {
		  delay(1);
       Serial.println(" Nao abriu a conexao TCP");
	   delay(1);
       return;
      }
     Serial.println("PREPARANDO PACOTE PARA ENVIO...");
	 delay(100);
     cmd = String("00 ") + String(TOKEN) + String(" ") + String(DATA_HORA) + String(" ") + String(DATA_HORA) + String(" ")+ String(LEITURA_ID) + String(" ")+ String(LEITURA);
	 delay(1);
     Serial2.print( "AT+CIPSEND=4," ); //envia comando AT para indicar o tamanho da string enviada
	 delay(100);
     Serial2.println(cmd.length());
     delay(100);
          if (Serial2.find( ">" ) )
          {
		   delay(1);
           Serial.print(">");
           Serial.print(cmd);
		   
		   delay(1);
           Serial2.print(cmd);
		   
		   delay(1);
		   Serial.print("\nDADOS ENVIADOS COM SUCESSO PARA O DEVICE HEAVEN..");
           delay(100);
          }

     Serial2.println( "AT+CIPCLOSE=4"); //fecha conexão TCP
     delay(1000);
						if ( Serial2.find("OK") )
						{
	 					 delay(1);
	 					 Serial.println("\nCONEXAO TCP FECHADA");
						 delay(1);
						}
								else
									{
									 Serial.println( " Erro ao fechar conexao " );
									 delay(1);
									}
}
