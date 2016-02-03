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
    if ( sc.sendMessage( 11 , true , "s", url) ) {
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
    if ( sc.sendMessage( 5 , true ) ) {
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
    if ( sc.sendMessage( 2 , true ) ) {
        sc.getData( "i" , &status );
        return status;
    }
    return -1;
}


/**
 * Disconnect
 */
bool ESPadon::disconnect( void ) {
    return sc.sendMessage( 3 , false );
}


/**
 * Begin
 */
int ESPadon::begin( char * ssid , char * password ) {
	int result = 0;
    if ( sc.sendMessage( 4 , true , "ss" , ssid , password ) ) {
    	sc.getData( "i" , &result );
    	return result;
    }
    return -1;
}


/**
 * Get the BSSID
 */
bool ESPadon::BSSID( int * bssid ) {
    if ( sc.sendMessage( 6 , true ) ) {
        sc.getData( "iiiiii" , &bssid[0] , &bssid[1] , &bssid[2] , bssid[3] , bssid[4] , bssid[5] );
        return true;
    }
    return false;
}


/**
 * Get the MAC address
 */
bool ESPadon::macAddress( int * mac ) {
    if ( sc.sendMessage( 7 , true ) ) {
        sc.getData( "iiiiii" , &mac[0] , &mac[1] , &mac[2] , &mac[3] , &mac[4] , &mac[5] );
        return true;
    }
    return false;
}


/**
 * Get the IP address
 */
bool ESPadon::localIP ( int * ip ) {
    if ( sc.sendMessage( 8 , true ) ) {
        sc.getData( "iiii" , &ip[0] , &ip[1] , &ip[2] , &ip[3] );
        return true;
    }
    return false;
}


/**
 * Get the subnet
 */
bool ESPadon::subnetMask ( int * ip ) {
    if ( sc.sendMessage( 9 , true ) ) {
        sc.getData( "iiii" , &ip[0] , &ip[1] , &ip[2] , &ip[3] );
        return true;
    }
    return false;
}


/**
 * Start HTTP server
 */
bool ESPadon::startHTTPServer ( int port ) {
    return sc.sendMessage( 10 , false , "i" , port );
}


/**
 * Get HTTP request
 */
bool ESPadon::getHTTPRequest ( char * url , int urlsize, ... ) {

    sc.getString( url , urlsize);
    int args_count = sc.getInt( );



    va_list args;
    va_start( args, urlsize );
    for ( int i = 0 ; i < args_count ; i++) {
        char *s = va_arg( args , char * );
        sc.getString( s , 20 );

    }
    /*
    char val1[20] = "";
    char murl[30];
    sc.getData( "s"  , url , 30  );
    Serial.println ( murl );
    sc.getData( "sis"  , url , urlsize , &args_count , args  );

    Serial.print( "getHTTPRequest : args_count : " );
    Serial.println( args_count );*/
    return true;
}
