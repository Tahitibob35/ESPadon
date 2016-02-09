#include <serialcomm.h>
#include "ESPadonESP8266.h"
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <ESP8266WebServer.h>
#include <stdio.h>

SerialComm s( Serial );
ESP8266WebServer* httpserver = NULL;
bool httpserverstarted = false;
bool httpserverconfigured = false;



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
    s.attach( A_STARTHTTPSERVER , startHTTPServer );



}

void loop () {
    // put your main code here, to run repeatedly:
    s.check_reception( );

    if ( httpserverstarted ) {
        httpserver->handleClient();
    }
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


/**
 * Handle incoming HTTP request
 */
void handleHTTPRequest( void ) {
    char tmpstr[50];
    s.sendHeader( A_HTTPREQUEST );
    httpserver->uri( ).toCharArray( tmpstr , sizeof( tmpstr ) );
    s.sendcharArray( tmpstr );
    s.sendInteger( httpserver->args() );
    for (uint8_t i=0; i<httpserver->args(); i++){
        httpserver->arg(i).toCharArray( tmpstr , sizeof( tmpstr ) );
        s.sendcharArray( tmpstr );
    }
    s.sendFooter( );
    httpserver->send( 200 , "text/plain", "a");
}


/**
 * Start HTTP server
 */
void startHTTPServer( void ) {
    if ( httpserverstarted )
        return;
    int port = 0;
    s.getData( "i" , &port );
    httpserver = new ESP8266WebServer( port );
    if ( !httpserverconfigured )
        httpserver->on("/ESPadon", handleESPadonRequest );
        httpserver->onNotFound( test );
        httpserverconfigured = true;
    httpserver->begin();
    httpserverstarted = true;
}

void parseURI ( String uri , int * pin , int * value) {
    int mstart = 0;
    int mend = 0;
    mstart = uri.indexOf( "/" , 1 );                    // pin
    mend = uri.indexOf( "/" , mstart + 1 );             // value

    * pin = uri.substring( mstart + 1 , mend ).toInt( );
    * value = uri.substring( mend + 1 ).toInt( );
}


void handleESPadonRequest( void ) {





    char tmp[100] = "";
    char htmlcontent[2500] = "<html>\
  <head>\
  </head>\
  <body>\
    <h1>ESPadon</h1>\
    <table>";
    int i = 0;
    for( uint8_t pin = 0 ; pin < 20 ; pin++ ) {
        if ( pin < 14 ) {
            i = s.rDigitalRead( pin );
        }
        else {
            i = s.rAnalogRead( pin );
        }
        s.getData( "i" , &i );
        snprintf( tmp , sizeof( tmp ) , "<tr><td>%d</td><td>%d</td>" , pin , i );
        strcat( htmlcontent , tmp );
        snprintf( tmp , sizeof( tmp ) , "<td><a href=\"/rdigitalwrite/%d/1\">on</a></td>" , pin );
        strcat( htmlcontent , tmp );
        snprintf( tmp , sizeof( tmp ) , "<td><a href=\"/rdigitalwrite/%d/0\">off</a></td>" , pin );
                strcat( htmlcontent , tmp );
        strcat( htmlcontent , "</tr>" );
    }

    strcat( htmlcontent , "</table></body></html>" );

    httpserver->send( 200 , "text/html", htmlcontent);

}

void test ( void ) {
    if ( httpserver->uri().startsWith( "/digitalwrite" ) ) {
        int pin = 0;
        int value = 0;
        parseURI( httpserver->uri() , &pin , &value );
        s.rDigitalWrite( pin , value );
        httpserver->send( 200 , "text/html", " ");
    }
    else if ( httpserver->uri().startsWith( "/rdigitalwrite" ) ) {
        int pin = 0;
        int value = 0;
        parseURI( httpserver->uri() , &pin , &value );
        s.rDigitalWrite( pin , value );
        httpredirect( "/ESPadon" );
    }


}

void httpredirect ( const char * uri ) {
    char body[70] = "HTTP/1.1 302 Found\r\nLocation: ";
    strcat( body , uri );
    strcat( body , "\r\n" );
    httpserver->sendContent(body);
}


