#include "Arduino.h"
#include <stdarg.h>
#include "serialcomm.h"
#include "espadon.h"


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
