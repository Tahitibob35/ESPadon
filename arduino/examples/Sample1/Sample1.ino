/************************************************************
 * Sample code with ESPadon library.
 *
 ***********************************************************/
#include "espadon.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial( 11 , 10 );
ESPadon esp( mySerial );

unsigned long previousMillis = 0;
const long interval = 5000;

void writetosparkfun ( void );

void setup() {
  Serial.begin( 9600 );
  mySerial.begin( 9600 );

  Serial.println( "Starting...." );
  
  esp.attach( incoming );  

  esp.startHTTPServer ( 80 );  
  Serial.println( "HTTP server started..." );

  Serial.println("Connecting to the wifi network");
  char nssid[] = "TahitibobNetwork";
  char npass[] = "ABCDEF1234";
  int result = 0;
  result  = esp.begin( nssid , npass );

  
  Serial.println("");
  do {
    result = esp.status( );
    Serial.print(".");
  } while (result != WL_CONNECTED );
  Serial.println("");
  Serial.println("");

  pinMode( 5 , OUTPUT );

}


void loop( ) {

    if ( mySerial.available( ) ) {
        esp.check_reception( );
    }

    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      
      /* Outgoing http request
      Serial.println( "Send msg" );
      char url[] = "http://192.168.0.10:8000/";
      int wstatus = esp.httpGET( url );
      Serial.print( "HTTP Status : " );
      Serial.println( wstatus );
      */
  
      char ssid[50] = "";
      if ( esp.SSID( ssid ) ){
      	Serial.print( "SSID : " );
      	Serial.println( ssid );
      }
  
  
      Serial.print( "ESP8266 status : " );
      Serial.println( esp.status( ) );
      
  
      int mac[6];
      if ( esp.macAddress( mac ) ){
      	Serial.print( "MAC : " );
      	for (int i=0 ; i<6 ; i++ ) {
      	    Serial.print( mac[i] , HEX );
            if ( i != 5 ) Serial.print( " " );
      	}
      	Serial.println( "" );
      }
  
      int ip[4];
      if ( esp.localIP( ip ) ){
      	Serial.print( "IP : " );
      	for (int i=0 ; i<4 ; i++ ) {
      	    Serial.print( ip[i] , DEC );
            if ( i != 3 ) Serial.print( "." );
      	}
      	Serial.println( "" );
      }
  
      if ( esp.subnetMask( ip ) ){
      	Serial.print( "Subnet mask : " );
      	for (int i=0 ; i<4 ; i++ ) {
      	    Serial.print( ip[i] , DEC );
            if ( i != 3 ) Serial.print( "." );
      	}
      	Serial.println( "" );
      }
  
  
      /*
      Serial.println( "Disconnect" );
      esp.disconnect( );
      */
  
      Serial.print( "ESPadon web interface : http://" );
      if ( esp.localIP( ip ) ){
        for (int i=0 ; i<4 ; i++ ) {
            Serial.print( ip[i] , DEC );
            if ( i != 3 ) Serial.print( "." );
        }
        Serial.println( ":80/ESPadon" );
      }
  
  
  
      Serial.println( "-------------------------------------" );
  }
}
  
void incoming ( void ) {
    Serial.println( "Incoming HTTP request !!!" );
    char url[50] = "";

    esp.incomingHTTPRequest ( url , sizeof( url ) );

    Serial.print( "Url : " );
    Serial.println( url );

}


// Another example of outgoing HTTP request
void spark ( void ) {
    static int i = 0;
    int result = 0;

    char sparkurl[] = "http://data.sparkfun.com/input/wpYGMnD506T7GV6b6q31?private_key=XXXXXXXXXXXXXx&val1=10";

    result =  esp.urlOpen( sparkurl );

    Serial.println( result );

    i++;
}
