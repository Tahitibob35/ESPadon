/*
  espadon.h - Library for the ESP8266 module
  Created by David Hautbois.
  Released into the public domain.
*/
#ifndef espadon_h
#define espadon_h

#include "serialcomm.h"


/*
  An ESP8266 channel is activated by creating an instance of the ESPadon class passing
  a Stream object (hard or soft).

  The methods are:
    ESPadon - Class for using the ESP8266 module.
    httpGET( url )  - Send an GET HTTP request the the URL.
    SSID            - Get the current sSID og the ESP8266 module

 */

#include "Arduino.h"

class ESPadon
{
  public:
	ESPadon( Stream &s );
	int httpGET( char * url );         // Open the URL
	bool SSID( char * ssid );          // Get the SSID
     
  private:
	Stream *_serial;
	SerialComm sc;
};

#endif
