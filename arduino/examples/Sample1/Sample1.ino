/************************************************************
 * Sample code with ESPadon library.
 *
 ***********************************************************/
#include "espadon.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial( 11 , 10 );
ESPadon esp( mySerial );


void setup() {
  Serial.begin( 9600 );
  mySerial.begin( 9600 );


  Serial.println( "Ready to play...." );
}


void loop( ) {

    /*if ( mySerial.available( ) ) {
      s.check_reception( );
      }*/

    Serial.println( "Send msg" );
    char url[] = "http://192.168.0.10:8000/";
    int wstatus = esp.httpGET( url );
    Serial.print( "HTTP Status : " );
    Serial.println( wstatus );

    char ssid[50] = "";
    if ( esp.SSID( ssid ) ){
    	Serial.print( "SSID : " );
    	Serial.println( ssid );
    }

    Serial.print( "ESP8266 status : " );
    Serial.println( esp.status( ) );

    delay(5000);

    Serial.println( "Disconnect" );
    esp.disconnect( );

    delay(5000);

    Serial.print( "ESP8266 status : " );
    Serial.println( esp.status( ) );

    delay(5000);

    char nssid[] = "TahitibobNetwork";
    char npass[] = "calimeroestgentil";
    int res = 0;
    res  = esp.begin( nssid , npass );

    Serial.print( "Connection result : " );
    Serial.println( res );



    delay(5000);

    Serial.print( "ESP8266 status : " );
    Serial.println( esp.status( ) );

    delay(5000);

    Serial.print( "ESP8266 status : " );
    Serial.println( esp.status( ) );

    delay(5000);

    Serial.print( "ESP8266 status : " );
    Serial.println( esp.status( ) );

    delay(5000);















}


