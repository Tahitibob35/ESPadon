#include "Arduino.h"
#include <stdarg.h>
#include "serialcomm.h"
#include "espadon.h"
#include <stdarg.h>


// Constructeur
ESPadon::ESPadon( Stream &s ): _serial( &s ) {

	this->sc = SerialComm ( *_serial );
}

/**
 * Open the URL
 */
int ESPadon::httpGET( char * url ) {
    if ( sc.sendMessage( A_HTTPGET , true , "s", url) ) {
        int wstatus = 0;
        sc.getData( "i" , &wstatus );
        return wstatus;
    }
    return -1;
}


/**
 * Get the SSID
 */
bool ESPadon::SSID( char * ssid ) {
    if ( sc.sendMessage( A_SSID , true ) ) {
        sc.getData( "s" , ssid , 50);
        return true;
    }
    return false;
}


/**
 * Get the status
 */
int ESPadon::status( void ) {
	int status = 0;
    if ( sc.sendMessage( A_WIFISTATUS , true ) ) {
        sc.getData( "i" , &status );
        return status;
    }
    return -1;
}


/**
 * Disconnect
 */
bool ESPadon::disconnect( void ) {
    return sc.sendMessage( A_WIFIDISCONN , false );
}


/**
 * Begin
 */
int ESPadon::begin( char * ssid , char * password ) {
	int result = 0;
    if ( sc.sendMessage( A_WIFIBEGIN , true , "ss" , ssid , password ) ) {
    	sc.getData( "i" , &result );
    	return result;
    }
    return -1;
}


/**
 * Get the BSSID
 */
bool ESPadon::BSSID( int * bssid ) {
    if ( sc.sendMessage( A_BSSID , true ) ) {
        sc.getData( "iiiiii" , &bssid[0] , &bssid[1] , &bssid[2] , bssid[3] , bssid[4] , bssid[5] );
        return true;
    }
    return false;
}


/**
 * Get the MAC address
 */
bool ESPadon::macAddress( int * mac ) {
    if ( sc.sendMessage( A_MAC , true ) ) {
        sc.getData( "iiiiii" , &mac[0] , &mac[1] , &mac[2] , &mac[3] , &mac[4] , &mac[5] );
        return true;
    }
    return false;
}


/**
 * Get the IP address
 */
bool ESPadon::localIP ( int * ip ) {
    if ( sc.sendMessage( A_IP , true ) ) {
        sc.getData( "iiii" , &ip[0] , &ip[1] , &ip[2] , &ip[3] );
        return true;
    }
    return false;
}


/**
 * Get the subnet
 */
bool ESPadon::subnetMask ( int * ip ) {
    if ( sc.sendMessage( A_SUBNET , true ) ) {
        sc.getData( "iiii" , &ip[0] , &ip[1] , &ip[2] , &ip[3] );
        return true;
    }
    return false;
}


/**
 * Start HTTP server
 */
bool ESPadon::startHTTPServer ( int port ) {
    return sc.sendMessage( A_STARTHTTPSERVER , false , "i" , port );
}


/**
 * Get HTTP request
 */
bool ESPadon::getHTTPRequest ( char * url , int urlsize , int max_args , int * rcv_args ,... ) {
    va_list args;
    va_start( args, rcv_args );

    sc.getString( url , urlsize);
    *rcv_args = sc.getInt( );

    for ( int i = 0 ; i < min(max_args , *rcv_args ) ; i++) {
        char *s = va_arg( args , char * );
        int size = va_arg( args , int );
        sc.getString( s , size );
    }
    va_end( args );
    return true;
}


/**
 * Check for incoming messages
 */
void ESPadon::check_reception( void ) {
    sc.check_reception( );
}


/**
 * Callback for incoming HTTP request
 */
void ESPadon::attach( void ( *pcallbackfct )( void ) ) {
    this->sc.attach( A_HTTPREQUEST , pcallbackfct );
}

