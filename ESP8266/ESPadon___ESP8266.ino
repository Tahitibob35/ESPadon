#include <serialcomm.h>
#include "ESPadonESP8266.h"
#include <ESP8266WiFi.h>
#include <SPI.h>

SerialComm s( Serial );


void setup( ) {
  // put your setup code here, to run once:

 Serial.begin( 115200 );
 s.attach( A_WIFISTATUS , wifiStatus );
 s.attach( A_WIFIDISCONN , wifiDisconnect );
 s.attach( A_WIFIBEGIN , wifiBegin );
 s.attach( A_SSID , wifiSSID );
 s.attach( A_BSSID , wifiBSSID );


}

void loop () {
  // put your main code here, to run repeatedly:
	s.check_reception( );

}


/**
 * Return the status of the Wifi connection
 * @param url String
 * @param httpsFingerprint String
 */
void wifiStatus( void ) {
	int result = 0;
	result = WiFi.status( );
    s.sendAck( "i" , result );
}


/**
 * Disconnect Wifi
 */
void wifiDisconnect( void ) {
	WiFi.disconnect( );
}


/**
 * Connect to the Wifi network
 */
void wifiBegin( void ) {
	char ssid[33] = "";
	char pass[20] = "";
	s.getData( "ss" , &ssid , sizeof( ssid ) , &pass , sizeof( pass ) );
    s.sendAck( "i" , WiFi.begin( ssid , pass ) );
}


/**
 * Return the current SSID
 */
void wifiSSID( void ) {
	char ssid[33] = "";
	String Str_ssid;
	Str_ssid = WiFi.SSID( );
	Str_ssid.toCharArray( ssid , sizeof( ssid ) );
    s.sendAck( "s" , ssid );
}


/**
 * Return the AM address of the router
 */
void wifiBSSID( void ) {
	char bssid[18] = { 0 };
	String Str_bssid;
	Str_bssid = WiFi.BSSIDstr( );
	Str_bssid.toCharArray( bssid , sizeof( bssid ) );
    s.sendAck( "s" , bssid );
}


