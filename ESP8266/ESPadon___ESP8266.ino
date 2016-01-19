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
	char ip[16];
	IPAddress ip_adr;
	String ip_str;
	ip_adr = WiFi.localIP( );
	ip_str = ip_adr.toString();
	ip_str.toCharArray( ip , sizeof ( ip ));
    s.sendAck( "s" , ip  );
}


/**
 * Return the IP address of the ESP8266 module
 */
void wifiSubnet( void ) {
	char subnet[16];
	IPAddress subnet_adr;
	String subnet_str;
	subnet_adr = WiFi.subnetMask( );
	subnet_str = subnet_adr.toString();
	subnet_str.toCharArray( subnet , sizeof ( subnet ));
    s.sendAck( "s" , subnet  );
}
