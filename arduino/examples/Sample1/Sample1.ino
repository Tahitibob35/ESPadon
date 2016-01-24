/************************************************************
 * Sample code with ESPadon library.
 *
 ***********************************************************/
#include "espadon.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial( 11 , 10 );
ESPadon esp( mySerial );

unsigned long previousMillis = 0;
const long interval = 2000;


void setup() {
  Serial.begin( 9600 );
  mySerial.begin( 9600 );


  // Attach the action #2 to the actionB function
  Serial.println( "Ready to play...." );
}


void loop( ) {

    /*if ( mySerial.available( ) ) {
      s.check_reception( );
      }*/
    unsigned long currentMillis = millis();
    Serial.println( "Send msg" );
    char url[] = "http://192.168.0.10:8000/";
    int wstatus = esp.httpGET( url );
    Serial.print( "Status : " );
    Serial.println( wstatus );

    char ssid[50] = "";
    if ( esp.SSID( ssid ) ){
    	Serial.print( "SSID : " );
    	Serial.println( ssid );
    }


    //Serial.println( wstatus );
  delay(5000);
}


