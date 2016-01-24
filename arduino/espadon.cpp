#include "Arduino.h"
#include <stdarg.h>
#include "serialcomm.h"
#include "espadon.h"


// Constructeur
ESPadon::ESPadon( Stream &s ): _serial( &s ) {

	this->sc = SerialComm ( *_serial );
}


int ESPadon::httpGET( char * url ) {
    if ( sc.sendMessage( 11 , true , "s", url) ) {
        int wstatus = 0;
        sc.getData( "i" , &wstatus );
        return wstatus;
    }
    return -1;
}

bool ESPadon::SSID( char * ssid ) {
    if ( sc.sendMessage( 5 , true ) ) {
        sc.getData( "s" , ssid );
        return true;
    }
    return false;
}
