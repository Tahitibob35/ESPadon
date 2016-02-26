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



void parseURI ( String uri , int * pin , int * value) {
    int mstart = 0;
    int mend = 0;
    mstart = uri.indexOf( "/" , 1 );                    // pin
    mend = uri.indexOf( "/" , mstart + 1 );             // value

    * pin = uri.substring( mstart + 1 , mend ).toInt( );
    * value = uri.substring( mend + 1 ).toInt( );
}


void handleESPadonRequest( void ) {
  
    String htmlcontent = "";
    htmlcontent += "<html><head></head><body><h1>ESPadon</h1><table border=\"1\">";
    
    int i = 0;
    int rw = 0;
    int pwm_cap = 0;
    int pwm_enabled = 0;
    int value = 0; 
    
    htmlcontent +=  "<tr><td><b>Pin</b></td><td><b>Value</b></td><td><b>Action</b></td></tr>\r\n\r\n";
    for( int pin = 0 ; pin < 14 ; pin++ ) {
        s.rdigitalPinState( pin , &rw , &pwm_cap , &pwm_enabled , &value );
        htmlcontent +=  "<tr><td>";
        htmlcontent += pin;
        htmlcontent +=  "</td>";
        //htmllength += snprintf( htmlcontent + htmllength , sizeof( htmlcontent ) - htmllength , "<td>%d</td>" , rw );
        //htmllength += snprintf( htmlcontent + htmllength , sizeof( htmlcontent ) - htmllength , "<td>%d</td>" , pwm_cap );
        //htmllength += snprintf( htmlcontent + htmllength , sizeof( htmlcontent ) - htmllength , "<td>%d</td>" , pwm_enabled );

        char color[] = "yellow";
        if ( pwm_enabled == 0 ) {
            if ( value == HIGH ) {
                strcpy( color , "green" ); 
            }
            else {
                strcpy( color , "red" ); 
            }                
        }

        if ( pwm_enabled ) {
            htmlcontent += "<td bgcolor=\"";
            htmlcontent +=  color;
            htmlcontent += "\">";
            htmlcontent += value;
            htmlcontent += "</td>";
        }
        else {
            char svalue[] = "HIGH";
            if ( value == LOW ) strcpy( svalue , "LOW" );
            htmlcontent += "<td bgcolor=\"";
            htmlcontent += color;
            htmlcontent += "\">";
            htmlcontent += svalue;
            htmlcontent += "</td>" ;
        
        }
        if ( rw ) {
            htmlcontent += "<td><a href=\"/rdigitalwrite/";
            htmlcontent += pin;
            htmlcontent += "/1\">HIGH</a>&nbsp;<a href=\"/rdigitalwrite/";
            htmlcontent += pin;
            htmlcontent += "/0\">LOW</a>";

            if ( pwm_cap ) {
                htmlcontent += "<form action=\"/ranalogwrite\" method=\"get\">";
                htmlcontent += "<input type=\"text\" name=\"value\" size=\"3\">";
                htmlcontent += "<input type=\"hidden\" name=\"pin\" value=\"";
                htmlcontent += pin;
                htmlcontent += "\"><input type=\"submit\" value=\"Write\"></form>";
            }

                
            htmlcontent += "</td>";
        }
        else {
            htmlcontent += "<td></td>";
        }
        htmlcontent += "</tr>";
        
    }
    for ( int pin = 14 ; pin < 20 ; pin++ ) {
        value = s.rAnalogRead( pin );
        htmlcontent += "<td>";
        htmlcontent += pin;
        htmlcontent += "</td><td bgcolor=\"yellow\">";
        htmlcontent += value;
        htmlcontent += "</td><td></td></tr>";
    }
    
    htmlcontent +=  "</table></body></html>";
    //Serial.print( htmlcontent );
    httpserver->send( 200 , "text/html", htmlcontent);
}


void handleRequest ( void ) {
    if ( httpserver->uri().startsWith( "/digitalwrite" ) ) {
        int pin = 0;
        int value = 0;
        parseURI( httpserver->uri() , &pin , &value );
        s.rDigitalWrite( pin , value );
        httpserver->send( 200 , "text/html", "Success");
        return;
    }
    else if ( httpserver->uri().startsWith( "/digitalread" ) ) {
        int pin = 0;
        int value = 0;
        parseURI( httpserver->uri() , &pin , &value );
        value = s.rDigitalRead( pin );
        httpserver->send( 200 , "text/plain", String( value ) );
        return;
    }
    else if ( httpserver->uri().startsWith( "/analogread" ) ) {
        int pin = 0;
        int value = 0;
        parseURI( httpserver->uri() , &pin , &value );
        value = s.rAnalogRead( pin );
        httpserver->send( 200 , "text/plain", String( value ) );
        return;
    }
    else if ( httpserver->uri().startsWith( "/analogwrite" ) ) {
        int pin = 0;
        int value = 0;
        parseURI( httpserver->uri() , &pin , &value );
        s.rAnalogWrite( pin , value );
        httpserver->send( 200 , "text/html", "Success");
        return;
    }
    else if ( httpserver->uri().startsWith( "/rdigitalwrite" ) ) {
        int pin = 0;
        int value = 0;
        parseURI( httpserver->uri() , &pin , &value );
        s.rDigitalWrite( pin , value );
        httpserver->sendHeader("Location", "/ESPadon");
        httpserver->send(302, "redirecting....");  
        return;
    }
    else if ( httpserver->uri().startsWith( "/ranalogwrite" ) ) {
        int pin = -1;
        int value = -1;

        for ( uint8_t i = 0; i < httpserver->args(); i++ ) {
            if ( httpserver->argName( i ) == "value" )
                value = httpserver->arg ( i ).toInt();
            if ( httpserver->argName( i ) == "pin" )
                pin = httpserver->arg ( i ).toInt();          
        }

        if (( pin != -1) && ( value != -1 ) )
            s.rAnalogWrite( pin , value );
        httpserver->sendHeader( "Location", "/ESPadon" );
        httpserver->send( 302, "redirecting...." );  
        return;
    }
    else {
      String uri = httpserver->uri();
      uri += "?";
      for ( uint8_t i = 0; i < httpserver->args(); i++ ) {
            uri += httpserver->argName( i );
            uri += "=";
            uri +=  httpserver->arg ( i );   
            if ( i < ( httpserver->args() - 1) ) uri += "&";
      }
      char a_uri[ uri.length() + 1 ]; 
      memset( a_uri , 0 , sizeof( a_uri ) );   // A optimiser....
      uri.toCharArray( a_uri , sizeof( a_uri ) );
      s.sendMessage( A_HTTPREQUEST , false , "s" , a_uri );  
      httpserver->send( 200 , "text/html", "Success");    

      return;
      
      
    }
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
        httpserver->onNotFound( handleRequest );
        httpserverconfigured = true;
    httpserver->begin();
    httpserverstarted = true;
}


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

