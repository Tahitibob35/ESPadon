#include <serialcomm.h>
#include "ESPadonESP8266.h"
#include <ESP8266WiFi.h>
#include <SPI.h>

SerialComm s( Serial );


void setup( ) {
  // put your setup code here, to run once:

 Serial.begin( 9600 );
 s.attach( A_WIFISTATUS , wifiStatus );
 s.attach( A_WIFIDISCONN , wifiDisconnect );
 s.attach( A_WIFIBEGIN , wifiBegin );
 s.attach( A_SSID , wifiSSID );
 s.attach( A_BSSID , wifiBSSID );
 s.attach( A_MAC , wifiMAC );
 s.attach( A_IP , wifiIP );
 s.attach( A_SUBNET , wifiSubnet );




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
 * Return the MAC address of the router
 */
void wifiBSSID( void ) {
	uint8_t * bssid;
	bssid = WiFi.BSSID();
    s.sendAck( "iiiiii" , bssid[0] , bssid[1] , bssid[2] , bssid[3]  , bssid[4] , bssid[5]  );
}


/**
 * Return the MAC address of the ESP8266 module
 */
void wifiMAC( void ) {
	byte mac[6];
	WiFi.macAddress(mac);
    s.sendAck( "iiiiii" , mac[0] , mac[1] , mac[2] , mac[3]  , mac[4] , mac[5]  );
}


/**
 * Return the IP address of the ESP8266 module
 */
void wifiIP( void ) {
	IPAddress ip_adr;
	ip_adr = WiFi.localIP( );
    s.sendAck( "iiii" , ip_adr[0], ip_adr[1] , ip_adr[2], ip_adr[3] );


}


/**
 * Return the IP address of the ESP8266 module
 */
void wifiSubnet( void ) {
	IPAddress subnet_adr;
	subnet_adr = WiFi.subnetMask( );
    s.sendAck( "iiii" , subnet_adr[0], subnet_adr[1] , subnet_adr[2], subnet_adr[3] );
}
