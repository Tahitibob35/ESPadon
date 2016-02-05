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

  esp.startHTTPServer ( 80 );
  esp.sc.attach( 2 , incoming);

}


void loop( ) {

    //Serial.println ( "A loop..." );

    if ( mySerial.available( ) ) {
        esp.sc.check_reception( );
    }

	/*char nssid[] = "TahitibobNetwork";
    char npass[] = "calimeroestgentil";
    int res = 0;
    res  = esp.begin( nssid , npass );
    delay(5000);

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
    delay(2000);

    delay(5000);

    int mac[6];
    if ( esp.macAddress( mac ) ){
    	Serial.print( "MAC : " );
    	for (int i=0 ; i<6 ; i++ ) {
    	    Serial.print( mac[i] , HEX );
    	}
    	Serial.println( "" );
    }

    int bssid[6];
    if ( esp.BSSID( bssid ) ){
    	Serial.print( "BSSID : " );
    	for (int i=0 ; i<6 ; i++ ) {
    	    Serial.print( bssid[i] , HEX );
    	}
    	Serial.println( "" );
    }

    int ip[4];
    if ( esp.localIP( ip ) ){
    	Serial.print( "IP : " );
    	for (int i=0 ; i<4 ; i++ ) {
    	    Serial.print( ip[i] , DEC );
    	}
    	Serial.println( "" );
    }

    if ( esp.subnetMask( ip ) ){
    	Serial.print( "Subnet mask : " );
    	for (int i=0 ; i<4 ; i++ ) {
    	    Serial.print( ip[i] , DEC );
    	}
    	Serial.println( "" );
    }



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
    Serial.println( esp.status( ) );*/

    //delay(2000);
}

void incoming ( void ) {
    Serial.println( "incoming !!!" );
    char url[30] = "";
    char val1[20] = "";
    char val2[20] = "";
    char val3[20] = "";
    int rcv_args = 0;

    int max_args = 3;


    esp.getHTTPRequest ( url , sizeof( url ) , max_args , &rcv_args\
                       , val1 , sizeof(val1) \
                       , val2 , sizeof(val2) \
                       , val3 , sizeof(val3) \
                       );

    Serial.print( "Url : " );
    Serial.println( url );
    Serial.print( "args_count : " );
    Serial.println( rcv_args );
    Serial.print( "val1 : " );
    Serial.println( val1 );
    Serial.print( "val2 : " );
    Serial.println( val2 );
    Serial.print( "val3 : " );
    Serial.println( val3 );

}
