//
// Esempio di utilizzo di Bot Telegram con ESP8266
//
// maurizio.conti@fablabromagna.org
// 20 Aprile 2019
//
// dipendenze:
//
// libreria CTBot di Stefano Ledda <shurillu@tiscalinet.it>
// https://github.com/shurillu/CTBot
//
// Libreria ArduinoJson  (attento: usa versione 5.13.5 non la 6.x)
// https://arduinojson.org/
// Installare con il library manager di Arduino
// 

#include "CTBot.h"

// Il client Telegram
CTBot myBot;

String ssid  = ""; 
String pass  = "";
String token = "";

void setup() {
  
	Serial.begin( 115200 );
	Serial.println( "\n\nSi parte..." );

  // Configuri il client Telegram 
  myBot.setTelegramToken(token);

	// lo connetti alla rete
	myBot.wifiConnect(ssid, pass);

  // tenti una connessione a Telegram per vedere se tutto è OK.
  // Stai qui finchè non è OK
  while(!myBot.testConnection())
  {
    Serial.print("?");
    delay(1000);
  }
}

void loop() {

  if( myBot.testConnection() ) {
    Serial.println("Connesso");
  
    // Il messaggio in formato telegram
	  TBMessage msg;

	  // Leggi i messaggi
	  if ( myBot.getNewMessage(msg) ) {
		  
		  // Se li trovi ne fai l'echo
		  myBot.sendMessage(msg.sender.id, msg.text);

      // e li mostri in locale
      Serial.println( msg.text );
    }
    else
    {
      // Non ci sono messaggi da leggere
      Serial.println("No msg...");
    }
  }
	
	// non essere troppo nervoso...
	delay(500);
}
